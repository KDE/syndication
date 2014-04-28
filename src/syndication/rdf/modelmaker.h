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
#ifndef SYNDICATION_RDF_MODELMAKER_H
#define SYNDICATION_RDF_MODELMAKER_H

#include <syndication_export.h>

class QDomDocument;
class QDomElement;

namespace boost {
    template <class T> class shared_ptr;
}

namespace Syndication {
namespace RDF {

class Model;
class Resource;
//@cond PRIVATE
typedef boost::shared_ptr<Resource> ResourcePtr;
//@endcond

/**
 * An RDF parser, used to parse an RDF model from RDF/XML. It doesn't support
 * the complete RDF specification, but suffices for our purposes.
 * 
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT ModelMaker
{
    public:
    
        /**
         * parses an RDF model from RDF/XML
         * @param doc an DOM document, must contain RDF/XML
         * @return the parsed model, or an empty model if parsing failed
         */
        Model createFromXML(const QDomDocument& doc);
    
    private:
    
        ResourcePtr readResource(Model& model, const QDomElement& el);
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_MODELMAKER_H
