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

#ifndef SYNDICATION_MAPPER_ITEMRSS2IMPL_H
#define SYNDICATION_MAPPER_ITEMRSS2IMPL_H

#include <rss2/item.h>
#include <item.h>

namespace Syndication
{

class ItemRSS2Impl;
typedef boost::shared_ptr<ItemRSS2Impl> ItemRSS2ImplPtr;

/**
 * @internal
 */
class ItemRSS2Impl : public Syndication::Item
{
public:

    explicit ItemRSS2Impl(const Syndication::RSS2::Item &item);

    QString title() const;

    QString link() const;

    QString description() const;

    QString content() const;

    QList<PersonPtr> authors() const;

    QString language() const;

    QString id() const;

    time_t datePublished() const;

    time_t dateUpdated() const;

    QList<EnclosurePtr> enclosures() const;

    QList<CategoryPtr> categories() const;

    SpecificItemPtr specificItem() const;

    int commentsCount() const;

    QString commentsLink() const;

    QString commentsFeed() const;

    QString commentPostUri() const;

    QMultiMap<QString, QDomElement> additionalProperties() const;

private:

    Syndication::RSS2::Item m_item;
};

} // namespace Syndication

#endif // SYNDICATION_MAPPER_ITEMRSS2IMPL_H
