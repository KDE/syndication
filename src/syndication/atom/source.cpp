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

#include "source.h"
#include "category.h"
#include "constants.h"
#include "generator.h"
#include "link.h"
#include "person.h"
#include "atomtools.h"

#include <tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QString>

namespace Syndication
{
namespace Atom
{

Source::Source() : ElementWrapper()
{
}

Source::Source(const QDomElement &element) : ElementWrapper(element)
{
}

QList<Person> Source::authors() const
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

QList<Person> Source::contributors() const
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

QList<Category> Source::categories() const
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

Generator Source::generator() const
{
    return Generator(firstElementByTagNameNS(atom1Namespace(),
                     QLatin1String("generator")));
}

QString Source::icon() const
{
    return extractElementTextNS(atom1Namespace(),
                                QLatin1String("icon"));
}

QString Source::id() const
{
    return extractElementTextNS(atom1Namespace(),
                                QLatin1String("id"));
}

QList<Link> Source::links() const
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

QString Source::logo() const
{
    return extractElementTextNS(atom1Namespace(),
                                QLatin1String("logo"));
}

QString Source::rights() const
{
    return extractAtomText(*this, QLatin1String("rights"));
}

QString Source::subtitle() const
{
    return extractAtomText(*this, QLatin1String("subtitle"));
}

QString Source::title() const
{
    return extractAtomText(*this, QLatin1String("title"));
}

time_t Source::updated() const
{
    QString upd = extractElementTextNS(atom1Namespace(),
                                       QLatin1String("updated"));
    return parseDate(upd, ISODate);
}

QString Source::debugInfo() const
{
    QString info;
    info += QLatin1String("### Source: ###################\n");
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
} //namespace Syndication
