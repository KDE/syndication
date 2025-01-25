/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_ATOM_CONTENT_H
#define SYNDICATION_ATOM_CONTENT_H

#include <syndication/elementwrapper.h>

#include <QString>

class QByteArray;
class QDomElement;

namespace Syndication
{
namespace Atom
{
/*!
 * \class Syndication::Atom::Content
 * \inmodule Syndication
 * \inheaderfile Syndication/Atom/Content
 *
 * \brief The content element either contains or links the content of an entry.
 *
 * The content is usually plain text or HTML, but arbitrary XML or binary
 * content are also possible. If isContained() is false, the content is
 * not contained in the feed source, but linked.
 */
class SYNDICATION_EXPORT Content : public ElementWrapper
{
public:
    /*!
     * format of the content.
     *
     * \value PlainText the content is plain text (i.e. "<", ">" etc. are text, not markup
     * \value EscapedHTML the content is escaped HTML, (i.e., "<", ">" etc. are markup)
     * \value XML the content is embedded XML
     * \value Binary the content is base64-encoded binary content
     */
    enum Format {
        PlainText,
        EscapedHTML,
        XML,
        Binary,
    };

    /*!
     * maps a mimetype to Format enum according to the Atom 1.0
     * specification
     *
     * \a type a valid mimetype, or one of "text", "html", "xhtml"
     *
     * \a src content source, see src() for details.
     */
    static Format mapTypeToFormat(const QString &type, const QString &src = QString());

    /*!
     * creates a null content object.
     */
    Content();

    /*!
     * creates a Content object wrapping an atom:content element.
     *
     * \a element a DOM element, should be a atom:content element
     * (although not enforced), otherwise this object will not parse
     * anything useful
     */
    explicit Content(const QDomElement &element);

    /*!
     * creates a copy of another Content object
     *
     * \a other the content object to copy
     */
    Content(const Content &other);

    ~Content() override;

    /*!
     * assigns another content objecct
     *
     * \a other the Content object to assign
     */
    Content &operator=(const Content &other);

    /*!
     * the type of the content. This is either "text" (plain text),
     * "html" (escaped HTML), "xhtml" (embedded XHTML) or a mime type
     *
     * Returns the content type. If no type is specified, "text" (the
     * default) is returned.
     */
    Q_REQUIRED_RESULT QString type() const;

    /*!
     * If src() is set, the content of this entry is not contained in the
     * feed source, but available on the net.
     * src() then contains a URL (more precise: IRI reference) linking to
     * remote content.
     * If src is provided, type() should contain a mimetype, instead of "text",
     * "html" or "xhtml".
     *
     * Returns a null string if the content is contained in the feed
     * source, or a URL linking to the remote content
     */
    Q_REQUIRED_RESULT QString src() const;

    /*!
     * returns the content as string. If the content format is Text, the
     * returned string contains the text as HTML.
     * If the content is embedded XML, the XML is returned as string.
     *
     * Returns a string representation of the content, or a null string if
     * the content is either binary content or not contained but linked
     * (see isContained())
     */
    Q_REQUIRED_RESULT QString asString() const;

    /*!
     * Returns byte array containing the embedded binary data, or
     * an empty array if the content is not in binary format
     */
    Q_REQUIRED_RESULT QByteArray asByteArray() const;

    /*!
     * returns the content format
     */
    Q_REQUIRED_RESULT Format format() const;

    /*!
     * returns whether the content is contained in the feed source,
     * or not. If it is not contained, src() provides a URL to the
     * content.
     */
    Q_REQUIRED_RESULT bool isContained() const;

    /*!
     * returns whether the content is embedded XML.
     * Use element() to access the DOM tree, or asString() to get the XML
     * as string.
     */
    Q_REQUIRED_RESULT bool isXML() const;

    /*!
     * returns whether the content is binary content or not.
     * Use asByteArray() to access it.
     */
    Q_REQUIRED_RESULT bool isBinary() const;

    /*!
     * returns whether the content is plain text or not.
     * Use asString() to access it.
     */
    Q_REQUIRED_RESULT bool isPlainText() const;

    /*!
     * returns whether the content is escaped HTML or not
     * Use asString() to access it
     */
    Q_REQUIRED_RESULT bool isEscapedHTML() const;

    /*!
     * returns a description of the content object
     * for debugging purposes
     */
    Q_REQUIRED_RESULT QString debugInfo() const;

private:
    class ContentPrivate;
    QSharedPointer<ContentPrivate> d;
};

} // namespace Atom
} // namespace Syndication

#endif // SYNDICATION_ATOM_CONTENT_H
