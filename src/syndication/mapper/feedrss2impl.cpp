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

#include "feedrss2impl.h"
#include "categoryrss2impl.h"
#include "imagerss2impl.h"
#include "itemrss2impl.h"
#include <personimpl.h>
#include <rss2/category.h>
#include <rss2/item.h>

#include <QtCore/QList>
#include <QtCore/QMultiMap>
#include <QtCore/QString>
#include <QtXml/QDomElement>

namespace Syndication
{

FeedRSS2Impl::FeedRSS2Impl(Syndication::RSS2::DocumentPtr doc) : m_doc(doc)
{
}

Syndication::SpecificDocumentPtr FeedRSS2Impl::specificDocument() const
{
    return m_doc;
}

QList<Syndication::ItemPtr> FeedRSS2Impl::items() const
{
    QList<ItemPtr> items;
    QList<Syndication::RSS2::Item> entries = m_doc->items();
    QList<Syndication::RSS2::Item>::ConstIterator it = entries.constBegin();
    QList<Syndication::RSS2::Item>::ConstIterator end = entries.constEnd();

    for (; it != end; ++it) {
        ItemRSS2ImplPtr item(new ItemRSS2Impl(*it));
        items.append(item);
    }

    return items;
}

QList<Syndication::CategoryPtr> FeedRSS2Impl::categories() const
{
    QList<CategoryPtr> categories;
    QList<Syndication::RSS2::Category> entries = m_doc->categories();
    QList<Syndication::RSS2::Category>::ConstIterator it = entries.constBegin();
    QList<Syndication::RSS2::Category>::ConstIterator end = entries.constEnd();

    for (; it != end; ++it) {
        CategoryRSS2ImplPtr item(new CategoryRSS2Impl(*it));
        categories.append(item);
    }

    return categories;
}

QString FeedRSS2Impl::title() const
{
    return m_doc->title();
}

QString FeedRSS2Impl::link() const
{
    return m_doc->link();
}

QString FeedRSS2Impl::description() const
{
    return m_doc->description();
}

QList<PersonPtr> FeedRSS2Impl::authors() const
{
    return QList<PersonPtr>();
}

QString FeedRSS2Impl::language() const
{
    return m_doc->language();
}

QString FeedRSS2Impl::copyright() const
{
    return m_doc->copyright();
}

ImagePtr FeedRSS2Impl::image() const
{
    ImageRSS2ImplPtr ptr(new ImageRSS2Impl(m_doc->image()));
    return ptr;
}

QMultiMap<QString, QDomElement> FeedRSS2Impl::additionalProperties() const
{
    QMultiMap<QString, QDomElement> ret;

    foreach (const QDomElement &i, m_doc->unhandledElements()) {
        ret.insert(i.namespaceURI() + i.localName(), i);
    }

    return ret;
}

} // namespace Syndication
