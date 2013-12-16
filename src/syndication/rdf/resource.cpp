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

#include "resource.h"
#include "model.h"
#include "model_p.h"
#include "nodevisitor.h"
#include "property.h"
#include "statement.h"

#include <krandom.h>

#include <QtCore/QList>
#include <QtCore/QString>

#include <boost/weak_ptr.hpp>

using namespace boost;

namespace Syndication {
namespace RDF {

class Resource::ResourcePrivate
{
    public:

        QString uri;
        weak_ptr<Model::ModelPrivate> model;
        bool isAnon;
        unsigned int id;

        bool operator==(const ResourcePrivate& other) const
        {
            if (!isAnon && !other.isAnon)
                return uri == other.uri;
            else
                return id == other.id;
        }
};

Resource::Resource(const Resource& other) : Node(other)
{
    *this = other;
}

Resource::Resource() : d()
{
}

Resource::Resource(const QString& uri) : d(new ResourcePrivate)
{
    if (uri.isNull())
    {
        d->uri = KRandom::randomString(10); // TODO: ensure uniqueness
        d->isAnon = true;
    }
    else
    {
        d->uri = uri;
        d->isAnon = false;
    }

    d->id = idCounter++;
}

Resource::~Resource()
{
}

Resource& Resource::operator=(const Resource& other)
{
    d = other.d;
    return *this;
}

bool Resource::operator==(const Node& other) const
{
    const Resource* o2 = dynamic_cast<const Resource*>(&other);
    if (!o2)
        return false;

    if (!d || !o2->d)
        return d == o2->d;
    return *d == *(o2->d);
}

bool Resource::hasProperty(PropertyPtr property) const
{
    if (!d)
        return false;
    const shared_ptr<Model::ModelPrivate> m = d->model.lock();
    if (!m)
        return false;
    return m->resourceHasProperty(this, property);
}

StatementPtr Resource::property(PropertyPtr property) const
{
    StatementPtr ptr(new Statement());
    if (!d)
        return ptr;
    const shared_ptr<Model::ModelPrivate> m = d->model.lock();
    if (!m)
        return ptr;
    return m->resourceProperty(this, property);
}

QList<StatementPtr> Resource::properties(PropertyPtr property) const
{
    if (!d)
        return QList<StatementPtr>();
    const shared_ptr<Model::ModelPrivate> m = d->model.lock();
    if (!m)
        return QList<StatementPtr>();

    return m->resourceProperties(this, property);
}

Resource* Resource::clone() const
{
    return new Resource(*this);
}

void Resource::accept(NodeVisitor* visitor, NodePtr ptr)
{
    ResourcePtr rptr = boost::static_pointer_cast<Resource>(ptr);
    if (!visitor->visitResource(rptr))
        Node::accept(visitor, ptr);
}

unsigned int Resource::id() const
{
    return d ? d->id : 0;
}

bool Resource::isNull() const
{
    return !d;
}

Model Resource::model() const
{
    if (!d)
        return Model();

    const shared_ptr<Model::ModelPrivate> mp = d->model.lock();

    Model m;

    if (mp)
        m.d = mp;

    return m;
}

bool Resource::isResource() const
{
    return true;
}

bool Resource::isProperty() const
{
    return false;
}

bool Resource::isLiteral() const
{
    return false;
}

bool Resource::isAnon() const
{
    return d ? d->isAnon : false;
}

bool Resource::isSequence() const
{
    return false;
}

void Resource::setModel(const Model& model)
{
    if (d)
        d->model = model.d;
}

void Resource::setId(unsigned int id)
{
    if (d)
        d->id = id;
}

QString Resource::text() const
{
    return QString();
}

QString Resource::uri() const
{
    return d ? d->uri : QString();
}

} // namespace RDF
} // namespace Syndication
