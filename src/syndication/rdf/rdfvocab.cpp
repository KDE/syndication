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

#include "rdfvocab.h"
#include "model.h"
#include "property.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

class RDFVocab::RDFVocabPrivate
{
public:

    QString namespaceURI;
    ResourcePtr seq;
    PropertyPtr type;
    PropertyPtr li;

    static RDFVocab *sSelf;
    static void cleanupRDFVocab()
    {
        delete sSelf;
        sSelf = 0;
    }
};
RDFVocab *RDFVocab::RDFVocabPrivate::sSelf = 0;

RDFVocab *RDFVocab::self()
{
    static RDFVocabPrivate p;
    if (!p.sSelf) {
        p.sSelf = new RDFVocab;
        qAddPostRoutine(RDFVocabPrivate::cleanupRDFVocab);
    }
    return p.sSelf;
}

RDFVocab::RDFVocab() : d(new RDFVocabPrivate)
{
    QString ns = QLatin1String("http://www.w3.org/1999/02/22-rdf-syntax-ns#");

    d->namespaceURI = ns;

    d->seq = ResourcePtr(new Resource(ns + QLatin1String("Seq")));
    d->type = PropertyPtr(new Property(ns + QLatin1String("type")));
    d->li = PropertyPtr(new Property(ns + QLatin1String("li")));
}

RDFVocab::~RDFVocab()
{
    delete d;
}

ResourcePtr RDFVocab::seq()
{
    return d->seq;
}

PropertyPtr RDFVocab::type()
{
    return d->type;
}

PropertyPtr RDFVocab::li()
{
    return d->li;
}

QString RDFVocab::namespaceURI()
{
    return d->namespaceURI;
}

} // namespace RDF
} // namespace Syndication
