/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2005 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "documentsource.h"
#include "tools.h"

#include <QByteArray>
#include <QDomDocument>
#include <QXmlSimpleReader>

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
        reader.setFeature(QStringLiteral("http://xml.org/sax/features/namespaces"), true);

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
