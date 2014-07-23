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

#include "tools.h"
#include <constants.h>
#include <elementwrapper.h>

#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QString>

namespace Syndication
{
namespace RSS2
{
//@cond PRIVATE
QString extractContent(const ElementWrapper &wrapper)
{
    if (wrapper.isNull()) {
        return QString();
    }

    QList<QDomElement> list = wrapper.elementsByTagNameNS(contentNameSpace(), QLatin1String("encoded"));

    if (!list.isEmpty()) {
        return list.first().text().trimmed();
    }

    list = wrapper.elementsByTagNameNS(xhtmlNamespace(), QLatin1String("body"));

    if (!list.isEmpty()) {
        return ElementWrapper::childNodesAsXML(list.first()).trimmed();
    }

    list = wrapper.elementsByTagNameNS(xhtmlNamespace(), QLatin1String("div"));

    if (!list.isEmpty()) {
        return ElementWrapper::childNodesAsXML(list.first()).trimmed();
    }

    return QString();
}
//@endcond

} // namespace RSS2
} // namespace Syndication
