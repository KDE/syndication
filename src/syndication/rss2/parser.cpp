/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2005 Frank Osterfeld <osterfeld@kde.org>
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

#include "parser.h"
#include "document.h"

#include <documentsource.h>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtCore/QString>

namespace Syndication
{
namespace RSS2
{

class Parser::ParserPrivate {};

bool Parser::accept(const Syndication::DocumentSource &source) const
{
    QDomDocument doc = source.asDomDocument();
    if (doc.isNull()) {
        return false;
    }

    QDomNode root = doc.namedItem(QLatin1String("rss")).toElement();

    return !root.isNull();
}

Syndication::SpecificDocumentPtr Parser::parse(const DocumentSource &source) const
{
    return DocumentPtr(new Document(Document::fromXML(source.asDomDocument())));
}

QString Parser::format() const
{
    return QLatin1String("rss2");
}

Parser::Parser() : d(0) {}
Parser::Parser(const Parser &other) : AbstractParser(other), d(0) {}
Parser::~Parser() {}
Parser &Parser::operator=(const Parser & /*other*/)
{
    return *this;
}

} // namespace RSS2
} // namespace Syndication
