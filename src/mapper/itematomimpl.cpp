/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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

#include <QDomElement>
#include <QList>
#include <QMultiMap>
#include <QString>

using Syndication::Atom::Content;
using Syndication::Atom::Link;
using Syndication::Atom::Person;

namespace Syndication
{
ItemAtomImpl::ItemAtomImpl(const Syndication::Atom::Entry &entry)
    : m_entry(entry)
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
    QList<Syndication::Atom::Person> contributorAtoms = m_entry.contributors();
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
    const QString id = m_entry.id();
    if (!id.isEmpty()) {
        return id;
    }

    return QStringLiteral("hash:%1").arg(Syndication::calcMD5Sum(title() + description() + link() + content()));
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
    list.reserve(cats.count());

    for (; it != end; ++it) {
        CategoryAtomImplPtr impl(new CategoryAtomImpl(*it));
        list.append(impl);
    }

    return list;
}

int ItemAtomImpl::commentsCount() const
{
    QString cstr = m_entry.extractElementTextNS(slashNamespace(), QStringLiteral("comments"));
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
    return m_entry.extractElementTextNS(commentApiNamespace(), QStringLiteral("commentRss"));
}

QString ItemAtomImpl::commentPostUri() const
{
    return m_entry.extractElementTextNS(commentApiNamespace(), QStringLiteral("comment"));
}

Syndication::SpecificItemPtr ItemAtomImpl::specificItem() const
{
    return Syndication::SpecificItemPtr(new Syndication::Atom::Entry(m_entry));
}

QMultiMap<QString, QDomElement> ItemAtomImpl::additionalProperties() const
{
    QMultiMap<QString, QDomElement> ret;
    const auto unhandledElements = m_entry.unhandledElements();
    for (const QDomElement &i : unhandledElements) {
        ret.insert(i.namespaceURI() + i.localName(), i);
    }

    return ret;
}

} // namespace Syndication
