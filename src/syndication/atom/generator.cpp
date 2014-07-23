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

#include "generator.h"
#include "constants.h"

#include <QtCore/QString>

namespace Syndication
{
namespace Atom
{

Generator::Generator() : ElementWrapper()
{
}

Generator::Generator(const QDomElement &element) : ElementWrapper(element)
{
}

QString Generator::uri() const
{
    return completeURI(attribute(QLatin1String("uri")));
}

QString Generator::name() const
{
    return text();
}

QString Generator::version() const
{
    return attribute(QLatin1String("version"));
}

QString Generator::debugInfo() const
{
    QString info;
    info += QLatin1String("### Generator: ###################\n");
    if (!name().isEmpty()) {
        info += QLatin1String("name: #") + name() + QLatin1String("#\n");
    }
    if (!uri().isEmpty()) {
        info += QLatin1String("uri: #") + uri() + QLatin1String("#\n");
    }
    if (!version().isEmpty()) {
        info += QLatin1String("version: #") + version() + QLatin1String("#\n");
    }
    info += QLatin1String("### Generator end ################\n");
    return info;
}

} // namespace Atom
} //namespace Syndication

