/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2019 Laurent Montel <montel@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "loaderutil_p.h"
#include <QDebug>
#include <QRegularExpression>

//#define DEBUG_PARSING_FEED
#ifdef DEBUG_PARSING_FEED
#include <QFile>
#include <QTextStream>
#endif
QUrl Syndication::LoaderUtil::parseFeed(const QByteArray &data, const QUrl &url)
{
#ifdef DEBUG_PARSING_FEED
    qDebug() << " QUrl Syndication::LoaderUtil::parseFeed(const QByteArray &data, const QUrl &url)";
    QFile headerFile(QStringLiteral("/tmp/bb.txt"));
    headerFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outHeaderStream(&headerFile);
    outHeaderStream << data;
    headerFile.close();
#endif
    QUrl discoveredFeedURL;
    QString str = QString::fromLatin1(data.constData()).simplified();
    QString s2;
    //QTextStream ts( &str, QIODevice::WriteOnly );
    //ts << data.data();

    // "<[\\s]link[^>]*rel[\\s]=[\\s]\\\"[\\s]alternate[\\s]\\\"[^>]*>"
    // "type[\\s]=[\\s]\\\"application/rss+xml\\\""
    // "href[\\s]=[\\s]\\\"application/rss+xml\\\""

    QRegularExpression rx(QStringLiteral("(?:REL)[^=]*=[^sAa]*(?:service.feed|ALTERNATE)[^sAa]*"
                                         "[\\s]*type[^=]*=\"application/rss\\+xml\"[^s][^s](?:[^>]*)"
                                         "[\\s]*[\\s]*[^s]*(?:HREF)[^=]*=[^A-Z0-9-_~,./$]*([^'\">\\s]*)"),
                           QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match;
    if ((match = rx.match(str)).hasMatch()) {
        s2 = match.captured(1);
    } else {
        const QRegularExpression rx2(QStringLiteral("(?:REL)[^=]*=[^sAa]*(?:service.feed|ALTERNATE)"
                                                    "[\\s]*[^s][^s](?:[^>]*)(?:HREF)[^=]*=[^A-Z0-9-_~,./$]*([^'\">\\s]*)"),
                                     QRegularExpression::CaseInsensitiveOption);
        if ((match = rx2.match(str)).hasMatch()) {
            s2 = match.captured(1);
        } else {
            // does not support Atom/RSS autodiscovery.. try finding feeds by brute force....
            QStringList feeds;
            QString host = url.host();
            rx.setPattern(QStringLiteral("(?:<A )[^H]*(?:HREF)[^=]*=[^A-Z0-9-_~,./]*([^'\">\\s]*)"));
            QRegularExpressionMatchIterator iter = rx.globalMatch(str);
            while (iter.hasNext()) {
                match = iter.next();
                s2 = match.captured(1);
                if (s2.endsWith(QLatin1String(".rdf"))
                    || s2.endsWith(QLatin1String(".rss"))
                    || s2.endsWith(QLatin1String(".xml"))) {
                    feeds.append(s2);
                }
            }

            QUrl testURL;
            // loop through, prefer feeds on same host
            QStringList::const_iterator end(feeds.constEnd());
            for (QStringList::const_iterator it = feeds.constBegin(); it != end; ++it) {
                testURL = QUrl(*it);
                if (testURL.host() == host) {
                    s2 = *it;
                    break;
                }
            }
        }
    }

    if (s2.isNull()) {
        return discoveredFeedURL;
    }

    if (QUrl(s2).isRelative()) {
        if (s2.startsWith(QLatin1String("//"))) {
            s2.prepend(url.scheme() + QLatin1Char(':'));
            discoveredFeedURL = QUrl(s2);
        } else if (s2.startsWith(QLatin1Char('/'))) {
            discoveredFeedURL = url;
            discoveredFeedURL.setPath(s2);
        } else {
            discoveredFeedURL = url;
            discoveredFeedURL.setPath(discoveredFeedURL.path() + QLatin1Char('/') + s2);
        }
    } else {
        discoveredFeedURL = QUrl(s2);
    }

    return discoveredFeedURL;
}
