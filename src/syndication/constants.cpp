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

#include "constants.h"

#include <QtCore/QString>

namespace Syndication
{

QString xmlNamespace()
{
    return QLatin1String("http://www.w3.org/XML/1998/namespace");
}

QString xhtmlNamespace()
{
    return QLatin1String("http://www.w3.org/1999/xhtml");
}

QString contentNameSpace()
{
    return QLatin1String("http://purl.org/rss/1.0/modules/content/");
}

QString dublinCoreNamespace()
{
    return QLatin1String("http://purl.org/dc/elements/1.1/");
}

QString itunesNamespace()
{
    return QLatin1String("http://www.itunes.com/dtds/podcast-1.0.dtd");
}

QString commentApiNamespace()
{
    return QLatin1String("http://wellformedweb.org/CommentAPI/");
}

QString slashNamespace()
{
    return QLatin1String("http://purl.org/rss/1.0/modules/slash/");
}

} // namespace Syndication
