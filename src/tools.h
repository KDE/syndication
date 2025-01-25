/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_TOOLS_H
#define SYNDICATION_TOOLS_H

#include "person.h"
#include "syndication_export.h"

#include <QString>

class QByteArray;
class QString;

namespace Syndication
{
/*!
 * date formats supported by date parsers
 *
 * \value ISODate ISO 8601 extended format. (date: "2003-12-13",datetime: "2003-12-13T18:30:02.25", datetime with timezone: "2003-12-13T18:30:02.25+01:00")
 * \value RFCDate RFC 822. (e.g. "Sat, 07 Sep 2002 00:00:01 GMT")
 */
enum DateFormat {
    ISODate,
    RFCDate,
};

/*!
 * parses a date string in ISO 8601 extended format.
 * (date: "2003-12-13",datetime: "2003-12-13T18:30:02.25",
 * datetime with timezone: "2003-12-13T18:30:02.25+01:00")
 *
 * \a str a string in ISO 8601 format
 *
 * Returns parsed date in seconds since epoch, 0 if no date could
 * be parsed from the string.
 */
SYNDICATION_EXPORT
uint parseISODate(const QString &str);

/*!
 * parses a date string as defined in RFC 822.
 * (Sat, 07 Sep 2002 00:00:01 GMT)
 *
 * \a str a string in RFC 822 format
 *
 * Returns parsed date in seconds since epoch, 0 if no date could
 * be parsed from the string.
 */
SYNDICATION_EXPORT
uint parseRFCDate(const QString &str);

/*!
 * parses a date string in ISO (see parseISODate()) or RFC 822 (see
 * parseRFCDate()) format.
 *
 * It tries both parsers and returns the first valid parsing result found (or 0
 * otherwise).
 *
 * To speed up parsing, you can give a hint which format you expect.
 * The method will try the corresponding parser first then.
 *
 * \a str a date string
 *
 * \a hint the expected format
 *
 * Returns parsed date in seconds since epoch, 0 if no date could
 * be parsed from the string.
 */
SYNDICATION_EXPORT
uint parseDate(const QString &str, DateFormat hint = RFCDate);

/*!
 * \internal
 * returns a string representation of a datetime.
 * this is used internally to create debugging output.
 *
 * \a date the date to convert
 *
 * Returns string representation of the date, or a null string if
 * \a date is 0
 */
SYNDICATION_EXPORT
QString dateTimeToString(uint date);

/*!
 * resolves entities to respective unicode chars.
 *
 * \a str a string
 */
SYNDICATION_EXPORT
QString resolveEntities(const QString &str);
/*!
 * replaces the characters <, >, &, ", '
 * with &lt; &gt; &amp;, &quot; &apos;.
 *
 * \a str the string to escape
 */
SYNDICATION_EXPORT
QString escapeSpecialCharacters(const QString &str);

/*!
 * replaces newlines ("\n") by <br/>
 *
 * \a str string to convert
 */
SYNDICATION_EXPORT
QString convertNewlines(const QString &str);

/*!
 * converts a plain text string to HTML
 *
 * \a plainText a string in plain text.
 */
SYNDICATION_EXPORT
QString plainTextToHtml(const QString &plainText);

/*!
 * converts a HTML string to plain text
 *
 * \a html string in HTML format
 *
 * Returns stripped text
 */
SYNDICATION_EXPORT
QString htmlToPlainText(const QString &html);

/*!
 * guesses whether a string contains plain text or HTML
 *
 * \a str the string in unknown format
 *
 * Returns \c true if the heuristic thinks it's HTML, \c false
 * if thinks it is plain text
 */
SYNDICATION_EXPORT
bool isHtml(const QString &str);

/*!
 * guesses whether a string contains (HTML) markup or not. This
 * implements not an exact check for valid HTML markup, but a
 * simple (and relatively fast) heuristic.
 *
 * \a str the string that might or might not contain markup
 *
 * Returns \c true if the heuristic thinks it contains markup, \c false
 * if thinks it is markup-free plain text
 */
SYNDICATION_EXPORT
bool stringContainsMarkup(const QString &str);

/*!
 * Ensures HTML formatting for a string.
 *
 * guesses via isHtml() if \a str contains HTML or plain text, and returns
 * plainTextToHtml(str) if it thinks it is plain text, or the unmodified \a str
 * otherwise.
 *
 * \a str a string with unknown content
 * Returns string as HTML (as long as the heuristics work)
 */
SYNDICATION_EXPORT
QString normalize(const QString &str);

/*!
 * normalizes a string based on feed-wide properties of tag content.
 * It is based on the assumption that all items in a feed encode their
 * title/description content in the same way (CDATA or not, plain text
 * vs. HTML). isCDATA and containsMarkup are determined once by the feed,
 * and then passed to this method.
 *
 * The returned string contains HTML, with special characters <, >,
 * &, ", and ' escaped, and all other entities resolved.
 * Whitespace is collapsed, relevant whitespace is replaced by respective
 * HTML tags (<br/>).
 *
 * \a str a string
 *
 * \a isCDATA whether the feed uses CDATA for the tag \a str was read from
 *
 * \a containsMarkup whether the feed uses HTML markup in the
 *        tag \a str was read from.
 *
 * Returns string as HTML (as long as the heuristics work)
 */
SYNDICATION_EXPORT
QString normalize(const QString &str, bool isCDATA, bool containsMarkup);

/*!
 * Parses a person object from a string by identifying name and email address
 * in the string. Currently detected variants are:
 * "foo@bar.com", "Foo", "Foo <foo@bar.com>", "foo@bar.com (Foo)".
 *
 * \a str the string to parse the person from.
 *
 * Returns a Person object containing the parsed information.
 */
SYNDICATION_EXPORT
PersonPtr personFromString(const QString &str);

/*!
 * \internal
 * calculates a hash value for a string
 */
unsigned int calcHash(const QString &str);

/*!
 * \internal
 * calculates a hash value for a byte array
 */
unsigned int calcHash(const QByteArray &array);

/*!
 * \internal
 * calculates a md5 checksum for a string
 */
QString calcMD5Sum(const QString &str);

/*!
 * \internal
 * used internally to represent element types
 */
struct ElementType {
    ElementType(const QString &localnamep,
                const QString &nsp = QString()); // implicit

    bool operator==(const ElementType &other) const;

    QString ns;
    QString localname;
};

} // namespace Syndication

#endif // SYNDICATION_TOOLS_H
