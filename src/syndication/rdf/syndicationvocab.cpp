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

#include "syndicationvocab.h"
#include "property.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

class SyndicationVocab::SyndicationVocabPrivate
{
public:

    QString namespaceURI;
    PropertyPtr updatePeriod;
    PropertyPtr updateFrequency;
    PropertyPtr updateBase;

    static SyndicationVocab *sSelf;
    static void cleanupSyndicationVocab()
    {
        delete sSelf;
        sSelf = 0;
    }
};
SyndicationVocab *SyndicationVocab::SyndicationVocabPrivate::sSelf = 0;

SyndicationVocab::SyndicationVocab() : d(new SyndicationVocabPrivate)
{
    QString ns = QLatin1String("http://purl.org/rss/1.0/modules/syndication/");

    d->namespaceURI = ns;

    d->updatePeriod = PropertyPtr(new Property(ns + QLatin1String("updatePeriod")));
    d->updateFrequency = PropertyPtr(new Property(ns + QLatin1String("updateFrequency")));
    d->updateBase = PropertyPtr(new Property(ns + QLatin1String("updateBase")));

}

SyndicationVocab::~SyndicationVocab()
{
    delete d;
}

SyndicationVocab *SyndicationVocab::self()
{
    static SyndicationVocabPrivate p;
    if (!p.sSelf) {
        p.sSelf = new SyndicationVocab;
        qAddPostRoutine(SyndicationVocabPrivate::cleanupSyndicationVocab);
    }
    return p.sSelf;
}

const QString &SyndicationVocab::namespaceURI() const
{
    return d->namespaceURI;
}

PropertyPtr SyndicationVocab::updatePeriod() const
{
    return d->updatePeriod;
}

PropertyPtr SyndicationVocab::updateFrequency() const
{
    return d->updateFrequency;
}

PropertyPtr SyndicationVocab::updateBase() const
{
    return d->updateBase;
}

} // namespace RDF
} // namespace Syndication
