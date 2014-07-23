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
#ifndef SYNDICATION_RDF_NODE_H
#define SYNDICATION_RDF_NODE_H

#include <QtCore/QString>
#include <syndication_export.h>
#include <boost/shared_ptr.hpp>

namespace Syndication
{
namespace RDF
{

class Model;
class Node;
class NodeVisitor;
//@cond PRIVATE
typedef boost::shared_ptr<Node> NodePtr;
//@endcond

/**
 * an RDF node, abstract baseclass for all RDF node types, like resources and
 * literals
 */
class SYNDICATION_EXPORT Node
{
public:

    /**
     * destructor
     */
    virtual ~Node();

    /**
     * Used by visitors for double dispatch. See NodeVisitor
     * for more information.
     * @param visitor the visitor calling the method
     * @param ptr a shared pointer object for this node
     */
    virtual void accept(NodeVisitor *visitor, NodePtr ptr);

    /**
     * checks whether two nodes are equal. The meaning of equality
     * is defined per subclass (e.g. equality of URIs, IDs etc.)
     *
     * @param other the node to compare to
     */
    virtual bool operator==(const Node &other) const = 0;

    /**
     * returns a copy of the object. Must be implemented
     * by subclasses to return a copy using the concrete
     * type
     */
    virtual Node *clone() const = 0;

    /**
     * returns whether this node is a null node
     */
    virtual bool isNull() const = 0;

    /**
     * returns whether this node is a resource
     */
    virtual bool isResource() const = 0;

    /**
     * returns whether this node is a property
     */
    virtual bool isProperty() const = 0;

    /**
     * returns whether this node is a literal
     */
    virtual bool isLiteral() const = 0;

    /**
     * returns whether this node is an RDF sequence
     */
    virtual bool isSequence() const = 0;

    /**
     * returns whether this node is an anonymous resource
     */
    virtual bool isAnon() const = 0;

    /**
     * the identifier of this node. the ID is unique per model
     * and set by the associated model at creation time.
     */
    virtual unsigned int id() const = 0;

    /**
     * returns a textual representation of the node.
     * This is the literal string for literals, and a null string for other
     * node types.
     */
    virtual QString text() const = 0;

    /**
     * used in Model
     * @internal
     */
    virtual void setModel(const Model &model) = 0;

    /**
     *  used in Model
     * @internal
     */
    virtual void setId(unsigned int id) = 0;

protected:

    /**
     * used to generate unique IDs for node objects
     */
    static unsigned int idCounter;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_NODE_H
