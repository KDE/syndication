/*
    This file is part of LibSyndication.

    Copyright (C) 2006 Frank Osterfeld <osterfeld@kde.org>

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

#include "specificdocument.h"
#include "documentsource.h"
#include "feed.h"
#include "parsercollection.h"

#include <QtCore/QByteArray>
#include <QtCore/QFile>
#include <QtCore/QString>

#include <iostream>


using namespace Syndication;

void printUsage(const QString& error)
{
    std::cerr << "testlibsyndication - (C) Frank Osterfeld 2006" << std::endl;
    std::cerr << std::endl;
    if (!error.isNull())
    {
        std::cerr << error.toUtf8().data() << std::endl;
        std::cerr << std::endl;
    }
    else
    {
        std::cerr << "Prints the parsed content of a feed file to standard output." << std::endl;
        std::cerr << std::endl;
    }
    std::cerr << "Usage: testlibsyndication [--specific-format] <file> [--compare <expectedfile>]" << std::endl;
    std::cerr << std::endl;
    std::cerr << "--specific-format: If set, the debug output for the specific" << std::endl;
    std::cerr << "feed format is printed to stdout, otherwise the debug output" << std::endl;
    std::cerr << "for the abstraction" << std::endl;
}

int main(int argc, char **argv)
{

    int pcompare = 2;
    if (argc < 2)
    {
        printUsage("filename expected");
        return 1;
    }

    QString filename(argv[1]);
    QString arg1(argv[1]);
    
    bool specificformat = false;
    
    if (filename == "--specific-format")
    {
        if (argc < 3)
        {
            printUsage("filename expected");
            return 1;
        }
        filename = QString(argv[2]);
        specificformat = true;
        pcompare += 1;
    }
    
    QString expfname;
    
    if (argc >= pcompare + 1 && QString(argv[pcompare]) == "--compare")
    {
        expfname = QString(argv[pcompare+1]);
    }
    
    
    QFile f(filename);

    if (!f.open(QIODevice::ReadOnly))
    {
        printUsage("Couldn't open file");
        return 1;
    }
    
   
    DocumentSource src(f.readAll(), "http://libsyndicationtest");
    f.close();

    FeedPtr ptr(Syndication::parse(src));

    if (ptr == 0L)
    {
        printUsage("Couldn't parse file");
        return 1;
    }

    QString res = specificformat ? ptr->specificDocument()->debugInfo() : ptr->debugInfo();
    
    if (expfname.isNull())
    {
        std::cout << res.toUtf8().data() << std::endl;
        return 0;
    }
    else
    {
          QFile expFile(expfname);
          expFile.open(QIODevice::ReadOnly);
          QByteArray expected = expFile.readAll();
          expFile.close();
          return expected == (res.toUtf8() + '\n') ? 0 : 1;
    }
    
    return 0;
}
