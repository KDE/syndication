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

#ifndef SYNDICATION_RSS2_DOCUMENT_H
#define SYNDICATION_RSS2_DOCUMENT_H

#include <syndication/specificdocument.h>
#include <syndication/elementwrapper.h>

#include <ctime>

class QDomDocument;
class QDomElement;
class QString;

template <class T> class QList;
template <class T> class QSet;

namespace Syndication
{
namespace RSS2
{

class Category;
class Cloud;
class Document;
class Image;
class Item;
class TextInput;
typedef boost::shared_ptr<Document> DocumentPtr;

/**
 * document implementation, representing an RSS feed from the 0.91-0.94/2.0
 * family.
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT Document : public Syndication::SpecificDocument,
    public Syndication::ElementWrapper
{
public:

    /**
     * Parses an RSS2 document from an XML document.
     * TODO: More on supported formats etc.
     *
     * @param document The dom document to parse the document from
     * @return the document parsed from XML, or an invalid
     * document if parsing failed.
     */
    static Document fromXML(const QDomDocument &document);

    /**
     * Default constructor, creates a null object, for which
     * isNull() is @c true and  isValid() is @c false.
     */
    Document();

    /**
     * copy constructor
     */
    Document(const Document &other);

    /**
     * destructor
     */
    virtual ~Document();

    /**
     * assigns another document. As the d pointer is shared,
     * this is a cheap operation.
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
     * The title of the channel.
     *
     * @return title TODO: more on escaping/HTML
     */
    QString title() const;

    /**
     * The URL to the HTML website corresponding to the channel.
     *
     * @return TODO
     */
    QString link() const;

    /**
     * Phrase or sentence describing the channel.
     *
     * @return TODO
     */
    QString description() const;

    /**
     * the items contained in this document
     */
    QList<Item> items() const;

    /**
     *
     * @return TODO
     */
    QString language() const;

    /**
     *
     * Copyright notice for content in the channel.
     * This method returns the content of the @c &lt;copyright>
     * element. If @c &lt;copyright> is not available, the method returns
     * @c &lt;dc:rights> instead, if available.
     *
     * @return copyright information, or a null string if not set
     */
    QString copyright() const;

    /**
     * Email address for person responsible for editorial content.
     *
     * @return editor's email address, or a null string if not set
     */
    QString managingEditor() const;

    /**
     * Email address for person responsible for technical issues relating
     * to channel.
     *
     * @return web master's email address, or a null string if not
     */
    QString webMaster() const;

    /**
     * The publication date for the content in the channel. For example,
     * the New York Times publishes on a daily basis, the publication date
     * flips once every 24 hours. That's when the pubDate of the channel
     * changes.
     * This method returns the content of the @c &lt;pubDate> element. If
     * @c &lt;pubDate> is not available, the method returns
     * @c &lt;dc:date> instead, if available.
     *
     * @return the publication date, or 0 if no date was specified or
     * parsing failed
     */
    time_t pubDate() const;

    /**
     * The last time the content of the channel changed.
     *
     * @return the last build date, or 0 if no date was specified or parsing
     * failed
     */
    time_t lastBuildDate() const;

    /**
     * Specifies one or more categories that the channel belongs to.
     *
     * @return TODO
     */
    QList<Category> categories() const;

    /**
     * A string indicating the program used to generate the channel.
     *
     * @return description of the generator program, or a null string if
     * not set
     */
    QString generator() const;

    /**
     * A URL that points to the documentation for the format used in the
     * RSS file. It's probably a pointer to the RSS specification.
     * It's for people who might stumble across an RSS file on a Web server
     * 25 years from now and wonder what it is.
     *
     * @return URL pointing to the format specification, or a null string if
     * not set
     */
    QString docs() const;

    /**
     * Allows processes to register with a cloud to be notified of updates
     * to the channel, implementing a lightweight publish-subscribe
     * protocol for RSS feeds.
     *
     * @return cloud information, or a null object if not set
     */
    Cloud cloud() const;

    /**
     * ttl stands for time to live. It's a number of minutes that indicates
     * how long a channel can be cached before refreshing from the source.
     *
     * @return the "time to live" in minutes, or 0 if not set
     */
    int ttl() const;

    /**
     * Specifies a GIF, JPEG or PNG image that can be displayed with the
     * channel.
     *
     * @return the image, or a null object if not set
     */
    Image image() const;

    /**
     * Specifies a text input box that can be displayed with the channel.
     *
     * @return the text input, or a null object if not set
     */
    TextInput textInput() const;

    /**
     * Contains a set of hours (from 0 to 23), time in GMT, when the
     * channel is not updated.
     */
    QSet<int> skipHours() const;

    /** days of week, used for skip days */
    enum DayOfWeek {

        Monday = 0, /**< self-explanatory */
        Tuesday = 1, /**< self-explanatory */
        Wednesday = 2, /**< self-explanatory */
        Thursday = 3, /**< self-explanatory */
        Friday = 4, /**< self-explanatory */
        Saturday = 5, /**< self-explanatory */
        Sunday = 6 /**< self-explanatory */
    };

    /**
     * A set of week days where aggregators shouldn't read the channel.
     *
     */
    QSet<DayOfWeek> skipDays() const;

    /**
     * returns all child elements of this document not covered by this class.
     * You can use this to access additional metadata from RSS extensions.
     */
    QList<QDomElement> unhandledElements() const;

    /**
     * Returns a description of the object and its children for
     * debugging purposes.
     *
     * @return debug string
     */
    QString debugInfo() const;

    //@cond PRIVATE
    /**
     * @internal
     * checks the format of title elements and returns the results
     * @param isCDATA whether the titles are encapsulated in CDATA
     * @param containsMarkup whether the heuristic found HTML markup in
     * titles
     */
    void getItemTitleFormatInfo(bool *isCDATA, bool *containsMarkup) const;

    /**
     * @internal
     * checks the format of title elements and returns the results
     * @param isCDATA whether the descriptions are encapsulated in CDATA
     * @param containsMarkup whether the heuristic found HTML markup in
     * descriptions
     */
    void getItemDescriptionFormatInfo(bool *isCDATA, bool *containsMarkup) const;
    //@endcond

private:
    /**
     * @internal
     * private constructor, used by fromXML()
     * TODO: remove fromXML(), make this one private
     */
    explicit Document(const QDomElement &element);

    class DocumentPrivate;
    boost::shared_ptr<DocumentPrivate> d;

};

} // namespace RSS2
} // namespace Syndication

#endif // SYNDICATION_RSS2_DOCUMENT_H
