
/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2006 Frank Osterfeld <osterfeld@kde.org>
 *
 * This library is free software you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "itemrss2impl.h"
#include "categoryrss2impl.h"
#include "enclosurerss2impl.h"
#include <atom/constants.h>
#include <rss2/category.h>
#include <rss2/enclosure.h>
#include <constants.h>
#include <personimpl.h>
#include <tools.h>

#include <QDomElement>
#include <QList>
#include <QMultiMap>
#include <QString>

namespace Syndication
{

ItemRSS2Impl::ItemRSS2Impl(const Syndication::RSS2::Item &item) : m_item(item)
{
}

QString ItemRSS2Impl::title() const
{
    return m_item.title();
}

QString ItemRSS2Impl::link() const
{
    QString link = m_item.link();
    if (!link.isEmpty()) {
        return link;
    }

    QString guid = m_item.guid();
    if (m_item.guidIsPermaLink()) {
        return guid;
    }

    return QString();
}

QString ItemRSS2Impl::description() const
{
    return m_item.description();
}

QString ItemRSS2Impl::content() const
{
    return m_item.content();
}

QList<PersonPtr> ItemRSS2Impl::authors() const
{
    QList<PersonPtr> list;

    PersonPtr ptr = personFromString(m_item.author());

    if (!ptr->isNull()) {
        list.append(ptr);
    }

    return list;
}

QString ItemRSS2Impl::language() const
{
    return QString();
}

QString ItemRSS2Impl::id() const
{
    QString guid = m_item.guid();
    if (!guid.isEmpty()) {
        return guid;
    }

    return QStringLiteral("hash:%1").arg(calcMD5Sum(title()
            + description() + link() + content()));
}

time_t ItemRSS2Impl::datePublished() const
{
    return m_item.pubDate();
}

time_t ItemRSS2Impl::dateUpdated() const
{
    //Some RSS feeds contain atom elements - return atom:dateUpdated if present
    const QString updstr = m_item.extractElementTextNS(Atom::atom1Namespace(), QStringLiteral("updated"));
    if (!updstr.isEmpty()) {
        return parseDate(updstr, ISODate);
    } else {
        return datePublished();
    }
}

QList<Syndication::EnclosurePtr> ItemRSS2Impl::enclosures() const
{
    QList<Syndication::EnclosurePtr> list;

    QList<Syndication::RSS2::Enclosure> encs = m_item.enclosures();
    list.reserve(encs.size());

    for (auto it = encs.cbegin(); it != encs.cend(); ++it) {
        EnclosureRSS2ImplPtr impl(new EnclosureRSS2Impl(m_item, *it));
        list.append(impl);
    }

    return list;
}

QList<Syndication::CategoryPtr> ItemRSS2Impl::categories() const
{
    QList<Syndication::CategoryPtr> list;

    QList<Syndication::RSS2::Category> cats = m_item.categories();
    list.reserve(cats.size());

    for (auto it = cats.cbegin(), end = cats.cend(); it != end; ++it) {
        CategoryRSS2ImplPtr impl(new CategoryRSS2Impl(*it));
        list.append(impl);
    }

    return list;
}

int ItemRSS2Impl::commentsCount() const
{
    QString cstr = m_item.extractElementTextNS(slashNamespace(), QStringLiteral("comments"));
    bool ok = false;
    int comments = cstr.toInt(&ok);
    return ok ? comments : -1;
}

QString ItemRSS2Impl::commentsLink() const
{
    return m_item.comments();
}

QString ItemRSS2Impl::commentsFeed() const
{
    QString t = m_item.extractElementTextNS(commentApiNamespace(), QStringLiteral("commentRss"));
    if (t.isNull()) {
        t = m_item.extractElementTextNS(commentApiNamespace(), QStringLiteral("commentRSS"));
    }
    return t;
}

QString ItemRSS2Impl::commentPostUri() const
{
    return m_item.extractElementTextNS(commentApiNamespace(), QStringLiteral("comment"));
}

Syndication::SpecificItemPtr ItemRSS2Impl::specificItem() const
{
    return Syndication::SpecificItemPtr(new Syndication::RSS2::Item(m_item));
}

QMultiMap<QString, QDomElement> ItemRSS2Impl::additionalProperties() const
{
    QMultiMap<QString, QDomElement> ret;

    const auto unhandledElements = m_item.unhandledElements();
    for (const QDomElement &i : unhandledElements) {
        ret.insert(i.namespaceURI() + i.localName(), i);
    }

    return ret;
}

} // namespace Syndication
