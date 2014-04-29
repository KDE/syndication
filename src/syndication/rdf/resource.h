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

#ifndef SYNDICATION_RDF_RESOURCE_H
#define SYNDICATION_RDF_RESOURCE_H

#include <syndication/rdf/node.h>

#include <boost/shared_ptr.hpp>

class QString;

template <class T> class QList;

namespace Syndication {
namespace RDF {

class Model;
class Property;
typedef boost::shared_ptr<Property> PropertyPtr;
class Resource;
class Statement;
typedef boost::shared_ptr<Statement> StatementPtr;

typedef boost::shared_ptr<Resource> ResourcePtr;

/**
 * Resources are the entities in the RDF graph.
 * In RSS, e.g. the feed channel itself and the items are
 * resources.
 */
class SYNDICATION_EXPORT Resource : public Node
{
    friend class Model;

    public:

        /**
         * creates a null resource
         */
        Resource();

        /**
         * copies a resource
         *
         * @param other the resource to copy
         */
        Resource(const Resource& other);

        /**
         * creates a resource with a given URI.
         * Do not use this directly, use Model::createResource() instead.
         *
         * @param uri the URI of the new resource
         */
        explicit Resource(const QString& uri);

        /**
         * destructor
         */
        virtual ~Resource();

        /**
         * assigns a resource
         *
         * @param other the resource to assign
         */
        Resource& operator=(const Resource& other);

        /**
         * checks two resources for equality. Currently both URI (or anonID)
         * _and_ id() must be equal!
         *
         * @param other the node to compare this node to
         */
        bool operator==(const Node& other) const;

        /**
         * Used by visitors for double dispatch. See NodeVisitor
         * for more information.
         * @param visitor the visitor calling the method
         * @param ptr a shared pointer object for this node
         */
        virtual void accept(NodeVisitor* visitor,  NodePtr ptr);

        /**
         * creates a copy of the resource object
         */
        virtual Resource* clone() const;

        /**
         * the model this resource belongs to
         */
        virtual Model model() const;

        /**
         * returns whether the resource has a property @p property in the
         * associated model.
         *
         * @param property the property to check for
         */
        virtual bool hasProperty(PropertyPtr property) const;

        /**
         * returns a statement from the associated model where this resource is
         * the subject and the given property the predicate.
         *
         * @param property the property to check for
         *
         * @return the first statement found that satisfies the conditions.
         * If there are multiple statements, an arbitrary one is returned.
         */
        virtual StatementPtr property(PropertyPtr property) const;

        /**
         * returns the list of all statements from the associated model where
         * this resource is the subject and the given property the predicate.
         *
         * @param property the property to check for
         *
         * @return a list of the statements that satisfy the conditions.
         */
        virtual QList<StatementPtr> properties(PropertyPtr property) const;

        /**
         * returns whether the resource is a null resource
         */
        virtual bool isNull() const;

        /**
         * the identifier of this node. the ID is unique per model
         * and set by the associated model at creation time.
         */
        virtual unsigned int id() const;

        /**
         * returns @p true
         */
        virtual bool isResource() const;

        /**
         * returns @p false
         */
        virtual bool isLiteral() const;

        /**
         * returns @p true if this resource is also a property, @p false
         * otherwise
         */
        virtual bool isProperty() const;

        /**
         * returns whether this resource is an anonymous resource
         */
        virtual bool isAnon() const;

        /**
         * returns @p true if this resource is also a sequence, @p false
         * otherwise.
         */
        virtual bool isSequence() const;

        /**
         * returns a null string
         */
        virtual QString text() const;

        /**
         * returns the URI of the resource
         */
        virtual QString uri() const;


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

        class ResourcePrivate;
        typedef boost::shared_ptr<ResourcePrivate> ResourcePrivatePtr;
        ResourcePrivatePtr d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_RESOURCE_H
