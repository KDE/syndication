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

#include "link.h"
#include "constants.h"

#include <QtCore/QString>

namespace Syndication
{
namespace Atom
{

Link::Link() : ElementWrapper()
{
}

Link::Link(const QDomElement &element) : ElementWrapper(element)
{
}

QString Link::href() const
{
    return completeURI(attribute(QLatin1String("href")));
}

QString Link::rel() const
{
    //"alternate" is default
    return attribute(QLatin1String("rel"), QLatin1String("alternate"));
}

QString Link::type() const
{
    return attribute(QLatin1String("type"));
}

QString Link::hrefLanguage() const
{
    return attribute(QLatin1String("hreflang"));
}

QString Link::title() const
{
    return attribute(QLatin1String("title"));
}

uint Link::length() const
{
    QString lengthStr = attribute(QLatin1String("length"));

    bool ok;
    uint c = lengthStr.toUInt(&ok);
    return ok ? c : 0;
}

QString Link::debugInfo() const
{
    QString info;
    info += QLatin1String("### Link: ###################\n");
    if (!title().isEmpty()) {
        info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    }
    if (!href().isEmpty()) {
        info += QLatin1String("href: #") + href() + QLatin1String("#\n");
    }
    if (!rel().isEmpty()) {
        info += QLatin1String("rel: #") + rel() + QLatin1String("#\n");
    }
    if (!type().isEmpty()) {
        info += QLatin1String("type: #") + type() + QLatin1String("#\n");
    }
    if (length() != 0) {
        info += QLatin1String("length: #") + QString::number(length()) + QLatin1String("#\n");
    }
    if (!hrefLanguage().isEmpty()) {
        info += QLatin1String("hrefLanguage: #") + hrefLanguage() + QLatin1String("#\n");
    }
    info += QLatin1String("### Link end ################\n");
    return info;
}

} // namespace Atom
} //namespace Syndication
