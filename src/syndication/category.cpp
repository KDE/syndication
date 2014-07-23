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

#include <QtCore/QString>

namespace Syndication
{

Category::~Category()
{
}

QString Category::debugInfo() const
{
    QString info;
    info += QLatin1String("# Category begin ##################\n");

    QString dterm = term();

    if (!dterm.isNull()) {
        info += QLatin1String("term: #") + dterm + QLatin1String("#\n");
    }

    QString dscheme = scheme();

    if (!dscheme.isNull()) {
        info += QLatin1String("scheme: #") + dscheme + QLatin1String("#\n");
    }

    QString dlabel = label();

    if (!dlabel.isNull()) {
        info += QLatin1String("label: #") + dlabel + QLatin1String("#\n");
    }

    info += QLatin1String("# Category end ####################\n");

    return info;
}

} // namespace Syndication
