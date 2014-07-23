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
#include "rssvocab.h"
#include "statement.h"

#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

Image::Image() : ResourceWrapper()
{
}

Image::Image(ResourcePtr resource) : ResourceWrapper(resource)
{
}

Image::~Image()
{
}

QString Image::title() const
{
    return resource()->property(RSSVocab::self()->title())->asString();
}

QString Image::link() const
{
    return resource()->property(RSSVocab::self()->link())->asString();
}

QString Image::url() const
{
    return resource()->property(RSSVocab::self()->url())->asString();
}

QString Image::debugInfo() const
{
    QString info;
    info += QLatin1String("### Image: ###################\n");
    info += QLatin1String("url: #") + url() + QLatin1String("#\n");
    info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    info += QLatin1String("link: #") + link() + QLatin1String("#\n");
    info += QLatin1String("### Image end ################\n");
    return info;
}

} // namespace RDF
} // namespace Syndication
