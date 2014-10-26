/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2006 Frank Osterfeld <osterfeld@kde.org>
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

#ifndef SYNDICATION_RDF_DOCUMENT_H
#define SYNDICATION_RDF_DOCUMENT_H

#include <syndication/rdf/resourcewrapper.h>

#include <syndication/specificdocument.h>

template <class T> class QList;

namespace Syndication
{
namespace RDF
{

class Document;
class Model;
class DublinCore;
class Image;
class Item;
class SyndicationInfo;
class TextInput;
//@cond PRIVATE
typedef QSharedPointer<Document> DocumentPtr;
//@endcond

/**
 * Document implementation for RDF, representing an RSS 1.0 feed.
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT Document : public Syndication::SpecificDocument, public ResourceWrapper
{
    friend class ::Syndication::RDF::Model;
public:

    /**
     * creates a wrapper wrapping a null resource
     */
    Document();

    /**
     * creates a document by wrapping a channel resource
     *
     * @param resource the channel resource to wrap
     */
    explicit Document(ResourcePtr resource);

    /**
     * creates a copy of another document
     *
     * @param other the document to copy
     */
    Document(const Document &other);

    /**
     * destructor
     */
    virtual ~Document();

    /**
     * compares two documents. Two documents are equal if they wrap
     * the same resource. See ResourceWrapper::operator==()
     *
     * @param other the document to compare to
     */
    bool operator==(const Document &other) const;

    /**
     * assigns another document
     *
     * @param other the document to assign
     */
    Document &operator=(const Document &other);

    /**
     * Used by visitors for double dispatch. See DocumentVisitor
     * for more information.
     * @param visitor the visitor calling the method
     */
    virtual bool accept(DocumentVisitor *visitor);

    /**
     * returns whether this document is valid or not.
     * Invalid documents do not contain any useful
     * information.
     */
    bool isValid() const;

    /**
     * title of the feed (required)
     *
     * @return feed title as TODO: define format
     */
    QString title() const;

    /**
     * A brief description of the channel's content, function, source, etc.
     *
     * @return TODO: define format etc.
     */
    QString description() const;

    /**
     *  The URL to which an HTML rendering of the channel title will link,
     * commonly the parent site's home or news page.
     */
    QString link() const;

    /**
     * returns a dublin core description of the document.
     */
    DublinCore dc() const;

    /**
     * returns syndication information describing how often this feed
     * is updated.
     */
    SyndicationInfo syn() const;

    /**
     * list of items contained in this feed
     */
    QList<Item> items() const;

    /**
     * An image to be associated with an HTML rendering of the channel.
     */
    Image image() const;

    /**
     * An optional text input element associated with the channel
     */
    TextInput textInput() const;
//@cond PRIVATE
    /**
     * @internal
     * checks the format of titles and returns the results
     *
     * @param containsMarkup whether the heuristic found HTML markup in
     * titles
     */
    void getItemTitleFormatInfo(bool *containsMarkup) const;

    /**
     * @internal
     * checks the format of descriptions and returns the results
     *
     * @param containsMarkup whether the heuristic found HTML markup in
     * descriptions
     */
    void getItemDescriptionFormatInfo(bool *containsMarkup) const;
//@endcond PRIVATE

    /**
     * Returns a description of the document for debugging purposes.
     *
     * @return debug string
     */
    virtual QString debugInfo() const;

private:
    class Private;
    Private *const d;
};

} // namespace RDF
} // namespace Syndication

#endif //  SYNDICATION_RDF_DOCUMENT_H
