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

#include "enclosure.h"

#include <QString>

namespace Syndication
{

Enclosure::~Enclosure()
{
}

QString Enclosure::debugInfo() const
{
    QString info;
    info += QLatin1String("# Enclosure begin #################\n");

    QString durl = url();

    if (!durl.isNull()) {
        info += QLatin1String("url: #") + durl + QLatin1String("#\n");
    }

    QString dtitle = title();

    if (!dtitle.isNull()) {
        info += QLatin1String("title: #") + dtitle + QLatin1String("#\n");
    }

    QString dtype = type();

    if (!dtype.isNull()) {
        info += QLatin1String("type: #") + dtype + QLatin1String("#\n");
    }

    int dlength = length();

    if (dlength != 0) {
        info += QLatin1String("length: #") + QString::number(dlength) + QLatin1String("#\n");
    }

    uint dduration = duration();

    if (dduration != 0) {
        int hours = dduration / 3600;
        int minutes = (dduration - hours * 3600) / 60;
        int seconds = dduration - hours * 3600 - minutes * 60;
        info += QString::fromLatin1("duration: #%1 (%2:%3:%4)#\n").arg(dduration).arg(hours).arg(minutes).arg(seconds);
    }

    info += QLatin1String("# Enclosure end ###################\n");

    return info;
}

} // namespace Syndication
