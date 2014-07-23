/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2005 Frank Osterfeld <osterfeld@kde.org>
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

#include "documentsource.h"
#include "tools.h"

#include <QtCore/QByteArray>
#include <QtXml/QDomDocument>
#include <QtXml/QXmlSimpleReader>

namespace Syndication
{

class DocumentSource::DocumentSourcePrivate
{
public:
    QByteArray array;
    QString url;
    mutable QDomDocument domDoc;
    mutable bool parsed;
    mutable unsigned int hash;
    mutable bool calculatedHash;
};

DocumentSource::DocumentSource() : d(new DocumentSourcePrivate)
{
    d->parsed = true;
    d->calculatedHash = true;
    d->hash = 0;
}

DocumentSource::DocumentSource(const QByteArray &source, const QString &url) : d(new DocumentSourcePrivate)
{
    d->array = source;
    d->url = url;
    d->calculatedHash = false;
    d->parsed = false;
}

DocumentSource::DocumentSource(const DocumentSource &other) : d()
{
    *this = other;
}

DocumentSource::~DocumentSource()
{
}

DocumentSource &DocumentSource::operator=(const DocumentSource &other)
{
    d = other.d;
    return *this;
}

QByteArray DocumentSource::asByteArray() const
{
    return d->array;
}

QDomDocument DocumentSource::asDomDocument() const
{
    if (!d->parsed) {
        QXmlInputSource source;
        source.setData(d->array);

        QXmlSimpleReader reader;
        reader.setFeature(QLatin1String("http://xml.org/sax/features/namespaces"), true);

        if (!d->domDoc.setContent(&source, &reader)) {
            d->domDoc.clear();
        }

        d->parsed = true;
    }

    return d->domDoc;
}

unsigned int DocumentSource::size() const
{
    return d->array.size();
}

unsigned int DocumentSource::hash() const
{
    if (!d->calculatedHash) {
        d->hash = calcHash(d->array);
        d->calculatedHash = true;
    }

    return d->hash;
}

QString DocumentSource::url() const
{
    return d->url;
}

} // namespace Syndication
