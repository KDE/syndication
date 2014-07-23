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

#include "person.h"
#include "constants.h"

#include <QtCore/QString>

namespace Syndication
{
namespace Atom
{

Person::Person() : ElementWrapper()
{
}

Person::Person(const QDomElement &element) : ElementWrapper(element)
{
}

QString Person::name() const
{
    return extractElementTextNS(atom1Namespace(),
                                QLatin1String("name"));
}

QString Person::uri() const
{

    return completeURI(extractElementTextNS(atom1Namespace(),
                                            QLatin1String("uri")));
}

QString Person::email() const
{
    return extractElementTextNS(atom1Namespace(),
                                QLatin1String("email"));
}

QString Person::debugInfo() const
{
    QString info;
    info += QLatin1String("### Person: ###################\n");
    info += QLatin1String("name: #") + name() + QLatin1String("#\n");
    info += QLatin1String("email: #") + email() + QLatin1String("#\n");
    info += QLatin1String("uri: #") + uri() + QLatin1String("#\n");
    info += QLatin1String("### Person end ################\n");

    return info;
}

} // namespace Atom
} //namespace Syndication
