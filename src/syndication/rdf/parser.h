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
#ifndef SYNDICATION_RDF_PARSER_H
#define SYNDICATION_RDF_PARSER_H

#include <syndication/rdf/document.h>
#include <syndication/abstractparser.h>
#include <boost/shared_ptr.hpp>

namespace Syndication
{

class DocumentSource;

namespace RDF
{

/**
 * Parser implementation for RDF-based RSS 0.9 and RSS 1.0 feeds.
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT Parser : public Syndication::AbstractParser
{
public:

    /** default constructor */
    Parser();

    /** destructor */
    virtual ~Parser();

    /**
     * returns whether the passed document looks like
     * an RSS 0.9 or RSS 1.0 document.
     * @param source the document source to check
     */
    virtual bool accept(const DocumentSource &source) const;

    /**
     * Parses an RSS 0.9/1.0 document from a feed source. RSS 0.9
     * documents are converted to RSS 1.0.
     *
     * @param source The document source to parse
     * @return parsed document (a Syndication::RDF::Document), or an
     * invalid document if parsing failed.
     * @see Document::isValid()
     */
    virtual SpecificDocumentPtr parse(const DocumentSource &source) const;

    /**
     * format string of this parser, which is @c "rdf".
     *
     * @return @c "rdf"
     */
    virtual QString format() const;

private:

    Parser(const Parser &other);
    Parser &operator=(const Parser &other);

    class ParserPrivate;
    ParserPrivate *const d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_PARSER_H
