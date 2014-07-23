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

#include "rssvocab.h"
#include "property.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace Syndication
{
namespace RDF
{

class RSSVocab::RSSVocabPrivate
{
public:

    QString namespaceURI;
    PropertyPtr title;
    PropertyPtr link;
    PropertyPtr description;
    PropertyPtr name;
    PropertyPtr url;
    PropertyPtr image;
    ResourcePtr channel;
    ResourcePtr item;
    PropertyPtr items;
    PropertyPtr textinput;

    static RSSVocab *sSelf;
    static void cleanupRSSVocab()
    {
        delete sSelf;
        sSelf = 0;
    }
};
RSSVocab *RSSVocab::RSSVocabPrivate::sSelf = 0;

RSSVocab::RSSVocab() : d(new RSSVocabPrivate)
{
    QString ns = QLatin1String("http://purl.org/rss/1.0/");

    d->namespaceURI = ns;

    d->title = PropertyPtr(new Property(ns + QLatin1String("title")));
    d->link = PropertyPtr(new Property(ns + QLatin1String("link")));
    d->description = PropertyPtr(new Property(ns + QLatin1String("description")));
    d->name = PropertyPtr(new Property(ns + QLatin1String("name")));
    d->url = PropertyPtr(new Property(ns + QLatin1String("url")));
    d->image = PropertyPtr(new Property(ns + QLatin1String("image")));
    d->textinput = PropertyPtr(new Property(ns + QLatin1String("textinput")));
    d->items = PropertyPtr(new Property(ns + QLatin1String("items")));
    d->channel = ResourcePtr(new Resource(ns + QLatin1String("channel")));
    d->item = ResourcePtr(new Resource(ns + QLatin1String("item")));
}

RSSVocab::~RSSVocab()
{
    delete d;
}

RSSVocab *RSSVocab::self()
{
    static RSSVocabPrivate p;
    if (!p.sSelf) {
        p.sSelf = new RSSVocab;
        qAddPostRoutine(RSSVocabPrivate::cleanupRSSVocab);
    }
    return p.sSelf;
}

const QString &RSSVocab::namespaceURI() const
{
    return d->namespaceURI;
}

PropertyPtr RSSVocab::title() const
{
    return d->title;
}

PropertyPtr RSSVocab::description() const
{
    return d->description;
}

PropertyPtr RSSVocab::link() const
{
    return d->link;
}

PropertyPtr RSSVocab::name() const
{
    return d->name;
}

PropertyPtr RSSVocab::url() const
{
    return d->url;
}

PropertyPtr RSSVocab::image() const
{
    return d->image;
}

PropertyPtr RSSVocab::textinput() const
{
    return d->textinput;
}

PropertyPtr RSSVocab::items() const
{
    return d->items;
}

ResourcePtr RSSVocab::item() const
{
    return d->item;
}

ResourcePtr RSSVocab::channel() const
{
    return d->channel;
}

class RSS09Vocab::RSS09VocabPrivate
{
public:

    QString namespaceURI;
    PropertyPtr title;
    PropertyPtr link;
    PropertyPtr description;
    PropertyPtr name;
    PropertyPtr url;
    PropertyPtr image;
    ResourcePtr channel;
    ResourcePtr item;
    PropertyPtr textinput;
    QStringList properties;
    QStringList classes;

    static RSS09Vocab *sSelf;
    static void cleanupRSS09Vocab()
    {
        delete sSelf;
        sSelf = 0;
    }
};
RSS09Vocab *RSS09Vocab::RSS09VocabPrivate::sSelf = 0;

RSS09Vocab::RSS09Vocab() : d(new RSS09VocabPrivate)
{
    QString ns = QLatin1String("http://my.netscape.com/rdf/simple/0.9/");

    d->namespaceURI = ns;

    d->title = PropertyPtr(new Property(ns + QLatin1String("title")));
    d->properties.append(d->title->uri());
    d->link = PropertyPtr(new Property(ns + QLatin1String("link")));
    d->properties.append(d->link->uri());
    d->description = PropertyPtr(new Property(ns + QLatin1String("description")));
    d->properties.append(d->description->uri());
    d->name = PropertyPtr(new Property(ns + QLatin1String("name")));
    d->properties.append(d->name->uri());
    d->url = PropertyPtr(new Property(ns + QLatin1String("url")));
    d->properties.append(d->url->uri());
    d->image = PropertyPtr(new Property(ns + QLatin1String("image")));
    d->properties.append(d->image->uri());
    d->textinput = PropertyPtr(new Property(ns + QLatin1String("textinput")));
    d->properties.append(d->textinput->uri());
    d->item = ResourcePtr(new Resource(ns + QLatin1String("item")));
    d->classes.append(d->item->uri());
    d->channel = ResourcePtr(new Resource(ns + QLatin1String("channel")));
    d->classes.append(d->channel->uri());
}

RSS09Vocab::~RSS09Vocab()
{
    delete d;
}

RSS09Vocab *RSS09Vocab::self()
{
    if (!RSS09VocabPrivate::sSelf) {
        RSS09VocabPrivate::sSelf = new RSS09Vocab;
        qAddPostRoutine(RSS09VocabPrivate::cleanupRSS09Vocab);
    }
    return RSS09VocabPrivate::sSelf;
}

const QString &RSS09Vocab::namespaceURI() const
{
    return d->namespaceURI;
}

PropertyPtr RSS09Vocab::title() const
{
    return d->title;
}

PropertyPtr RSS09Vocab::description() const
{
    return d->description;
}

PropertyPtr RSS09Vocab::link() const
{
    return d->link;
}

PropertyPtr RSS09Vocab::name() const
{
    return d->name;
}

PropertyPtr RSS09Vocab::url() const
{
    return d->url;
}

PropertyPtr RSS09Vocab::image() const
{
    return d->image;
}

PropertyPtr RSS09Vocab::textinput() const
{
    return d->textinput;
}

ResourcePtr RSS09Vocab::item() const
{
    return d->item;
}

ResourcePtr RSS09Vocab::channel() const
{
    return d->channel;
}

QStringList RSS09Vocab::classes() const
{
    return d->classes;
}

QStringList RSS09Vocab::properties() const
{
    return d->properties;
}

} // namespace RDF
} // namespace Syndication
