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
typedef QSharedPointer<ItemRSS2Impl> ItemRSS2ImplPtr;

/**
 * @internal
 */
class ItemRSS2Impl : public Syndication::Item
{
public:

    explicit ItemRSS2Impl(const Syndication::RSS2::Item &item);

    QString title() const Q_DECL_OVERRIDE;

    QString link() const Q_DECL_OVERRIDE;

    QString description() const Q_DECL_OVERRIDE;

    QString content() const Q_DECL_OVERRIDE;

    QList<PersonPtr> authors() const Q_DECL_OVERRIDE;

    QString language() const Q_DECL_OVERRIDE;

    QString id() const Q_DECL_OVERRIDE;

    time_t datePublished() const Q_DECL_OVERRIDE;

    time_t dateUpdated() const Q_DECL_OVERRIDE;

    QList<EnclosurePtr> enclosures() const Q_DECL_OVERRIDE;

    QList<CategoryPtr> categories() const Q_DECL_OVERRIDE;

    SpecificItemPtr specificItem() const Q_DECL_OVERRIDE;

    int commentsCount() const Q_DECL_OVERRIDE;

    QString commentsLink() const Q_DECL_OVERRIDE;

    QString commentsFeed() const Q_DECL_OVERRIDE;

    QString commentPostUri() const Q_DECL_OVERRIDE;

    QMultiMap<QString, QDomElement> additionalProperties() const Q_DECL_OVERRIDE;

private:

    Syndication::RSS2::Item m_item;
};

} // namespace Syndication

#endif // SYNDICATION_MAPPER_ITEMRSS2IMPL_H
