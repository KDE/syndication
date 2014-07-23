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
#include "entry.h"
#include "category.h"
#include "constants.h"
#include "content.h"
#include "link.h"
#include "person.h"
#include "source.h"
#include "atomtools.h"

#include <specificitemvisitor.h>
#include <tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QString>

namespace Syndication
{
namespace Atom
{

Entry::Entry() : ElementWrapper()
{
}

Entry::Entry(const QDomElement &element) : ElementWrapper(element)
{
}

void Entry::setFeedAuthors(const QList<Person> &feedAuthors)
{
    m_feedAuthors = feedAuthors;
}

QList<Person> Entry::authors() const
{
    QList<QDomElement> a =
        elementsByTagNameNS(atom1Namespace(),
                            QLatin1String("author"));
    QList<Person> list;

    if (!a.isEmpty()) {
        QList<QDomElement>::ConstIterator it = a.constBegin();
        QList<QDomElement>::ConstIterator end = a.constEnd();

        for (; it != end; ++it) {
            list.append(Person(*it));
        }
    } else {
        list = source().authors();
    }

    if (!list.isEmpty()) {
        return list;
    }

    return m_feedAuthors;
}

QList<Person> Entry::contributors() const
{
    QList<QDomElement> a =
        elementsByTagNameNS(atom1Namespace(),
                            QLatin1String("contributor"));
    QList<Person> list;

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Person(*it));
    }

    return list;
}

QList<Category> Entry::categories() const
{
    QList<QDomElement> a =
        elementsByTagNameNS(atom1Namespace(),
                            QLatin1String("category"));
    QList<Category> list;

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Category(*it));
    }

    return list;
}

QString Entry::id() const
{
    return extractElementTextNS(atom1Namespace(),
                                QLatin1String("id"));

}

QList<Link> Entry::links() const
{
    QList<QDomElement> a =
        elementsByTagNameNS(atom1Namespace(),
                            QLatin1String("link"));
    QList<Link> list;

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Link(*it));
    }

    return list;
}

QString Entry::rights() const
{
    return extractAtomText(*this, QLatin1String("rights"));
}

Source Entry::source() const
{
    return Source(firstElementByTagNameNS(atom1Namespace(),
                                          QLatin1String("source")));
}

time_t Entry::published() const
{
    QString pub = extractElementTextNS(atom1Namespace(),
                                       QLatin1String("published"));
    return parseDate(pub, ISODate);
}

time_t Entry::updated() const
{
    QString upd = extractElementTextNS(atom1Namespace(),
                                       QLatin1String("updated"));
    return parseDate(upd, ISODate);
}

QString Entry::summary() const
{
    return extractAtomText(*this, QLatin1String("summary"));
}

QString Entry::title() const
{
    return extractAtomText(*this, QLatin1String("title"));
}

Content Entry::content() const
{
    return Content(firstElementByTagNameNS(atom1Namespace(),
                                           QLatin1String("content")));
}

QList<QDomElement> Entry::unhandledElements() const
{
    // TODO: do not hardcode this list here
    QList<ElementType> handled;
    handled.append(ElementType(QLatin1String("author"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("contributor"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("category"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("id"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("link"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("rights"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("source"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("published"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("updated"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("summary"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("title"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("content"), atom1Namespace()));

    QList<QDomElement> notHandled;

    QDomNodeList children = element().childNodes();
    for (int i = 0; i < children.size(); ++i) {
        QDomElement el = children.at(i).toElement();
        if (!el.isNull()
                && !handled.contains(ElementType(el.localName(), el.namespaceURI()))) {
            notHandled.append(el);
        }
    }

    return notHandled;
}

QString Entry::debugInfo() const
{
    QString info;
    info += QLatin1String("### Entry: ###################\n");
    if (!title().isEmpty()) {
        info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    }
    if (!summary().isEmpty()) {
        info += QLatin1String("summary: #") + summary() + QLatin1String("#\n");
    }
    if (!id().isEmpty()) {
        info += QLatin1String("id: #") + id() + QLatin1String("#\n");
    }
    if (!content().isNull()) {
        info += content().debugInfo();
    }

    if (!rights().isEmpty()) {
        info += QLatin1String("rights: #") + rights() + QLatin1String("#\n");
    }

    QString dupdated = dateTimeToString(updated());
    if (!dupdated.isNull()) {
        info += QLatin1String("updated: #") + dupdated + QLatin1String("#\n");
    }

    QString dpublished = dateTimeToString(published());
    if (!dpublished.isNull()) {
        info += QLatin1String("published: #") + dpublished + QLatin1String("#\n");
    }

    QList<Link> dlinks = links();
    QList<Link>::ConstIterator endlinks = dlinks.constEnd();
    for (QList<Link>::ConstIterator it = dlinks.constBegin(); it != endlinks; ++it) {
        info += (*it).debugInfo();
    }

    QList<Category> dcats = categories();
    QList<Category>::ConstIterator endcats = dcats.constEnd();
    for (QList<Category>::ConstIterator it = dcats.constBegin(); it != endcats; ++it) {
        info += (*it).debugInfo();
    }

    info += QLatin1String("### Authors: ###################\n");

    QList<Person> dauthors = authors();
    QList<Person>::ConstIterator endauthors = dauthors.constEnd();
    for (QList<Person>::ConstIterator it = dauthors.constBegin(); it != endauthors; ++it) {
        info += (*it).debugInfo();
    }

    info += QLatin1String("### Contributors: ###################\n");

    QList<Person> dcontri = contributors();
    QList<Person>::ConstIterator endcontri = dcontri.constEnd();
    for (QList<Person>::ConstIterator it = dcontri.constBegin(); it != endcontri; ++it) {
        info += (*it).debugInfo();
    }

    if (!source().isNull()) {
        info += source().debugInfo();
    }

    info += QLatin1String("### Entry end ################\n");

    return info;
}

bool Entry::accept(SpecificItemVisitor *visitor)
{
    return visitor->visitAtomEntry(this);
}

} // namespace Atom
} //namespace Syndication

