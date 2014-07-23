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

#include "image.h"

#include <QtCore/QString>

namespace Syndication
{
namespace RSS2
{

Image::Image() : ElementWrapper()
{
}

Image::Image(const QDomElement &element) : ElementWrapper(element)
{
}

QString Image::url() const
{
    return extractElementTextNS(QString(), QLatin1String("url"));
}

QString Image::title() const
{
    return extractElementTextNS(QString(), QLatin1String("title"));

}

QString Image::link() const
{
    return extractElementTextNS(QString(), QLatin1String("link"));

}

uint Image::width() const
{
    QString text;
    bool ok;
    uint c;

    text = extractElementTextNS(QString(), QLatin1String("width"));
    c = text.toUInt(&ok);
    return ok ? c : 88; // set to default if not parsable
}

uint Image::height() const
{
    QString text;
    bool ok;
    uint c;

    text = extractElementTextNS(QString(), QLatin1String("height"));
    c = text.toUInt(&ok);
    return ok ? c : 31; // set to default if not parsable
}

QString Image::description() const
{
    return extractElementTextNS(QString(), QLatin1String("description"));
}

QString Image::debugInfo() const
{
    QString info;
    info += QLatin1String("### Image: ###################\n");
    if (!title().isNull()) {
        info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    }
    if (!link().isNull()) {
        info += QLatin1String("link: #") + link() + QLatin1String("#\n");
    }
    if (!description().isNull()) {
        info += QLatin1String("description: #") + description() + QLatin1String("#\n");
    }
    if (!url().isNull()) {
        info += QLatin1String("url: #") + url() + QLatin1String("#\n");
    }
    info += QLatin1String("width: #") + QString::number(width()) + QLatin1String("#\n");
    info += QLatin1String("height: #") + QString::number(height()) + QLatin1String("#\n");
    info += QLatin1String("### Image end ################\n");
    return info;
}

} // namespace RSS2
} //namespace Syndication
