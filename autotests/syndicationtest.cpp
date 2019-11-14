/*
    This file is part of LibSyndication.

    Copyright (C) Laurent Montel <montel@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/

#include "syndicationtest.h"
#include "specificdocument.h"
#include "documentsource.h"
#include "feed.h"
#include "parsercollection.h"

#include <QDebug>
#include <QByteArray>
#include <QFile>

#include <QTest>
QTEST_GUILESS_MAIN(SyndicationTest)
using namespace Syndication;
SyndicationTest::SyndicationTest(QObject *parent)
    : QObject(parent)
{
    qputenv("LC_ALL", "C");
}

void SyndicationTest::testSyncationFile_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("referenceFileName");

    QDir dir(QStringLiteral(SYNDICATION_DATA_DIR  "/atom"));
    auto l = dir.entryList(QStringList(QStringLiteral("*.xml")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : l) {
        QTest::newRow(file.toLatin1().constData()) << QString(dir.path() + QLatin1Char('/') +  file) << QString(dir.path() + QLatin1Char('/') + file + QLatin1String(".expected"));
    }
    QDir dirRdf(QStringLiteral(SYNDICATION_DATA_DIR  "/rdf"));
    l = dirRdf.entryList(QStringList(QStringLiteral("*.xml")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : l) {
        QTest::newRow(file.toLatin1().constData()) << QString(dirRdf.path() + QLatin1Char('/') +  file) << QString(dirRdf.path() + QLatin1Char('/') + file + QLatin1String(".expected"));
    }
    QDir dirRss2(QStringLiteral(SYNDICATION_DATA_DIR  "/rss2"));
    l = dirRss2.entryList(QStringList(QStringLiteral("*.xml")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : l) {
        QTest::newRow(file.toLatin1().constData()) << QString(dirRss2.path() + QLatin1Char('/') +  file) << QString(dirRss2.path() + QLatin1Char('/') + file + QLatin1String(".expected"));
    }
}

void SyndicationTest::testSyncationFile()
{
    QFETCH(QString, fileName);
    QFETCH(QString, referenceFileName);
    QFile f(fileName);
    QVERIFY(f.open(QIODevice::ReadOnly|QIODevice::Text));

    DocumentSource src(f.readAll(), QStringLiteral("http://libsyndicationtest"));
    f.close();

    FeedPtr ptr(Syndication::parse(src));
    QVERIFY(ptr);

    const QString result = ptr->debugInfo();

    QFile expFile(referenceFileName);
    QVERIFY(expFile.open(QIODevice::ReadOnly|QIODevice::Text));
    const QByteArray expected = expFile.readAll();
    expFile.close();

    const bool compare = (result.trimmed() != QString::fromUtf8(expected));
    if (!compare) {
        qDebug() << " result.toUtf8().trimmed()" << result.trimmed();
        qDebug() << " expected.trimmed()" << expected.trimmed();
    }
    QVERIFY(compare);

    //QCOMPARE(result.toUtf8().trimmed(), expected.trimmed());
}
