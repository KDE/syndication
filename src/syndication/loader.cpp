/*
 * loader.cpp
 *
 * Copyright (c) 2001, 2002, 2003 Frerich Raabe <raabe@kde.org>
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. For licensing and distribution details, check the
 * accompanying file 'COPYING'.
 */
#include "loader.h"
#include "dataretriever.h"
#include "documentsource.h"
#include "feed.h"
#include "global.h"
#include "parsercollection.h"

#include <kio/global.h>
#include <QUrl>

#include <QtCore/QBuffer>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>

#include <boost/shared_ptr.hpp>

// test: TODO remove
#include <iostream>

namespace Syndication
{

struct Loader::LoaderPrivate {
    LoaderPrivate() : retriever(0), lastError(Success),
        retrieverError(0)
    {
    }

    ~LoaderPrivate()
    {
        delete retriever;
    }

    DataRetriever *retriever;
    Syndication::ErrorCode lastError;
    int retrieverError;
    QUrl discoveredFeedURL;
    QUrl url;
};

Loader *Loader::create()
{
    return new Loader;
}

Loader *Loader::create(QObject *object, const char *slot)
{
    Loader *loader = create();
    connect(loader, SIGNAL(loadingComplete(Syndication::Loader *,
                                           Syndication::FeedPtr, Syndication::ErrorCode)),
            object, slot);
    return loader;
}

Loader::Loader() : d(new LoaderPrivate)
{
}

Loader::~Loader()
{
    delete d;
}

void Loader::loadFrom(const QUrl &url)
{
    loadFrom(url, new FileRetriever);
}

void Loader::loadFrom(const QUrl &url, DataRetriever *retriever)
{
    if (d->retriever != 0L) {
        return;
    }

    d->url = url;
    d->retriever = retriever;

    connect(d->retriever, SIGNAL(dataRetrieved(QByteArray, bool)),
            this, SLOT(slotRetrieverDone(QByteArray, bool)));

    d->retriever->retrieveData(url);
}

int Loader::retrieverError() const
{
    return d->retrieverError;
}

Syndication::ErrorCode Loader::errorCode() const
{
    return d->lastError;
}

void Loader::abort()
{
    if (d && d->retriever) {
        d->retriever->abort();
        delete d->retriever;
        d->retriever = 0L;
    }

    emit loadingComplete(this, FeedPtr(), Aborted);
    delete this;
}

QUrl Loader::discoveredFeedURL() const
{
    return d->discoveredFeedURL;
}

void Loader::slotRetrieverDone(const QByteArray &data, bool success)
{
    d->retrieverError = d->retriever->errorCode();
    ErrorCode status = Success;
    FeedPtr feed;
    bool isFileRetriever = dynamic_cast<FileRetriever *>(d->retriever) != 0;
    delete d->retriever;
    d->retriever = 0;

    if (success) {
        DocumentSource src(data, d->url.url());
        feed = parserCollection()->parse(src);

        if (parserCollection()->lastError() != Syndication::Success) {
            status = parserCollection()->lastError();
            discoverFeeds(data);
        }
    } else {
        if (isFileRetriever) {
            // retriever is a FileRetriever, so we interpret the
            // error code and set lastError accordingly
            status = FileNotFound; // TODO
            std::cout << "file retriever error: " <<  d->retrieverError << std::endl;
        } else {
            // retriever is a custom impl, so we set OtherRetrieverError
            status = OtherRetrieverError;
        }
    }

    emit loadingComplete(this, feed, status);

    delete this;
}

void Loader::discoverFeeds(const QByteArray &data)
{
    QString str = QString::fromLatin1(data.constData()).simplified();
    QString s2;
    //QTextStream ts( &str, QIODevice::WriteOnly );
    //ts << data.data();

    // "<[\\s]link[^>]*rel[\\s]=[\\s]\\\"[\\s]alternate[\\s]\\\"[^>]*>"
    // "type[\\s]=[\\s]\\\"application/rss+xml\\\""
    // "href[\\s]=[\\s]\\\"application/rss+xml\\\""
    QRegExp rx(QLatin1String("(?:REL)[^=]*=[^sAa]*(?:service.feed|ALTERNATE)[\\s]*[^s][^s](?:[^>]*)(?:HREF)[^=]*=[^A-Z0-9-_~,./$]*([^'\">\\s]*)"), Qt::CaseInsensitive);
    if (rx.indexIn(str) != -1) {
        s2 = rx.cap(1);
    } else {
        // does not support Atom/RSS autodiscovery.. try finding feeds by brute force....
        int pos = 0;
        QStringList feeds;
        QString host = d->url.host();
        rx.setPattern(QLatin1String("(?:<A )[^H]*(?:HREF)[^=]*=[^A-Z0-9-_~,./]*([^'\">\\s]*)"));
        while (pos >= 0) {
            pos = rx.indexIn(str, pos);
            s2 = rx.cap(1);
            if (s2.endsWith(QLatin1String(".rdf")) ||
                    s2.endsWith(QLatin1String(".rss")) ||
                    s2.endsWith(QLatin1String(".xml"))) {
                feeds.append(s2);
            }
            if (pos >= 0) {
                pos += rx.matchedLength();
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

    if (s2.isNull()) {
        return;
    }

    if (QUrl(s2).isRelative()) {
        if (s2.startsWith(QLatin1String("//"))) {
            s2 = s2.prepend(d->url.scheme() + QLatin1Char(':'));
            d->discoveredFeedURL = QUrl(s2);
        } else if (s2.startsWith(QLatin1Char('/'))) {
            d->discoveredFeedURL = d->url;
            d->discoveredFeedURL.setPath(s2);
        } else {
            d->discoveredFeedURL = d->url;
            d->discoveredFeedURL.setPath(d->discoveredFeedURL.path() + QLatin1Char('/') + s2);
        }
        //QT5 d->discoveredFeedURL.cleanPath();
    } else {
        d->discoveredFeedURL = QUrl(s2);
    }

    //QT5 d->discoveredFeedURL.cleanPath();
}

} // namespace Syndication

