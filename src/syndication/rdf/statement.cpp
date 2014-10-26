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

#include "statement.h"
#include "literal.h"
#include "model.h"
#include "model_p.h"
#include "property.h"
#include "resource.h"

#include <QtCore/QString>
#include <QtCore/QWeakPointer>

namespace Syndication
{
namespace RDF
{

class Statement::StatementPrivate
{
public:

    uint subjectID;
    uint predicateID;
    uint objectID;
    QWeakPointer<Model::ModelPrivate> model;

    bool operator==(const StatementPrivate &other) const
    {
        // FIXME: use better check that works also with multiple models
        return subjectID == other.subjectID &&
               predicateID == other.predicateID &&
               objectID == other.objectID;
    }
};

Statement::Statement() : d(new StatementPrivate)
{
    d->subjectID = 0;
    d->predicateID = 0;
    d->objectID = 0;
}

Statement::Statement(const Statement &other)
{
    d = other.d;
}

Statement::Statement(ResourcePtr subject, PropertyPtr predicate,
                     NodePtr object) : d(new StatementPrivate)
{
    d->model = subject->model().d;
    d->subjectID = subject->id();
    d->predicateID = predicate->id();
    d->objectID = object->id();
}

Statement::~Statement()
{
}

Statement &Statement::operator=(const Statement &other)
{
    d = other.d;
    return *this;
}

bool Statement::operator==(const Statement &other) const
{
    if (!d || !other.d) {
        return d == other.d;
    }

    return *d == *(other.d);
}

bool Statement::isNull() const
{
    return d->subjectID == 0;
}

ResourcePtr Statement::subject() const
{
    const QSharedPointer<Model::ModelPrivate> m = d ? d->model.toStrongRef() : QSharedPointer<Model::ModelPrivate>();
    return m ? m->resourceByID(d->subjectID) : ResourcePtr(new Resource);
}

PropertyPtr Statement::predicate() const
{
    const QSharedPointer<Model::ModelPrivate> m = d ? d->model.toStrongRef() : QSharedPointer<Model::ModelPrivate>();
    return m ? m->propertyByID(d->predicateID) : PropertyPtr(new Property());
}

NodePtr Statement::object() const
{
    const QSharedPointer<Model::ModelPrivate> m = d ? d->model.toStrongRef() : QSharedPointer<Model::ModelPrivate>();
    return m ? m->nodeByID(d->objectID) : NodePtr(LiteralPtr(new Literal()));
}

ResourcePtr Statement::asResource() const
{
    const QSharedPointer<Model::ModelPrivate> m = d ? d->model.toStrongRef() : QSharedPointer<Model::ModelPrivate>();

    if (isNull() || !m || !m->nodeByID(d->objectID)->isResource()) {
        return ResourcePtr(new Resource);
    }

    return m->resourceByID(d->objectID);
}

QString Statement::asString() const
{
    if (isNull()) {
        return QString();
    }

    const QSharedPointer<Model::ModelPrivate> m = d ? d->model.toStrongRef() : QSharedPointer<Model::ModelPrivate>();
    return m ? m->nodeByID(d->objectID)->text() : QString();
}

} // namespace RDF
} // namespace Syndication
