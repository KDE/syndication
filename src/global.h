/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_GLOBAL_H
#define SYNDICATION_GLOBAL_H

#include "feed.h"

#include "syndication_export.h"

#include <QString>

/*!
 * \namespace Syndication
 * \inmodule Syndication
 * \inheaderfile Syndication/Global
 */
namespace Syndication
{
class DocumentSource;
template<class T>
class ParserCollection;

/*!
 * The default ParserCollection instance parsing
 * a DocumentSource into a Feed object.
 *
 * Use this to parse a local file or a otherwise
 * manually created DocumentSource object.
 *
 * To retrieve a feed from the web, use Loader instead.
 *
 * Example code:
 *
 * \code
 * ...
 * QFile someFile(somePath);
 * ...
 * DocumentSource src(someFile.readAll());
 * someFile.close();
 *
 * FeedPtr feed = parserCollection()->parse(src);
 *
 * if (feed)
 * {
 *     QString title = feed->title();
 *     QList<ItemPtr> items = feed->items();
 *     ...
 * }
 * \endcode
 */
SYNDICATION_EXPORT
ParserCollection<Feed> *parserCollection();

/*!
 * parses a document from a source and returns a new Feed object
 * wrapping the feed content.
 *
 * Shortcut for parserCollection()->parse().
 *
 * See ParserCollection::parse() for more details.
 *
 * \a src the document source to parse
 *
 * \a formatHint an optional hint which format to test first
 */
SYNDICATION_EXPORT
FeedPtr parse(const DocumentSource &src, const QString &formatHint = QString());

/*!
 * error code indicating fetching or parsing errors
 *
 * \value Success No error occurred, feed was fetched and parsed successfully
 * \value Aborted File downloading/parsing was aborted by the user
 * \value Timeout File download timed out
 * \value UnknownHost The hostname couldn't get resolved to an IP address
 * \value FileNotFound The host was contacted successfully, but reported a 404 error
 * \value OtherRetrieverError Retriever error not covered by the error codes above. This is returned if a custom DataRetriever was used. See the
 * retriever-specific status byte for more information on the occurred error.
 * \value InvalidXml The XML is invalid. This is returned if no parser accepts the source and the DOM document can't be parsed. It is not returned if the source
 * is not valid XML but a (non-XML) parser accepts it.
 * \value XmlNotAccepted The source is valid XML, but no parser accepted it.
 * \value InvalidFormat The source was accepted by a parser, but the actual parsing failed. As our parser implementations currently do not validate the source
 * ("parse what you can get"), this code will be rarely seen.
 */
enum ErrorCode {
    Success = 0,
    Aborted = 1,
    Timeout = 2,
    UnknownHost = 3,
    FileNotFound = 4,
    OtherRetrieverError = 5,
    InvalidXml = 6,
    XmlNotAccepted = 7,
    InvalidFormat = 8,
};

} // namespace Syndication

#endif // SYNDICATION_GLOBAL_H
