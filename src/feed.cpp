/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "feed.h"
#include "category.h"
#include "image.h"
#include "item.h"
#include "person.h"

#include <QList>
#include <QString>

namespace Syndication
{
Feed::~Feed()
{
}

QString Feed::debugInfo() const
{
    QString info = QLatin1String("# Feed begin ######################\n");

    const QString dtitle = title();
    if (!dtitle.isNull()) {
        info += QLatin1String("title: #") + dtitle + QLatin1String("#\n");
    }

    const QString dlink = link();
    if (!dlink.isNull()) {
        info += QLatin1String("link: #") + dlink + QLatin1String("#\n");
    }

    const QString ddescription = description();
    if (!ddescription.isNull()) {
        info += QLatin1String("description: #") + ddescription + QLatin1String("#\n");
    }

    const QString dcopyright = copyright();
    if (!dcopyright.isNull()) {
        info += QLatin1String("copyright: #") + dcopyright + QLatin1String("#\n");
    }

    const QString dlanguage = language();
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

    ImagePtr dicon = icon();

    if (!dicon->isNull()) {
        info += dicon->debugInfo();
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
