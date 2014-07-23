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

#ifndef SYNDICATION_RDF_DUBLINCOREVOCAB_H
#define SYNDICATION_RDF_DUBLINCOREVOCAB_H

#include <syndication/rdf/property.h>

class QString;

namespace Syndication
{
namespace RDF
{

/**
 * Singleton holding RDF class and property constants of the Dublin Core
 * vocabulary. See http://dublincore.org/documents/dces/ for a
 * specification.
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT DublinCoreVocab
{
public:

    /**
     * returns the singleton instance
     */
    static DublinCoreVocab *self();

    /**
     * destructor
     */
    ~DublinCoreVocab();

    /**
     * the namespace of the Dublin Core vocabulary,
     * http://purl.org/dc/elements/1.1/
     */
    const QString &namespaceURI() const;

    /**
     * dc:contributor property. See DublinCore::contributor() for
     * an explanation.
     */
    PropertyPtr contributor() const;

    /**
     * dc:creator property. See DublinCore::creator() for
     * an explanation.
     */
    PropertyPtr creator() const;

    /**
     * dc:coverage property. See DublinCore::coverage() for
     * an explanation.
     */
    PropertyPtr coverage() const;

    /**
     * dc:date property. See DublinCore::date() for
     * an explanation.
     */
    PropertyPtr date() const;

    /**
     * dc:description property. See DublinCore::description() for
     * an explanation.
     */
    PropertyPtr description() const;

    /**
     * dc:format property. See DublinCore::format() for
     * an explanation.
     */
    PropertyPtr format() const;

    /**
     * dc:identifier property. See DublinCore::identifier() for
     * an explanation.
     */
    PropertyPtr identifier() const;

    /**
     * dc:language property. See DublinCore::language() for
     * an explanation.
     */
    PropertyPtr language() const;

    /**
     * dc:publisher property. See DublinCore::publisher() for
     * an explanation.
     */
    PropertyPtr publisher() const;

    /**
     * dc:relation property. See DublinCore::relation() for
     * an explanation.
     */
    PropertyPtr relation() const;

    /**
     * dc:rights property. See DublinCore::rights() for
     * an explanation.
     */
    PropertyPtr rights() const;

    /**
     * dc:source property. See DublinCore::source() for
     * an explanation.
     */
    PropertyPtr source() const;

    /**
     * dc:subject property. See DublinCore::subject() for
     * an explanation.
     */
    PropertyPtr subject() const;

    /**
     * dc:title property. See DublinCore::title() for
     * an explanation.
     */
    PropertyPtr title() const;

    /**
     * dc:type property. See DublinCore::type() for
     * an explanation.
     */
    PropertyPtr type() const;

private:
    DublinCoreVocab();

    class DublinCoreVocabPrivate;
    DublinCoreVocabPrivate *const d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_DUBLINCOREVOCAB_H
