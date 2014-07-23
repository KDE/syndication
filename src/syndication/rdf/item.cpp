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

#include "item.h"
#include "contentvocab.h"
#include "document.h"
#include "dublincore.h"
#include "model.h"
#include "rssvocab.h"
#include "statement.h"

#include <specificitemvisitor.h>
#include <tools.h>

#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

class Item::Private
{
public:
    DocumentPtr doc;
};

Item::Item() : ResourceWrapper(), d(new Private)
{
}

Item::Item(ResourcePtr resource, DocumentPtr doc) : ResourceWrapper(resource),
    d(new Private)
{
    d->doc = doc;
}

Item::Item(const Item &other) : ResourceWrapper(other),
    SpecificItem(other),
    d(new Private)
{
    *d = *(other.d);
}

Item::~Item()
{
    delete d;
}

Item &Item::operator=(const Item &other)
{
    ResourceWrapper::operator=(other);
    *d = *(other.d);
    return *this;
}

bool Item::operator==(const Item &other) const
{
    return ResourceWrapper::operator==(other);
}

QString Item::title() const
{
    if (!d->doc) {
        return originalTitle();
    }

    bool containsMarkup = false;
    d->doc->getItemTitleFormatInfo(&containsMarkup);

    return normalize(originalTitle(), false, containsMarkup);
}

QString Item::description() const
{
    if (!d->doc) {
        return originalDescription();
    }

    bool containsMarkup = false;
    d->doc->getItemDescriptionFormatInfo(&containsMarkup);

    return normalize(originalDescription(), false, containsMarkup);
}

QString Item::link() const
{
    return resource()->property(RSSVocab::self()->link())->asString();
}

DublinCore Item::dc() const
{
    return DublinCore(resource());
}

QString Item::encodedContent() const
{
    return resource()->property(ContentVocab::self()->encoded())->asString();
}

QString Item::originalTitle() const
{
    return resource()->property(RSSVocab::self()->title())->asString();
}

QString Item::originalDescription() const
{
    return resource()->property(RSSVocab::self()->description())->asString();
}

QString Item::debugInfo() const
{
    QString info;
    info += QLatin1String("### Item: ###################\n");
    info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    info += QLatin1String("link: #") + link() + QLatin1String("#\n");
    info += QLatin1String("description: #") + description() + QLatin1String("#\n");
    info += QLatin1String("content:encoded: #") + encodedContent() + QLatin1String("#\n");
    info += dc().debugInfo();
    info += QLatin1String("### Item end ################\n");
    return info;
}

bool Item::accept(SpecificItemVisitor *visitor)
{
    return visitor->visitRDFItem(this);
}

} // namespace RDF
} // namespace Syndication
