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

#include "itemrdfimpl.h"

#include <rdf/dublincore.h>
#include <rdf/property.h>
#include <rdf/resource.h>
#include <rdf/resourcewrapper.h>
#include <rdf/statement.h>
#include <constants.h>
#include <category.h>
#include <enclosure.h>
#include <personimpl.h>
#include <tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QMultiMap>
#include <QtCore/QString>
#include <QtCore/QStringList>

using Syndication::RDF::Property;
using Syndication::RDF::PropertyPtr;

namespace Syndication
{

ItemRDFImpl::ItemRDFImpl(const Syndication::RDF::Item &item) : m_item(item)
{
}

QString ItemRDFImpl::title() const
{
    return m_item.title();
}

QString ItemRDFImpl::link() const
{
    return m_item.link();
}

QString ItemRDFImpl::description() const
{
    return m_item.description();
}

QString ItemRDFImpl::content() const
{
    return m_item.encodedContent();
}

QList<PersonPtr> ItemRDFImpl::authors() const
{
    QList<PersonPtr> list;

    QStringList people = m_item.dc().creators();
    people += m_item.dc().contributors();
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

QString ItemRDFImpl::language() const
{
    return m_item.dc().language();
}

QString ItemRDFImpl::id() const
{
    if (!m_item.resource()->isAnon()) {
        return m_item.resource()->uri();
    } else {
        return QLatin1String("hash:") + calcMD5Sum(title() + description() + link() + content());
    }
}

time_t ItemRDFImpl::datePublished() const
{
    return m_item.dc().date();
}

time_t ItemRDFImpl::dateUpdated() const
{
    return m_item.dc().date();
}

QList<Syndication::EnclosurePtr> ItemRDFImpl::enclosures() const
{
    // return empty list
    return QList<Syndication::EnclosurePtr>();
}

QList<Syndication::CategoryPtr> ItemRDFImpl::categories() const
{
    // return empty list
    return QList<Syndication::CategoryPtr>();
}

int ItemRDFImpl::commentsCount() const
{
    PropertyPtr prop(new Property(slashNamespace() + QLatin1String("comments")));
    QString cstr = m_item.resource()->property(prop)->asString();
    bool ok = false;
    int comments = cstr.toInt(&ok);
    return ok ? comments : -1;
    return -1;
}

QString ItemRDFImpl::commentsLink() const
{
    return QString();
}

QString ItemRDFImpl::commentsFeed() const
{
    PropertyPtr prop(new Property(commentApiNamespace() + QLatin1String("commentRss")));
    return m_item.resource()->property(prop)->asString();
}

QString ItemRDFImpl::commentPostUri() const
{
    PropertyPtr prop(new Property(commentApiNamespace() + QLatin1String("comment")));
    return m_item.resource()->property(prop)->asString();
}

Syndication::SpecificItemPtr ItemRDFImpl::specificItem() const
{
    return Syndication::SpecificItemPtr(new Syndication::RDF::Item(m_item));
}

QMultiMap<QString, QDomElement> ItemRDFImpl::additionalProperties() const
{
    return QMultiMap<QString, QDomElement>();
}

} // namespace Syndication
