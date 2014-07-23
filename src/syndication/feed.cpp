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

#include "feed.h"
#include "category.h"
#include "image.h"
#include "item.h"
#include "person.h"

#include <QtCore/QList>
#include <QtCore/QString>

namespace Syndication
{

Feed::~Feed()
{
}

QString Feed::debugInfo() const
{
    QString info;

    info += QLatin1String("# Feed begin ######################\n");

    QString dtitle = title();
    if (!dtitle.isNull()) {
        info += QLatin1String("title: #") + dtitle + QLatin1String("#\n");
    }

    QString dlink = link();
    if (!dlink.isNull()) {
        info += QLatin1String("link: #") + dlink + QLatin1String("#\n");
    }

    QString ddescription = description();
    if (!ddescription.isNull()) {
        info += QLatin1String("description: #") + ddescription + QLatin1String("#\n");
    }

    QString dcopyright = copyright();
    if (!dcopyright.isNull()) {
        info += QLatin1String("copyright: #") + dcopyright + QLatin1String("#\n");
    }

    QString dlanguage = language();
    if (!dlanguage.isNull()) {
        info += QLatin1String("language: #") + dlanguage + QLatin1String("#\n");
    }

    QList<PersonPtr> dauthors = authors();
    QList<PersonPtr>::ConstIterator itp = dauthors.constBegin();
    QList<PersonPtr>::ConstIterator endp = dauthors.constEnd();

    for (; itp != endp; ++itp) {
        info += (*itp)->debugInfo();
    }

    QList<CategoryPtr> dcategories = categories();
    QList<CategoryPtr>::ConstIterator itc = dcategories.constBegin();
    QList<CategoryPtr>::ConstIterator endc = dcategories.constEnd();

    for (; itc != endc; ++itc) {
        info += (*itc)->debugInfo();
    }

    ImagePtr dimage = image();

    if (!dimage->isNull()) {
        info += dimage->debugInfo();
    }

    QList<ItemPtr> ditems = items();
    QList<ItemPtr>::ConstIterator it = ditems.constBegin();
    QList<ItemPtr>::ConstIterator end = ditems.constEnd();

    for (; it != end; ++it) {
        info += (*it)->debugInfo();
    }

    info += QLatin1String("# Feed end ########################\n");

    return info;
}

} // namespace Syndication
