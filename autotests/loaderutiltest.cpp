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

#include "loaderutiltest.h"
#include "loaderutil_p.h"
#include <QTest>
QTEST_GUILESS_MAIN(LoaderUtilTest)

LoaderUtilTest::LoaderUtilTest(QObject *parent)
    : QObject(parent)
{

}

void LoaderUtilTest::testParsing_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QUrl>("url");
    QTest::addColumn<QUrl>("urlfound");
    QTest::addRow("bug-383381") << QString(QStringLiteral(SYNDICATION_DATA_FEEDPARSING_DIR) + QStringLiteral("/bug-383381.txt"))
                                << QUrl(QStringLiteral("https://www.youtube.com/user/bigclivedotcom/videos"))
                                << QUrl(QStringLiteral("https://www.youtube.com/feeds/videos.xml?channel_id=UCtM5z2gkrGRuWd0JQMx76qA"));
}

void LoaderUtilTest::testParsing()
{
    QFETCH(QString, fileName);
    QFETCH(QUrl, url);
    QFETCH(QUrl, urlfound);
    QFile f(fileName);
    QVERIFY(f.open(QIODevice::ReadOnly|QIODevice::Text));
    const QByteArray ba = f.readAll();
    QCOMPARE(Syndication::LoaderUtil::parseFeed(ba, url), urlfound);
}
