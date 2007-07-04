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

#ifndef SYNDICATION_RDF_LITERAL_H
#define SYNDICATION_RDF_LITERAL_H

#include <syndication/rdf/node.h>

#include <boost/shared_ptr.hpp>

namespace Syndication {
namespace RDF {

class Literal;

//@cond PRIVATE
typedef boost::shared_ptr<Literal> LiteralPtr;
//@endcond

/**
 * a node type representing simple string values. Literals can
 * be object of statement, but neither subject nor predicate.
 */
class SYNDICATION_EXPORT Literal : public Node
{
    public:

        /**
         * creates a null literal. text() will return a null string.
         */
        Literal();
        
        /**
         * copies a literal node
         * 
         * @param other the literal node to copy
         */
        Literal(const Literal& other);
        
        /**
         * creates a new literal node with a given text
         * 
         * @param text the literal string
         */
        explicit Literal(const QString& text);
        
        /**
         * destructor
         */
        virtual ~Literal();

        /**
         * assigns another literal
         * 
         * @param other the literal to assign
         */
        virtual Literal& operator=(const Literal& other);
        
        /**
         * two literal nodes are equal iff their text _and_ ID's 
         * are equal.
         */
        virtual bool operator==(const Node& other) const;

        /**
         * clones the literal node.
         */
        virtual Literal* clone() const;
        
        /**
         * Used by visitors for double dispatch. See NodeVisitor
         * for more information.
         * @param visitor the visitor calling the method
         * @param ptr a shared pointer object for this node
         */
        virtual void accept( NodeVisitor* visitor, NodePtr ptr);

        /**
         * returns whether this node is a null node
         */
        virtual bool isNull() const;
        
        /**
         * the identifier of this node. the ID is unique per model
         * and set by the associated model at creation time.
         */
        virtual unsigned int id() const;
        
        /**
         * returns false, as a literal is not a resource
         */
        virtual bool isResource() const;
        /**
         * returns false, as a literal is not a property
         */
        virtual bool isProperty() const;
        
        /**
         * returns true for literals
         */
        virtual bool isLiteral() const;
        
        /**
         * returns false, literals are not anonymous resources
         */
        virtual bool isAnon() const;
        
        /**
         * returns false, literals are not sequences
         */
        virtual bool isSequence() const;

        /**
         * implicit conversion to string. returns text()
         */
        virtual operator QString() const;
        
        /**
         * the string value of the literal
         */
        virtual QString text() const;
        
        /**
         * used in Model
         * @internal
         */
        virtual void setModel(const Model& model);
        
        /**
         * used in Model
         * @internal
         */
        virtual void setId(unsigned int id);

    private:
        class LiteralPrivate;
        typedef boost::shared_ptr<LiteralPrivate> LiteralPrivatePtr;
        LiteralPrivatePtr d;
};


} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_LITERAL_H
