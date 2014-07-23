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

#include "image.h"

#include <QtCore/QString>

namespace Syndication
{

Image::~Image()
{
}

QString Image::debugInfo() const
{
    QString info;
    info += QLatin1String("# Image begin #####################\n");

    QString durl = url();

    if (!durl.isNull()) {
        info += QLatin1String("url: #") + durl + QLatin1String("#\n");
    }

    QString dtitle = title();

    if (!dtitle.isNull()) {
        info += QLatin1String("title: #") + dtitle + QLatin1String("#\n");
    }

    QString dlink = link();

    if (!dlink.isNull()) {
        info += QLatin1String("link: #") + dlink + QLatin1String("#\n");
    }

    QString ddescription = description();

    if (!ddescription.isNull()) {
        info += QLatin1String("description: #") + ddescription + QLatin1String("#\n");
    }

    int dheight = height();
    if (dheight > 0) {
        info += QLatin1String("height: #") + QString::number(height()) + QLatin1String("#\n");
    }

    int dwidth = width();
    if (dwidth > 0) {
        info += QLatin1String("width: #") + QString::number(width()) + QLatin1String("#\n");
    }
    info += QLatin1String("# Image end #######################\n");

    return info;
}

} // namespace Syndication
