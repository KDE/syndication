/*
    This file is part of LibSyndication.

    Copyright (C) 2005 Frank Osterfeld <osterfeld@kde.org>

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

#include "testloader.h"

#include "specificdocument.h"
#include "feed.h"
#include "loader.h"
#include "dataretriever.h"
#include "atom/parser.h"
#include "rdf/parser.h"
#include "rss2/parser.h"
#include "syndication_version.h"

#include <qapplication.h>

#include <qurl.h>

#include <QByteArray>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>
#include <QFile>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <cstdlib>
#include <iostream>

using namespace Syndication;

class SimpleRetriever : public Syndication::DataRetriever
{
    Q_OBJECT
public:
    explicit SimpleRetriever()
        : mMgr(new QNetworkAccessManager)
        , mReply(nullptr)
    {
    }
    ~SimpleRetriever()
    {
        delete mReply;
        delete mMgr;
    }

    void retrieveData(const QUrl & url) override
    {
        mReply = mMgr->get(QNetworkRequest(url));
        connect(mReply, &QNetworkReply::finished,
                this, [this]() {
                    if (mReply->error() == QNetworkReply::NoError) {
                        Q_EMIT dataRetrieved(mReply->readAll(), true);
                    } else {
                        Q_EMIT dataRetrieved({}, false);
                    }
                });
    }
    void abort() override
    {
        if (mReply) {
            mReply->abort();
        }
    }
    int errorCode() const override
    {
        if (mReply) {
            return mReply->error();
        } else {
            return 0;
        }
    }

private:
    QNetworkAccessManager *mMgr;
    QNetworkReply *mReply;
};

TestLibSyndication::TestLibSyndication(const QString &url)
{
    QUrl kurl = QUrl::fromUserInput(url);

    std::cerr << kurl.url().toLocal8Bit().data() << std::endl;
    Loader *loader = Loader::create(this, SLOT(slotLoadingComplete(Syndication::Loader *,
                                    Syndication::FeedPtr,
                                    Syndication::ErrorCode)));
    loader->loadFrom(kurl, new SimpleRetriever());
}

void TestLibSyndication::slotLoadingComplete(Syndication::Loader *loader,
        Syndication::FeedPtr feed,
        Syndication::ErrorCode error)
{
    Q_UNUSED(loader)
    Q_UNUSED(error)

    if (feed) {
        std::cout << feed->debugInfo().toUtf8().data() << std::endl;
        exit(0);
    } else {
        std::cerr << "error" << std::endl;
        exit(1);
    }

}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "filename expected" << std::endl;
        return 1;
    }

    QApplication app(argc, argv);

    QCommandLineParser parser;
    app.setApplicationVersion(QStringLiteral(SYNDICATION_VERSION_STRING));
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(QStringList() << QStringLiteral("+url"), QStringLiteral("URL of feed")));
    parser.process(app);

    if (parser.positionalArguments().count() != 1) {
        parser.showHelp();
    }

    TestLibSyndication *tester = new TestLibSyndication(parser.positionalArguments().at(0));
    Q_UNUSED(tester)

    return app.exec();
}

#include "testloader.moc"
