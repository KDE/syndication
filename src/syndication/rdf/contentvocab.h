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
#ifndef SYNDICATION_RDF_CONTENTVOCAB_H
#define SYNDICATION_RDF_CONTENTVOCAB_H

#include <QtCore/QSharedPointer>

#include <syndication_export.h>

class QString;


namespace Syndication
{

namespace RDF
{

class Property;
//@cond PRIVATE
typedef QSharedPointer<Property> PropertyPtr;
//@endcond
/**
 * Singleton holding RDF class and property constants of the RSS 1.0 content
 * module. See http://web.resource.org/rss/1.0/modules/content/ for a
 * specification.
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT ContentVocab
{
public:

    /**
     * returns the singleton instance
     */
    static ContentVocab *self();

    /**
     * destructor
     */
    ~ContentVocab();

    /**
     * Namespace of the Content module
     *
     * http://purl.org/rss/1.0/modules/content/
    **/
    const QString &namespaceURI() const;

    /**
     * content:encoded property
     */
    PropertyPtr encoded() const;

private:
    ContentVocab();

    class ContentVocabPrivate;
    ContentVocabPrivate *const d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_CONTENTVOCAB_H
