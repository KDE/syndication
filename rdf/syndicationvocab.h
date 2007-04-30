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

#ifndef SYNDICATION_RDF_SYNDICATIONVOCAB_H
#define SYNDICATION_RDF_SYNDICATIONVOCAB_H

#include <syndication/ksyndication.h>

class QString;

namespace boost {
    template <class T> class shared_ptr;
}

namespace Syndication {
    
namespace RDF {

//@cond PRIVATE
class Property;
typedef boost::shared_ptr<Property> PropertyPtr;
//@endcond

/**
 * Singleton providing Property constants for 
 * the Syndication module.
 * For a specification, see
 * http://web.resource.org/rss/1.0/modules/syndication/
 * 
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT SyndicationVocab
{
    public:

        /**
         * destructor
         */
        ~SyndicationVocab();
        
        /**
         * returns the singleton instance
         */
        static SyndicationVocab* self();
        
        /**
         * namespace URI of the syndication vocabulary, 
         * @p "http://purl.org/rss/1.0/modules/syndication/"
         */
        const QString& namespaceURI() const;

        /**
         * updatePeriod property, see Syndication::updatePeriod() for more
         * information.
         */
        PropertyPtr updatePeriod() const;
        
        /**
         * updateFrequency property, see Syndication::updateFrequency() for more
         * information.
         */
        PropertyPtr updateFrequency() const;
        
        /**
         * updateBase property, see Syndication::updateBase() for more
         * information.
         */
        PropertyPtr updateBase() const;
                
    private:
        SyndicationVocab();

        class SyndicationVocabPrivate;
        SyndicationVocabPrivate * const d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_SYNDICATIONVOCAB_H
