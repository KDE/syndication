/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "source.h"
#include "atomtools.h"
#include "category.h"
#include "constants.h"
#include "generator.h"
#include "link.h"
#include "person.h"

#include <tools.h>

#include <QDomElement>
#include <QList>
#include <QString>

namespace Syndication
{
namespace Atom
{
Source::Source()
    : ElementWrapper()
{
}

Source::Source(const QDomElement &element)
    : ElementWrapper(element)
{
}

QList<Person> Source::authors() const
{
    const QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("author"));
    QList<Person> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Person(*it));
    }

    return list;
}

QList<Person> Source::contributors() const
{
    const QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("contributor"));
    QList<Person> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Person(*it));
    }

    return list;
}

QList<Category> Source::categories() const
{
    const QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("category"));
    QList<Category> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Category(*it));
    }

    return list;
}

Generator Source::generator() const
{
    return Generator(firstElementByTagNameNS(atom1Namespace(), QStringLiteral("generator")));
}

QString Source::icon() const
{
    return extractElementTextNS(atom1Namespace(), QStringLiteral("icon"));
}

QString Source::id() const
{
    return extractElementTextNS(atom1Namespace(), QStringLiteral("id"));
}

QList<Link> Source::links() const
{
    const QList<QDomElement> a = elementsByTagNameNS(atom1Namespace(), QStringLiteral("link"));
    QList<Link> list;
    list.reserve(a.count());

    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();

    for (; it != end; ++it) {
        list.append(Link(*it));
    }

    return list;
}

QString Source::logo() const
{
    return extractElementTextNS(atom1Namespace(), QStringLiteral("logo"));
}

QString Source::rights() const
{
    return extractAtomText(*this, QStringLiteral("rights"));
}

QString Source::subtitle() const
{
    return extractAtomText(*this, QStringLiteral("subtitle"));
}

QString Source::title() const
{
    return extractAtomText(*this, QStringLiteral("title"));
}

time_t Source::updated() const
{
    const QString upd = extractElementTextNS(atom1Namespace(), QStringLiteral("updated"));
    return parseDate(upd, ISODate);
}

QString Source::debugInfo() const
{
    QString info = QLatin1String("### Source: ###################\n");
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

    info += QLatin1String("### Source end ################\n");

    return info;
}

} // namespace Atom
} // namespace Syndication
