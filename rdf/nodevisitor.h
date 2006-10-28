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
#ifndef SYNDICATION_RDF_NODEVISITOR_H
#define SYNDICATION_RDF_NODEVISITOR_H

#include "ksyndication.h"

namespace Syndication {

template <class T> class SharedPtr;

namespace RDF {

class Literal;
typedef SharedPtr<Literal> LiteralPtr;
class Node;
typedef SharedPtr<Node> NodePtr;
class Property;
typedef SharedPtr<Property> PropertyPtr;
class Resource;
typedef SharedPtr<Resource> ResourcePtr;
class Sequence;
typedef SharedPtr<Sequence> SequencePtr;

/**
 * Visitor interface, following the Visitor design pattern. Use this if you
 * want to process nodes and the way how to handle the nodes depends
 * on it's concrete type (e.g. Resource or Literal).
 *
 * TODO: insert code example
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT NodeVisitor
{
    public:

        /**
         * destructor
         */
        virtual ~NodeVisitor();

        /**
         * call this method to handle a node. Depending on the concrete type
         * of the node, a specialized visit method is called.
         *
         * @param node the node to process
         */
        virtual void visit(NodePtr node);

        /**
         * reimplement this method to handle literals.
         *
         * @param item the literal to visit
         * @return whether the visitor handled the literal.
         * Reimplementations of this method must return @p true.
         */
        virtual bool visitLiteral(LiteralPtr);

        /**
         * reimplement this method to handle nodes that weren't handled 
         * by the more specific method.
         *
         * @param item the node to visit
         * @return whether the visitor handled the node.
         * Reimplementations of this method must return @p true.
         */
        virtual bool visitNode(NodePtr);

        /**
         * reimplement this method to handle properties.
         *
         * @param item the property to visit
         * @return whether the visitor handled the property.
         * Reimplementations of this method must return @p true.
         */
        virtual bool visitProperty(PropertyPtr);

        /**
         * reimplement this method to handle resources.
         *
         * @param item the resource to visit
         * @return whether the visitor handled the resource.
         * Reimplementations of this method must return @p true.
         */
        virtual bool visitResource(ResourcePtr);

        /**
         * reimplement this method to handle sequences.
         *
         * @param item the sequence to visit
         * @return whether the visitor handled the sequence.
         * Reimplementations of this method must return @p true.
         */
        virtual bool visitSequence(SequencePtr);
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_NODEVISITOR_H
