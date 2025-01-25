/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_ATOM_TOOLS_H
#define SYNDICATION_ATOM_TOOLS_H

class QString;

namespace Syndication
{
class ElementWrapper;

namespace Atom
{
/*!
 * \internal
 *
 * extracts the content of an atomTextConstruct. An atomTextConstruct is an element containing
 * either plain text, escaped html, or embedded XHTML.
 *
 * TODO: examples
 *
 * \a parent the parent element to extract from. E.g. an atom:entry element.
 *
 * \a tagname the child element of parent to extract from the text from.
 *
 * Atom namespace is assumed. Example: <atom:title>
 *
 * Returns the HTMLized version of the element content. If the content is
 * escaped HTML, the escaped markup is resolved. If it is XHTML, the XHTML
 * content is converted to a string. If it is plain text, characters like "<", ">", "&"
 * are escaped so the return string is valid HTML.
 */
QString extractAtomText(const Syndication::ElementWrapper &parent, const QString &tagname);

} // namespace Atom
} // namespace Syndication

#endif // SYNDICATION_ATOM_TOOLS_H
