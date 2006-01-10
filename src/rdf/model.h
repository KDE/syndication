/*
 * This file is part of libsyndication
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
#ifndef LIBSYNDICATION_RDF_MODEL_H
#define LIBSYNDICATION_RDF_MODEL_H

#include <ksharedptr.h>

template <class T> class QList;
class QString;

namespace LibSyndication {
namespace RDF {

class Node;
class Property;
class Resource;
class Statement;

class Model
{
    public:

        Model();
        Model(const Model& other);

        virtual ~Model();

        Model& operator=(const Model& other);
        bool operator==(const Model& other) const;

        virtual Resource createResource(const QString& uri) const;

        virtual void addStatement(const Statement& statement);
        virtual void addStatement(const Resource& subject, const Property& predicate, const Node& object);
        virtual bool isEmpty() const;
        virtual bool resourceHasProperty(const Resource& resource, const Property& property) const;
        virtual Statement resourceProperty(const Resource& resource, const Property& property) const;
    
        virtual QList<Statement> statements() const;
        virtual QList<Resource*> resourcesWithType(const Resource& type) const;
        virtual QList<Resource> listSubjects() const;

    private:
        class ModelPrivate;
        KSharedPtr<ModelPrivate> d;
};


} // namespace RDF
} // namespace LibSyndication

#endif // LIBSYNDICATION_RDF_MODEL_H