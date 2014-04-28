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
#include "constants.h"
#include "tools.h"

#include <Syndication/elementwrapper.h>
#include <Syndication/tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QString>

namespace Syndication {

namespace Atom {

QString extractAtomText(const Syndication::ElementWrapper& parent, const QString& tagname)
{
    QString str;

    QDomElement el = parent.firstElementByTagNameNS(atom1Namespace(), tagname);

    bool isCDATA = el.firstChild().isCDATASection();

    QString type = el.attribute(QLatin1String("type"), QLatin1String("text"));

    if (type == QLatin1String("text"))
    {
        str = parent.extractElementTextNS(atom1Namespace(), tagname).trimmed();
        if (isCDATA)
            str = resolveEntities(str);

        str = escapeSpecialCharacters(str);
    }
    else if (type == QLatin1String("html"))
    {
        str = parent.extractElementTextNS(atom1Namespace(), tagname).trimmed();
    }
    else if (type == QLatin1String("xhtml"))
    {
        str = ElementWrapper::childNodesAsXML(el).trimmed();
    }

    return str;
}

} // namespace Atom
} // namespace Syndication


