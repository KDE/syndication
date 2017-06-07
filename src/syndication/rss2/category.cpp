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

#include "category.h"
#include "tools.h"

#include <QString>

namespace Syndication
{
namespace RSS2
{

Category::Category() : ElementWrapper()
{
}

Category::Category(const QDomElement &element) : ElementWrapper(element)
{
}
QString Category::category() const
{
    return text().simplified();
}

QString Category::domain() const
{
    return attribute(QStringLiteral("domain"));
}

QString Category::debugInfo() const
{
    QString info;
    info += QLatin1String("### Category: ###################\n");
    if (!category().isNull()) {
        info += QLatin1String("category: #") + category() + QLatin1String("#\n");
    }
    if (!domain().isNull()) {
        info += QLatin1String("domain: #") + domain() + QLatin1String("#\n");
    }
    info += QLatin1String("### Category end ################\n");
    return info;
}

} // namespace RSS2
} // namespace Syndication
