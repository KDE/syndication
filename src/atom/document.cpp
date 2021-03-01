/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "document.h"
#include "atomtools.h"
#include "category.h"
#include "constants.h"
#include "entry.h"
#include "generator.h"
#include "link.h"
#include "person.h"

#include <documentvisitor.h>
#include <tools.h>

#include <QDomElement>
#include <QList>
#include <QString>

#include <vector>

namespace Syndication
{
namespace Atom
{
FeedDocument::FeedDocument()
    : ElementWrapper()
{
}

FeedDocument::FeedDocument(const QDomElement &element)
    : ElementWrapper(element)
{
}

bool FeedDocument::accept(DocumentVisitor *visitor)
{
    return visitor->visitAtomFeedDocument(this);
}

QList<Person> FeedDocument::authors() const
{
    QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("author"));
    QList<Person> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    const QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Person(*it));
    }

    return list;
}

QList<Person> FeedDocument::contributors() const
{
    QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("contributor"));
    QList<Person> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    const QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Person(*it));
    }

    return list;
}

QList<Category> FeedDocument::categories() const
{
    QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("category"));
    QList<Category> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    const QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Category(*it));
    }

    return list;
}

Generator FeedDocument::generator() const
{
    return Generator(firstElementByTagNameNS(atom1Namespace(), QStringLiteral("generator")));
}

QString FeedDocument::icon() const
{
    const QString iconPath = extractElementTextNS(atom1Namespace(), QStringLiteral("icon"));
    if (iconPath.isEmpty()) {
        return {};
    }
    return completeURI(iconPath);
}

QString FeedDocument::logo() const
{
    return completeURI(extractElementTextNS(atom1Namespace(), QStringLiteral("logo")));
}

QString FeedDocument::id() const
{
    return extractElementTextNS(atom1Namespace(), QStringLiteral("id"));
}

QString FeedDocument::rights() const
{
    return extractAtomText(*this, QStringLiteral("rights"));
}

QString FeedDocument::title() const
{
    return extractAtomText(*this, QStringLiteral("title"));
}

QString FeedDocument::subtitle() const
{
    return extractAtomText(*this, QStringLiteral("subtitle"));
}

time_t FeedDocument::updated() const
{
    QString upd = extractElementTextNS(atom1Namespace(), QStringLiteral("updated"));
    return parseDate(upd, ISODate);
}

QList<Link> FeedDocument::links() const
{
    QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("link"));
    QList<Link> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Link(*it));
    }

    return list;
}

QList<Entry> FeedDocument::entries() const
{
    QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("entry"));
    QList<Entry> list;
    list.reserve(a.count());

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
    static std::vector<ElementType> handled; // QVector would require a default ctor, and ElementType is too big for QList
    if (handled.empty()) {
        handled.reserve(13);
        handled.push_back(ElementType(QStringLiteral("author"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("contributor"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("category"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("generator"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("icon"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("logo"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("id"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("rights"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("title"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("subtitle"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("updated"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("link"), atom1Namespace()));
        handled.push_back(ElementType(QStringLiteral("entry"), atom1Namespace()));
    }

    QList<QDomElement> notHandled;

    QDomNodeList children = element().childNodes();
    const int numChildren = children.size();
    for (int i = 0; i < numChildren; ++i) {
        QDomElement el = children.at(i).toElement();
        if (!el.isNull() //
            && std::find(handled.cbegin(), handled.cend(), ElementType(el.localName(), el.namespaceURI())) == handled.cend()) {
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
    QString info = QLatin1String("### FeedDocument: ###################\n");
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

EntryDocument::EntryDocument()
    : ElementWrapper()
{
}

EntryDocument::EntryDocument(const QDomElement &element)
    : ElementWrapper(element)
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
