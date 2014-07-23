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

#include "content.h"

#include <tools.h>

#include <QtCore/QByteArray>
#include <QtXml/QDomElement>
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace Syndication
{
namespace Atom
{

class Content::ContentPrivate
{
public:

    ContentPrivate() : formatIdentified(false)
    {
    }
    mutable Format format;
    mutable bool formatIdentified;
};

Content::Content() : ElementWrapper(), d(new ContentPrivate)
{
}

Content::Content(const QDomElement &element) : ElementWrapper(element), d(new ContentPrivate)
{
}

Content::Content(const Content &other) : ElementWrapper(other), d(other.d)
{
}

Content::~Content()
{
}

Content &Content::operator=(const Content &other)
{
    ElementWrapper::operator=(other);
    d = other.d;
    return *this;
}

QString Content::type() const
{
    return attribute(QLatin1String("type"));
}

QString Content::src() const
{
    return completeURI(attribute(QLatin1String("src")));
}

QByteArray Content::asByteArray() const
{
    if (!isBinary()) {
        return QByteArray();
    }
    return QByteArray::fromBase64(text().trimmed().toLatin1());
}

//@cond PRIVATE
static QStringList xmltypes;
//@endcond

Content::Format Content::mapTypeToFormat(const QString &typep,  const QString &src)
{
    QString type = typep;
    //"If neither the type attribute nor the src attribute is provided,
    //Atom Processors MUST behave as though the type attribute were
    //present with a value of "text""
    if (type.isNull() && src.isEmpty()) {
        type = QLatin1String("text");
    }

    if (type == QLatin1String("html")
            || type == QLatin1String("text/html")) {
        return EscapedHTML;
    }

    if (type == QLatin1String("text")
            || (type.startsWith(QLatin1String("text/"), Qt::CaseInsensitive)
                && !type.startsWith(QLatin1String("text/xml"), Qt::CaseInsensitive))
       ) {
        return PlainText;
    }

    if (xmltypes.isEmpty()) {
        xmltypes.append(QLatin1String("xhtml"));
        xmltypes.append(QLatin1String("application/xhtml+xml"));
        // XML media types as defined in RFC3023:
        xmltypes.append(QLatin1String("text/xml"));
        xmltypes.append(QLatin1String("application/xml"));
        xmltypes.append(QLatin1String("text/xml-external-parsed-entity"));
        xmltypes.append(QLatin1String("application/xml-external-parsed-entity"));
        xmltypes.append(QLatin1String("application/xml-dtd"));
        xmltypes.append(QLatin1String("text/x-dtd")); // from shared-mime-info
    }

    if (xmltypes.contains(type)
            || type.endsWith(QLatin1String("+xml"), Qt::CaseInsensitive)
            || type.endsWith(QLatin1String("/xml"), Qt::CaseInsensitive)) {
        return XML;
    }

    return Binary;
}

Content::Format Content::format() const
{
    if (d->formatIdentified == false) {
        d->format = mapTypeToFormat(type(), src());
        d->formatIdentified = true;
    }
    return d->format;
}

bool Content::isBinary() const
{
    return format() == Binary;
}

bool Content::isContained() const
{
    return src().isEmpty();
}

bool Content::isPlainText() const
{
    return format() == PlainText;
}

bool Content::isEscapedHTML() const
{
    return format() == EscapedHTML;
}

bool Content::isXML() const
{
    return format() == XML;
}

QString Content::asString() const
{
    Format f = format();

    if (f == PlainText) {
        return plainTextToHtml(text()).trimmed();
    } else if (f == EscapedHTML) {
        return text().trimmed();
    } else if (f == XML) {
        return childNodesAsXML().trimmed();
    }

    return QString();
}

QString Content::debugInfo() const
{
    QString info;
    info += QLatin1String("### Content: ###################\n");
    info += QLatin1String("type: #") + type() + QLatin1String("#\n");
    if (!src().isNull()) {
        info += QLatin1String("src: #") + src() + QLatin1String("#\n");
    }
    if (!isBinary()) {
        info += QLatin1String("content: #") + asString() + QLatin1String("#\n");
    } else {
        info += QLatin1String("binary length: #") + QString::number(asByteArray().size()) + QLatin1String("#\n");
    }
    info += QLatin1String("### Content end ################\n");

    return info;
}

} // namespace Atom
} //namespace Syndication
