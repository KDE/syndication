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

#ifndef SYNDICATION_RSS2_TOOLS_P_H
#define SYNDICATION_RSS2_TOOLS_P_H

class QString;
template <class T> class QList;

namespace Syndication
{

class ElementWrapper;

namespace RSS2
{

/**
 * @internal
 * extracts encoded content from XHTML, content:encoded and friends
 *
 * @param parent the parent node, e.g. a channel or item element
 * @return the content as HTML (see Item::content() for details)
 */
QString extractContent(const ElementWrapper &parent);

} // RSS2
} // Syndication

#endif // SYNDICATION_RSS2_TOOLS_P_H
