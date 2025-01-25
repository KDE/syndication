/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2005 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_DOCUMENTVISITOR_H
#define SYNDICATION_DOCUMENTVISITOR_H

#include "syndication_export.h"

namespace Syndication
{
class SpecificDocument;

namespace Atom
{
class EntryDocument;
class FeedDocument;
}

namespace RDF
{
class Document;
}

namespace RSS2
{
class Document;
}

/*!
 * \class Syndication::DocumentVisitor
 * \inmodule Syndication
 * \inheaderfile Syndication/DocumentVisitor
 *
 * \brief Visitor interface, following the Visitor design pattern.
 *
 * Use this if you
 * want to process documents and the way how to handle the document depends
 * on it's concrete type (e.g. RSS2::Document, RDF::Document...).
 *
 * TODO: insert code example
 */
class SYNDICATION_EXPORT DocumentVisitor // krazy:exclude=dpointer
{
public:
    virtual ~DocumentVisitor();

    /*!
     * Call this method to handle a document. Depending on the concrete type
     * of the document, a specialized visit method is called.
     *
     * \a document the document to process
     *
     * Returns whether this visitor handles the type of the document.
     */
    virtual bool visit(SpecificDocument *document);

    /*!
     * Reimplement this method to handle RSS2-like (RSS 0.9x, 2.0) documents.
     *
     * \a document the RSS2 document to visit
     *
     * Returns whether the visitor handled the document.
     *
     * Reimplementations of this method must return \c true.
     */
    virtual bool visitRSS2Document(Syndication::RSS2::Document *document);

    /*!
     * Reimplement this method to handle RDF (i.e. RSS 1.0) documents.
     *
     * \a document the RDF document to visit
     *
     * Returns whether the visitor handled the document.
     *
     * Reimplementations of this method must return \c true.
     */
    virtual bool visitRDFDocument(Syndication::RDF::Document *document);

    /*!
     * Reimplement this method to handle Atom feed documents (most Atom
     * feeds are of this type).
     *
     * \a document the atom feed document to visit
     *
     * Returns whether the visitor handled the document.
     *
     * Reimplementations of this method must return \c true.
     */
    virtual bool visitAtomFeedDocument(Syndication::Atom::FeedDocument *document);

    /*!
     * Reimplement this method to handle Atom entry documents.
     *
     * \a document the atom entry document to visit
     *
     * Returns whether the visitor handled the document.
     *
     * Reimplementations of this method must return \c true.
     */
    virtual bool visitAtomEntryDocument(Syndication::Atom::EntryDocument *document);
};

} // namespace Syndication

#endif // SYNDICATION_DOCUMENTVISITOR_H
