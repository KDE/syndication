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
#ifndef SYNDICATION_RDF_STATEMENT_H
#define SYNDICATION_RDF_STATEMENT_H

#include <syndication/rdf/property.h>

#include <boost/shared_ptr.hpp>

class QString;

namespace Syndication {
namespace RDF {

//@cond PRIVATE
class Statement;
typedef boost::shared_ptr<Statement> StatementPtr;
//@endcond

/**
 * An RDF statement, consisting of a triple
 * (subject, predicate, object).
 */
class SYNDICATION_EXPORT Statement
{
    friend class Model;
    public:

        /**
         * creates a null statement
         */
        Statement();
        
        /**
         * creates a copy of another statement
         * 
         * @param other the statement to copy
         */
        Statement(const Statement& other);
        
        /**
         * creates a statement
         * Do not call this in your code, use Model::createStatement() instead.
         * 
         * @param subject the subject resource of the statement
         * @param predicate the predicate of the statement
         * @param object the object node of the statement
         */
        Statement(ResourcePtr subject, PropertyPtr predicate, NodePtr object);
        
        /**
         * destructor
         */
        virtual ~Statement();

        /**
         * assigns another statement
         * 
         * @param other the statement to assign
         */
        Statement& operator=(const Statement& other);
        
        /**
         * returns whether two statements are equal.
         * Currently statements are equal, if they are from the same model (!)
         * and subject, predicate and object are equal.
         * 
         * @param other the statement to compare to
         */
        virtual bool operator==(const Statement& other) const;

        /**
         * returns whether this statement is a null statement (i.e. was created
         * using Statement())
         */
        virtual bool isNull() const;

        /**
         * the subject of the statement.
         */
        virtual ResourcePtr subject() const;

        /**
         * the predicate of the statement
         */
        virtual PropertyPtr predicate() const;

        /**
         * the object of the statement
         */
        virtual NodePtr object() const;

        /**
         * returns the object of this statement as resource, if possible.
         *
         * @return the object node as Resource, or @c null if the object
         * is not a resource
         */
        virtual ResourcePtr asResource() const;

        /**
         * returns the object of this statement as string, if possible.
         *
         * @return the literal text as QString, or a null string if the object
         * is not a literal
         */
        virtual QString asString() const;


    private:
        class StatementPrivate;
        boost::shared_ptr<StatementPrivate> d;
};


} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_STATEMENT_H
