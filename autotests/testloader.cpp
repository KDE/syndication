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
#include "atom/parser.h"
#include "rdf/parser.h"
#include "rss2/parser.h"
#include "syndication_version.h"

#include <kapplication.h>
#include <kaboutdata.h>

#include <klocalizedstring.h>
#include <qurl.h>

#include <QtCore/QByteArray>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>

#include <cstdlib>
#include <iostream>

using namespace Syndication;

TestLibSyndication::TestLibSyndication(const QString& url)
{
    QUrl kurl;
    if (!QUrl(url).isRelative())
        kurl = QUrl(url);
    else
        kurl = QUrl(QString("file://" + QDir::currentPath() + '/'), url);

    std::cerr << kurl.url().toLocal8Bit().data() << std::endl;
    Loader* loader = Loader::create(this, SLOT(slotLoadingComplete(Syndication::Loader*,
                                    Syndication::FeedPtr,
                                    Syndication::ErrorCode)));
    loader->loadFrom(kurl);
}

void TestLibSyndication::slotLoadingComplete(Syndication::Loader* loader,
                    Syndication::FeedPtr feed,
                    Syndication::ErrorCode error)
{
    Q_UNUSED(loader)
    Q_UNUSED(error)

    if (feed)
    {
        std::cout << feed->debugInfo().toUtf8().data() << std::endl;
        exit(0);
    }
    else
    {
        std::cerr << "error" << std::endl;
        exit(1);
    }

}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "filename expected" << std::endl;
        return 1;
    }

    KAboutData aboutData("testlibsyndication", 0, ki18n("testlibsyndication"), "0.1");

    QCommandLineParser *parser = new QCommandLineParser;
    app.setApplicationVersion(SYNDICATION_VERSION_STRING);
    parser->addVersionOption();
    parser->addHelpOption();
    parser->addOption(QCommandLineOption(QStringList() << "+url", i18n("URL of feed")));
    KApplication app;

    if ( parser->remainingArguments().count() != 1 ) parser->showHelp();

    TestLibSyndication* tester = new TestLibSyndication(args->arg( 0 ));
    Q_UNUSED(tester)

    return app.exec();
}

