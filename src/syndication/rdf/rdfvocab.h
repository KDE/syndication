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
#ifndef SYNDICATION_RDF_RDFVOCAB_H
#define SYNDICATION_RDF_RDFVOCAB_H

#include <syndication_export.h>

class QString;

namespace boost {
    template <class T> class shared_ptr;
}

namespace Syndication {
    
namespace RDF {

class Property;
typedef boost::shared_ptr<Property> PropertyPtr;
class Resource;
typedef boost::shared_ptr<Resource> ResourcePtr;

/**
 * singleton holding RDF vocabulary, expressed as RDF.
 */
class SYNDICATION_EXPORT RDFVocab
{
    public:
    
        /**
         * returns the singleton instance
         */
        static RDFVocab* self();
        
        /**
         * destructor
         */
        ~RDFVocab();
        
        /**
         * the RDF namespace, which is
         * http://www.w3.org/1999/02/22-rdf-syntax-ns#
         */
        QString namespaceURI();

        /**
         * the sequence type
         */
        ResourcePtr seq();
        
        /**
         * the rdf:type property (A rdf:type B means A is instance of B)
         */
        PropertyPtr type();

        /**
         * the rdf:li property, used for list items in RDF containers (like
         * rdf:seq)
         */
        PropertyPtr li();
        
    private:
        RDFVocab();
                
        class RDFVocabPrivate;
        RDFVocabPrivate* const d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_RDFVOCAB_H
