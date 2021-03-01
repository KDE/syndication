/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "feedatomimpl.h"
#include "categoryatomimpl.h"
#include "imageatomimpl.h"
#include "itematomimpl.h"
#include <atom/category.h>
#include <atom/entry.h>
#include <atom/link.h>
#include <atom/person.h>
#include <personimpl.h>

#include <QDomElement>
#include <QList>
#include <QMultiMap>
#include <QString>

namespace Syndication
{
FeedAtomImpl::FeedAtomImpl(Syndication::Atom::FeedDocumentPtr doc)
    : m_doc(doc)
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
    items.reserve(entries.count());

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
    categories.reserve(entries.count());

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
    QList<Syndication::Atom::Person> contributorAtoms = m_doc->contributors();
    QList<Syndication::Atom::Person>::ConstIterator it = atomps.constBegin();
    QList<Syndication::Atom::Person>::ConstIterator end = atomps.constEnd();

    QList<PersonPtr> list;
    list.reserve(atomps.count() + contributorAtoms.count());

    for (; it != end; ++it) {
        PersonImplPtr ptr(new PersonImpl((*it).name(), (*it).uri(), (*it).email()));
        list.append(ptr);
    }

    it = contributorAtoms.constBegin();
    end = contributorAtoms.constEnd();

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

ImagePtr FeedAtomImpl::icon() const
{
    return ImageAtomImplPtr(new ImageAtomImpl(m_doc->icon()));
}

QMultiMap<QString, QDomElement> FeedAtomImpl::additionalProperties() const
{
    QMultiMap<QString, QDomElement> ret;
    const auto unhandledElements = m_doc->unhandledElements();
    for (const QDomElement &i : unhandledElements) {
        ret.insert(i.namespaceURI() + i.localName(), i);
    }

    return ret;
}

} // namespace Syndication
