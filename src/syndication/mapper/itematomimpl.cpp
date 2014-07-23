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

#include "itematomimpl.h"
#include "categoryatomimpl.h"
#include "enclosureatomimpl.h"

#include <atom/category.h>
#include <atom/content.h>
#include <atom/link.h>
#include <atom/person.h>
#include <category.h>
#include <constants.h>
#include <enclosure.h>
#include <personimpl.h>
#include <tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QMultiMap>
#include <QtCore/QString>

using Syndication::Atom::Content;
using Syndication::Atom::Link;
using Syndication::Atom::Person;

namespace Syndication
{

ItemAtomImpl::ItemAtomImpl(const Syndication::Atom::Entry &entry) : m_entry(entry)
{
}

QString ItemAtomImpl::title() const
{
    return m_entry.title();
}

QString ItemAtomImpl::link() const
{
    QList<Syndication::Atom::Link> links = m_entry.links();
    QList<Syndication::Atom::Link>::ConstIterator it = links.constBegin();
    QList<Syndication::Atom::Link>::ConstIterator end = links.constEnd();

    // return first link where rel="alternate"
    for (; it != end; ++it) {
        if ((*it).rel() == QLatin1String("alternate")) {
            return (*it).href();
        }
    }

    return QString();
}

QString ItemAtomImpl::description() const
{
    return m_entry.summary();
}

QString ItemAtomImpl::content() const
{
    Content content = m_entry.content();
    if (content.isNull()) {
        return QString();
    }

    return content.asString();
}

QList<PersonPtr> ItemAtomImpl::authors() const
{
    QList<Syndication::Atom::Person> atomps = m_entry.authors();
    QList<Syndication::Atom::Person>::ConstIterator it = atomps.constBegin();
    QList<Syndication::Atom::Person>::ConstIterator end = atomps.constEnd();

    QList<PersonPtr> list;

    for (; it != end; ++it) {
        PersonImplPtr ptr(new PersonImpl((*it).name(), (*it).uri(), (*it).email()));
        list.append(ptr);
    }

    atomps = m_entry.contributors();

    it = atomps.constBegin();
    end = atomps.constEnd();

    for (; it != end; ++it) {
        PersonImplPtr ptr(new PersonImpl((*it).name(), (*it).uri(), (*it).email()));
        list.append(ptr);
    }

    return list;
}

time_t ItemAtomImpl::datePublished() const
{
    time_t pub = m_entry.published();
    if (pub == 0) {
        return m_entry.updated();
    } else {
        return pub;
    }
}

time_t ItemAtomImpl::dateUpdated() const
{
    time_t upd = m_entry.updated();
    if (upd == 0) {
        return m_entry.published();
    } else {
        return upd;
    }
}

QString ItemAtomImpl::language() const
{
    return m_entry.xmlLang();
}

QString ItemAtomImpl::id() const
{
    QString id = m_entry.id();
    if (!id.isEmpty()) {
        return id;
    }

    return QString::fromLatin1("hash:%1").arg(Syndication::calcMD5Sum(title() + description() + link() + content()));
}

QList<Syndication::EnclosurePtr> ItemAtomImpl::enclosures() const
{
    QList<Syndication::EnclosurePtr> list;

    QList<Syndication::Atom::Link> links = m_entry.links();
    QList<Syndication::Atom::Link>::ConstIterator it = links.constBegin();
    QList<Syndication::Atom::Link>::ConstIterator end = links.constEnd();

    for (; it != end; ++it) {
        if ((*it).rel() == QLatin1String("enclosure")) {
            list.append(EnclosureAtomImplPtr(new EnclosureAtomImpl(*it)));

        }
    }

    return list;
}

QList<Syndication::CategoryPtr> ItemAtomImpl::categories() const
{
    QList<Syndication::CategoryPtr> list;

    QList<Syndication::Atom::Category> cats = m_entry.categories();
    QList<Syndication::Atom::Category>::ConstIterator it = cats.constBegin();
    QList<Syndication::Atom::Category>::ConstIterator end = cats.constEnd();

    for (; it != end; ++it) {
        CategoryAtomImplPtr impl(new CategoryAtomImpl(*it));
        list.append(impl);
    }

    return list;
}

int ItemAtomImpl::commentsCount() const
{
    QString cstr = m_entry.extractElementTextNS(slashNamespace(), QLatin1String("comments"));
    bool ok = false;
    int comments = cstr.toInt(&ok);
    return ok ? comments : -1;
}

QString ItemAtomImpl::commentsLink() const
{
    return QString();
}

QString ItemAtomImpl::commentsFeed() const
{
    return m_entry.extractElementTextNS(commentApiNamespace(), QLatin1String("commentRss"));
}

QString ItemAtomImpl::commentPostUri() const
{
    return m_entry.extractElementTextNS(commentApiNamespace(), QLatin1String("comment"));
}

Syndication::SpecificItemPtr ItemAtomImpl::specificItem() const
{
    return Syndication::SpecificItemPtr(new Syndication::Atom::Entry(m_entry));
}

QMultiMap<QString, QDomElement> ItemAtomImpl::additionalProperties() const
{
    QMultiMap<QString, QDomElement> ret;

    foreach (const QDomElement &i, m_entry.unhandledElements()) {
        ret.insert(i.namespaceURI() + i.localName(), i);
    }

    return ret;
}

} // namespace Syndication
