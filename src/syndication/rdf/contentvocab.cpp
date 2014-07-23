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

#include "contentvocab.h"
#include "property.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

class ContentVocab::ContentVocabPrivate
{
public:

    QString namespaceURI;
    PropertyPtr encoded;

    static ContentVocab *sSelf;
    static void cleanupContentVocab()
    {
        delete sSelf;
        sSelf = 0;
    }
};
ContentVocab *ContentVocab::ContentVocabPrivate::sSelf = 0;

ContentVocab::ContentVocab() : d(new ContentVocabPrivate)
{
    QString ns = QLatin1String("http://purl.org/rss/1.0/modules/content/");

    d->namespaceURI = ns;

    d->encoded = PropertyPtr(new Property(ns + QLatin1String("encoded")));

}

ContentVocab::~ContentVocab()
{
    delete d;
}

ContentVocab *ContentVocab::self()
{
    static ContentVocabPrivate p;
    if (!p.sSelf) {
        p.sSelf = new ContentVocab;
        qAddPostRoutine(ContentVocabPrivate::cleanupContentVocab);
    }
    return p.sSelf;
}

const QString &ContentVocab::namespaceURI() const
{
    return d->namespaceURI;
}

PropertyPtr ContentVocab::encoded() const
{
    return d->encoded;
}

} // namespace RDF
} // namespace Syndication
