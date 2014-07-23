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

#include "document.h"
#include "category.h"
#include "constants.h"
#include "entry.h"
#include "generator.h"
#include "link.h"
#include "person.h"
#include "atomtools.h"

#include <documentvisitor.h>
#include <tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QString>

namespace Syndication
{
namespace Atom
{

FeedDocument::FeedDocument() : ElementWrapper()
{
}

FeedDocument::FeedDocument(const QDomElement &element)  : ElementWrapper(element)
{
}

bool FeedDocument::accept(DocumentVisitor *visitor)
{
    return visitor->visitAtomFeedDocument(this);
}

QList<Person> FeedDocument::authors() const
{
    QList<QDomElement> a =
        elementsByTagNameNS(atom1Namespace(),
                            QLatin1String("author"));
    QList<Person> list;

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Person(*it));
    }

    return list;
}

QList<Person> FeedDocument::contributors() const
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

QList<Category> FeedDocument::categories() const
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

Generator FeedDocument::generator() const
{
    return Generator(firstElementByTagNameNS(atom1Namespace(),
                     QLatin1String("generator")));
}

QString FeedDocument::icon() const
{
    return completeURI(extractElementTextNS(atom1Namespace(),
                                            QLatin1String("icon")));

}

QString FeedDocument::logo() const
{
    return completeURI(extractElementTextNS(atom1Namespace(),
                                            QLatin1String("logo")));
}

QString FeedDocument::id() const
{
    return extractElementTextNS(atom1Namespace(),
                                QLatin1String("id"));
}

QString FeedDocument::rights() const
{

    return extractAtomText(*this, QLatin1String("rights"));
}

QString FeedDocument::title() const
{
    return extractAtomText(*this, QLatin1String("title"));
}

QString FeedDocument::subtitle() const
{
    return extractAtomText(*this, QLatin1String("subtitle"));
}

time_t FeedDocument::updated() const
{
    QString upd = extractElementTextNS(atom1Namespace(),
                                       QLatin1String("updated"));
    return parseDate(upd, ISODate);
}

QList<Link> FeedDocument::links() const
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

QList<Entry> FeedDocument::entries() const
{
    QList<QDomElement> a =
        elementsByTagNameNS(atom1Namespace(),
                            QLatin1String("entry"));
    QList<Entry> list;

    QList<Person> feedAuthors = authors();
    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        Entry entry(*it);
        entry.setFeedAuthors(feedAuthors);
        list.append(entry);
    }

    return list;
}

QList<QDomElement> FeedDocument::unhandledElements() const
{
    // TODO: do not hardcode this list here
    QList<ElementType> handled;
    handled.append(ElementType(QLatin1String("author"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("contributor"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("category"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("generator"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("icon"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("logo"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("id"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("rights"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("title"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("subtitle"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("updated"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("link"), atom1Namespace()));
    handled.append(ElementType(QLatin1String("entry"), atom1Namespace()));

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

bool FeedDocument::isValid() const
{
    return !isNull();
}

QString FeedDocument::debugInfo() const
{
    QString info;
    info += QLatin1String("### FeedDocument: ###################\n");
    if (!title().isEmpty()) {
        info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    }
    if (!subtitle().isEmpty()) {
        info += QLatin1String("subtitle: #") + subtitle() + QLatin1String("#\n");
    }
    if (!id().isEmpty()) {
        info += QLatin1String("id: #") + id() + QLatin1String("#\n");
    }

    if (!rights().isEmpty()) {
        info += QLatin1String("rights: #") + rights() + QLatin1String("#\n");
    }
    if (!icon().isEmpty()) {
        info += QLatin1String("icon: #") + icon() + QLatin1String("#\n");
    }
    if (!logo().isEmpty()) {
        info += QLatin1String("logo: #") + logo() + QLatin1String("#\n");
    }
    if (!generator().isNull()) {
        info += generator().debugInfo();
    }

    QString dupdated = dateTimeToString(updated());
    if (!dupdated.isNull()) {
        info += QLatin1String("updated: #") + dupdated + QLatin1String("#\n");
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

    QList<Entry> dentries = entries();
    QList<Entry>::ConstIterator endentries = dentries.constEnd();
    for (QList<Entry>::ConstIterator it = dentries.constBegin(); it != endentries; ++it) {
        info += (*it).debugInfo();
    }

    info += QLatin1String("### FeedDocument end ################\n");

    return info;
}

EntryDocument::EntryDocument() : ElementWrapper()
{
}

EntryDocument::EntryDocument(const QDomElement &element)  : ElementWrapper(element)
{
}

bool EntryDocument::accept(DocumentVisitor *visitor)
{
    return visitor->visitAtomEntryDocument(this);
}

Entry EntryDocument::entry() const
{
    return Entry(element());
}

bool EntryDocument::isValid() const
{
    return !isNull();
}

QString EntryDocument::debugInfo() const
{
    QString info;
    info += QLatin1String("### EntryDocument: ##################\n");

    Entry dentry = entry();
    if (!dentry.isNull()) {
        info += dentry.debugInfo();
    }

    info += QLatin1String("### EntryDocument end ###############\n");
    return info;
}

} // namespace Atom
} // namespace Syndication
