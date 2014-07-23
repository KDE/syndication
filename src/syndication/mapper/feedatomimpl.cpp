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

#include "feedatomimpl.h"
#include "categoryatomimpl.h"
#include "imageatomimpl.h"
#include "itematomimpl.h"
#include <personimpl.h>
#include <atom/category.h>
#include <atom/entry.h>
#include <atom/link.h>
#include <atom/person.h>

#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QMultiMap>
#include <QtCore/QString>

namespace Syndication
{

FeedAtomImpl::FeedAtomImpl(Syndication::Atom::FeedDocumentPtr doc) : m_doc(doc)
{
}

Syndication::SpecificDocumentPtr FeedAtomImpl::specificDocument() const
{
    return m_doc;
}

QList<Syndication::ItemPtr> FeedAtomImpl::items() const
{
    QList<ItemPtr> items;
    QList<Syndication::Atom::Entry> entries = m_doc->entries();
    QList<Syndication::Atom::Entry>::ConstIterator it = entries.constBegin();
    QList<Syndication::Atom::Entry>::ConstIterator end = entries.constEnd();

    for (; it != end; ++it) {
        ItemAtomImplPtr item(new ItemAtomImpl(*it));
        items.append(item);
    }

    return items;
}

QList<Syndication::CategoryPtr> FeedAtomImpl::categories() const
{
    QList<CategoryPtr> categories;
    QList<Syndication::Atom::Category> entries = m_doc->categories();
    QList<Syndication::Atom::Category>::ConstIterator it = entries.constBegin();
    QList<Syndication::Atom::Category>::ConstIterator end = entries.constEnd();

    for (; it != end; ++it) {
        CategoryAtomImplPtr item(new CategoryAtomImpl(*it));
        categories.append(item);
    }

    return categories;
}

QString FeedAtomImpl::title() const
{
    return m_doc->title();
}

QString FeedAtomImpl::link() const
{
    QList<Syndication::Atom::Link> links = m_doc->links();
    QList<Syndication::Atom::Link>::ConstIterator it = links.constBegin();
    QList<Syndication::Atom::Link>::ConstIterator end = links.constEnd();

    // return first link where rel="alternate"
    // TODO: if there are multiple "alternate" links, find other criteria to choose one of them
    for (; it != end; ++it) {
        if ((*it).rel() == QLatin1String("alternate")) {
            return (*it).href();
        }
    }

    return QString();
}

QString FeedAtomImpl::description() const
{
    return m_doc->subtitle();
}

QList<PersonPtr> FeedAtomImpl::authors() const
{
    QList<Syndication::Atom::Person> atomps = m_doc->authors();
    QList<Syndication::Atom::Person>::ConstIterator it = atomps.constBegin();
    QList<Syndication::Atom::Person>::ConstIterator end = atomps.constEnd();

    QList<PersonPtr> list;

    for (; it != end; ++it) {
        PersonImplPtr ptr(new PersonImpl((*it).name(), (*it).uri(), (*it).email()));
        list.append(ptr);
    }

    atomps = m_doc->contributors();

    it = atomps.constBegin();
    end = atomps.constEnd();

    for (; it != end; ++it) {
        PersonImplPtr ptr(new PersonImpl((*it).name(), (*it).uri(), (*it).email()));
        list.append(ptr);
    }

    return list;
}

QString FeedAtomImpl::language() const
{
    return m_doc->xmlLang();
}

QString FeedAtomImpl::copyright() const
{
    return m_doc->rights();
}

ImagePtr FeedAtomImpl::image() const
{
    return ImageAtomImplPtr(new ImageAtomImpl(m_doc->logo()));
}

QMultiMap<QString, QDomElement> FeedAtomImpl::additionalProperties() const
{
    QMultiMap<QString, QDomElement> ret;

    foreach (const QDomElement &i, m_doc->unhandledElements()) {
        ret.insert(i.namespaceURI() + i.localName(), i);
    }

    return ret;
}

} // namespace Syndication
