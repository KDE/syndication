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

#include "dublincorevocab.h"
#include "property.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

class DublinCoreVocab::DublinCoreVocabPrivate
{
public:

    QString namespaceURI;
    PropertyPtr contributor;
    PropertyPtr coverage;
    PropertyPtr creator;
    PropertyPtr date;
    PropertyPtr description;
    PropertyPtr format;
    PropertyPtr identifier;
    PropertyPtr language;
    PropertyPtr publisher;
    PropertyPtr relation;
    PropertyPtr rights;
    PropertyPtr source;
    PropertyPtr subject;
    PropertyPtr title;
    PropertyPtr type;

    static DublinCoreVocab *sSelf;
    static void cleanupDublinCoreVocab()
    {
        delete sSelf;
        sSelf = 0;
    }
};
DublinCoreVocab *DublinCoreVocab::DublinCoreVocabPrivate::sSelf = 0;

DublinCoreVocab::DublinCoreVocab() : d(new DublinCoreVocabPrivate)
{
    QString ns = QLatin1String("http://purl.org/dc/elements/1.1/");

    d->namespaceURI = ns;

    d->contributor = PropertyPtr(new Property(ns + QLatin1String("contributor")));
    d->coverage = PropertyPtr(new Property(ns + QLatin1String("coverage")));
    d->creator = PropertyPtr(new Property(ns + QLatin1String("creator")));
    d->date = PropertyPtr(new Property(ns + QLatin1String("date")));
    d->description = PropertyPtr(new Property(ns + QLatin1String("description")));
    d->format = PropertyPtr(new Property(ns + QLatin1String("format")));
    d->identifier = PropertyPtr(new Property(ns + QLatin1String("identifier")));
    d->language = PropertyPtr(new Property(ns + QLatin1String("language")));
    d->publisher = PropertyPtr(new Property(ns + QLatin1String("publisher")));
    d->relation = PropertyPtr(new Property(ns + QLatin1String("relation")));
    d->rights = PropertyPtr(new Property(ns + QLatin1String("rights")));
    d->source = PropertyPtr(new Property(ns + QLatin1String("source")));
    d->subject = PropertyPtr(new Property(ns + QLatin1String("subject")));
    d->title = PropertyPtr(new Property(ns + QLatin1String("title")));
    d->type = PropertyPtr(new Property(ns + QLatin1String("type")));

}

DublinCoreVocab::~DublinCoreVocab()
{
    delete d;
}

DublinCoreVocab *DublinCoreVocab::self()
{
    static DublinCoreVocabPrivate p;
    if (!p.sSelf) {
        p.sSelf = new DublinCoreVocab;
        qAddPostRoutine(DublinCoreVocabPrivate::cleanupDublinCoreVocab);
    }
    return p.sSelf;
}

const QString &DublinCoreVocab::namespaceURI() const
{
    return d->namespaceURI;
}

PropertyPtr DublinCoreVocab::contributor() const
{
    return d->contributor;
}

PropertyPtr DublinCoreVocab::creator() const
{
    return d->creator;
}

PropertyPtr DublinCoreVocab::coverage() const
{
    return d->coverage;
}

PropertyPtr DublinCoreVocab::date() const
{
    return d->date;
}

PropertyPtr DublinCoreVocab::description() const
{
    return d->description;
}

PropertyPtr DublinCoreVocab::format() const
{
    return d->format;
}

PropertyPtr DublinCoreVocab::identifier() const
{
    return d->identifier;
}

PropertyPtr DublinCoreVocab::language() const
{
    return d->language;
}

PropertyPtr DublinCoreVocab::publisher() const
{
    return d->publisher;
}

PropertyPtr DublinCoreVocab::relation() const
{
    return d->relation;
}

PropertyPtr DublinCoreVocab::rights() const
{
    return d->rights;
}

PropertyPtr DublinCoreVocab::source() const
{
    return d->source;
}

PropertyPtr DublinCoreVocab::subject() const
{
    return d->subject;
}

PropertyPtr DublinCoreVocab::title() const
{
    return d->title;
}

PropertyPtr DublinCoreVocab::type() const
{
    return d->type;
}

} // namespace RDF
} // namespace Syndication
