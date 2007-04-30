/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2006 Frank Osterfeld <frank.osterfeld@kdemail.net>
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
#ifndef SYNDICATION_RDF_RSSVOCAB_H
#define SYNDICATION_RDF_RSSVOCAB_H

#include <syndication/ksyndication.h>

class QString;
class QStringList;

namespace boost {
    template <class T> class shared_ptr;
}

namespace Syndication {

namespace RDF {

//@cond PRIVATE
class Property;
typedef boost::shared_ptr<Property> PropertyPtr;
class Resource;
typedef boost::shared_ptr<Resource> ResourcePtr;
//@endcond

/**
 * Singleton holding RDF class and property constants of the RSS 1.0
 * vocabulary. See http://web.resource.org/rss/1.0/ for a specification.
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT RSSVocab
{
    public:

        /**
         * destructor
         */
        ~RSSVocab();

        /**
         * returns the singleton instance
         */
        static RSSVocab* self();

        /**
         * namespace URI of the RSS 1.0 vocabulary,
         * @c "http://web.resource.org/rss/1.0/"
         */
        const QString& namespaceURI() const;

        /**
         * RSS 1.0 title property, see Document::title() for
         * more details
         */
        PropertyPtr title() const;

        /**
         * RSS 1.0 description property, see Document::description() for
         * more details
         */
        PropertyPtr description() const;

        /**
         * RSS 1.0 link property, see Document::link() for
         * more details
         */
        PropertyPtr link() const;

        /**
         * RSS 1.0 name property, see Document::name() for
         * more details
         */
        PropertyPtr name() const;

        /**
         * RSS 1.0 url property, see Document::url() for
         * more details
         */
        PropertyPtr url() const;

        /**
         * RSS 1.0 channel class, the instance is represented by
         * Syndication::RDF::Document
         */
        ResourcePtr channel() const;
        
        /**
         * RSS 1.0 item class, the instance is represented by
         * Syndication::RDF::Item
         */
        ResourcePtr item() const;

        /**
         * RSS 1.0 items property, see Document::items() for
         * more details
         */
        PropertyPtr items() const;

        /**
         * RSS 1.0 image property, see Document::image() for
         * more details
         */
        PropertyPtr image() const;

        /**
         * RSS 1.0 textinput property, see Document::textinput() for
         * more details
         */
        PropertyPtr textinput() const;

    private:
        RSSVocab();
        
        class RSSVocabPrivate;
        RSSVocabPrivate * const d;
};

/**
 * Singleton holding RDF class and property constants of the RSS 0.9
 * vocabulary. Only used to map RSS 0.9 to 1.0.
 *
 * @author Frank Osterfeld
 */

class SYNDICATION_EXPORT RSS09Vocab
{
    public:

        /**
         * destructor
         */
        ~RSS09Vocab();

        /**
         * returns the singleton instance
         */
        static RSS09Vocab* self();

        /**
         * namespace URI of the RSS 0.9 vocabulary,
         * @c "http://web.resource.org/rss/0.9/"
         */
        const QString& namespaceURI() const;

        /**
         * RSS 0.9 title property, see Document::title() for
         * more details
         */
        PropertyPtr title() const;

        /**
         * RSS 0.9 description property, see Document::description() for
         * more details
         */
        PropertyPtr description() const;

        /**
         * RSS 0.9 link property, see Document::link() for
         * more details
         */
        PropertyPtr link() const;

        /**
         * RSS 0.9 name property, see Document::name() for
         * more details
         */
        PropertyPtr name() const;

        /**
         * RSS 0.9 url property, see Document::url() for
         * more details
         */
        PropertyPtr url() const;

        /**
         * RSS 0.9 channel class, the instance is represented by
         * Syndication::RDF::Document
         */
        ResourcePtr channel() const;

        /**
         * RSS 0.9 item class, see Document::items() for
         * more details
         */
        ResourcePtr item() const;

        /**
         * RSS 0.9 image property, see Document::image() for
         * more details
         */
        PropertyPtr image() const;

        /**
         * RSS 0.9 textinput property, see Document::textinput() for
         * more details
         */
        PropertyPtr textinput() const;

        /**
         * returns a list containing all URIs representing properties in this vocabulary
         */
        QStringList properties() const;

        /**
         * returns a list containing all URIs representing classes in this vocabulary
         */
        QStringList classes() const;

    private:
        RSS09Vocab();

        class RSS09VocabPrivate;
        RSS09VocabPrivate * const d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_RSSVOCAB_H
