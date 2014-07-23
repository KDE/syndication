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

#include "category.h"
#include "constants.h"

#include <QtXml/QDomElement>
#include <QtCore/QString>

namespace Syndication
{
namespace Atom
{

Category::Category() : ElementWrapper()
{
}

Category::Category(const QDomElement &element) : ElementWrapper(element)
{
}

QString Category::term() const
{
    return attribute(QLatin1String("term"));
}

QString Category::scheme() const
{
    // NOTE: The scheme IRI is not completed by purpose.
    // According to Atom spec, it must be an absolute IRI.
    // If this is a problem with real-world feeds, it might be changed.
    return attribute(QLatin1String("scheme"));
}

QString Category::label() const
{
    return attribute(QLatin1String("label"));
}

QString Category::debugInfo() const
{
    QString info;
    info += QLatin1String("### Category: ###################\n");
    info += QLatin1String("term: #") + term() + QLatin1String("#\n");
    if (!scheme().isEmpty()) {
        info += QLatin1String("scheme: #") + scheme() + QLatin1String("#\n");
    }
    if (!label().isEmpty()) {
        info += QLatin1String("label: #") + label() + QLatin1String("#\n");
    }
    info += QLatin1String("### Category end ################\n");

    return info;
}

} // namespace Atom
} //namespace Syndication
