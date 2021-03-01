/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "feedrdfimpl.h"
#include "imagerdfimpl.h"
#include "itemrdfimpl.h"

#include <category.h>
#include <personimpl.h>
#include <rdf/dublincore.h>
#include <rdf/item.h>
#include <tools.h>

#include <QDomElement>
#include <QList>
#include <QMultiMap>
#include <QString>
#include <QStringList>

namespace Syndication
{
FeedRDFImpl::FeedRDFImpl(Syndication::RDF::DocumentPtr doc)
    : m_doc(doc)
{
}

Syndication::SpecificDocumentPtr FeedRDFImpl::specificDocument() const
{
    return m_doc;
}

QList<Syndication::ItemPtr> FeedRDFImpl::items() const
{
    QList<ItemPtr> items;
    QList<Syndication::RDF::Item> entries = m_doc->items();
    QList<Syndication::RDF::Item>::ConstIterator it = entries.constBegin();
    QList<Syndication::RDF::Item>::ConstIterator end = entries.constEnd();
    items.reserve(entries.count());

    for (; it != end; ++it) {
        ItemRDFImplPtr item(new ItemRDFImpl(*it));
        items.append(item);
    }

    return items;
}

QList<Syndication::CategoryPtr> FeedRDFImpl::categories() const
{
    // TODO: check if it makes sense to map dc:subject to categories
    return QList<Syndication::CategoryPtr>();
}

QString FeedRDFImpl::title() const
{
    return m_doc->title();
}

QString FeedRDFImpl::link() const
{
    return m_doc->link();
}

QString FeedRDFImpl::description() const
{
    return m_doc->description();
}

QList<PersonPtr> FeedRDFImpl::authors() const
{
    QList<PersonPtr> list;

    QStringList people = m_doc->dc().creators();
    people += m_doc->dc().contributors();
    QStringList::ConstIterator it = people.constBegin();
    QStringList::ConstIterator end = people.constEnd();

    for (; it != end; ++it) {
        PersonPtr ptr = personFromString(*it);
        if (!ptr->isNull()) {
            list.append(ptr);
        }
    }

    return list;
}

QString FeedRDFImpl::language() const
{
    return m_doc->dc().language();
}

QString FeedRDFImpl::copyright() const
{
    return m_doc->dc().rights();
}

ImagePtr FeedRDFImpl::image() const
{
    ImageRDFImplPtr ptr(new ImageRDFImpl(m_doc->image()));
    return ptr;
}

ImagePtr FeedRDFImpl::icon() const
{
    ImageRDFImplPtr ptr(new ImageRDFImpl({}));
    return ptr;
}

QMultiMap<QString, QDomElement> FeedRDFImpl::additionalProperties() const
{
    return QMultiMap<QString, QDomElement>();
}

} // namespace Syndication
