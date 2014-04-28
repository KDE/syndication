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
#ifndef SYNDICATION_RDF_SEQUENCE_H
#define SYNDICATION_RDF_SEQUENCE_H

#include <syndication_export.h>
#include <Syndication/rdf/resource.h>

#include <boost/shared_ptr.hpp>

template <class T> class QList;

namespace Syndication {
namespace RDF {

//@cond PRIVATE
class Sequence;
typedef boost::shared_ptr<Sequence> SequencePtr;
//@endcond

/**
 * Sequence container, a sequence contains an ordered list
 * of RDF nodes. (opposed to the usually unordered graph
 * structure)
 */
class SYNDICATION_EXPORT Sequence : public Resource
{
    public:

        /**
         * creates a null sequence
         */
        Sequence();
        
        /**
         * creates a sequence with the given URI. Do not use this directly, 
         * use Model::createSequence() instead.
         */
        explicit Sequence(const QString& uri);
        
        /**
         * copies a sequence
         * 
         * @param other sequence
         */
        Sequence(const Sequence& other);
        
        /**
         * destructor
         */
        virtual ~Sequence();

        /**
         * assigns another sequence
         * 
         * @param other the sequence to assign
         */
        virtual Sequence& operator=(const Sequence& other);

         /**
         * Used by visitors for double dispatch. See NodeVisitor
         * for more information.
         * @param visitor the visitor calling the method
         * @param ptr a shared pointer object for this node
         */
        virtual void accept(NodeVisitor* visitor, NodePtr ptr);

        /**
         * creates a copy of the sequence
         */
        virtual Sequence* clone() const;

        /**
         * appends a node at the end of the sequence
         * 
         * @param node the RDF node to append to the sequence
         */
        virtual void append(NodePtr node);
        
        /**
         * the list of the list items in the sequence, in the 
         * specified order
         */
        virtual QList<NodePtr> items() const;
        
        /**
         * returns @p true
         */
        virtual bool isSequence() const;

    private:

        class SequencePrivate;
        boost::shared_ptr<SequencePrivate> d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_SEQUENCE_H
