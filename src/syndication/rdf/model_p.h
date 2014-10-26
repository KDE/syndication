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
#ifndef SYNDICATION_RDF_MODEL_P_H
#define SYNDICATION_RDF_MODEL_P_H

#include "model.h"
#include "literal.h"
#include "nodevisitor.h"
#include "property.h"
#include "rdfvocab.h"
#include "resource.h"
#include "sequence.h"
#include "statement.h"

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

class Model::ModelPrivate
{
public:
    long id;
    static long idCounter;
    LiteralPtr nullLiteral;
    PropertyPtr nullProperty;
    ResourcePtr nullResource;
    StatementPtr nullStatement;
    QHash<QString, StatementPtr> statements;
    QHash<QString, QList<StatementPtr> > stmtsBySubject;

    QHash<int, NodePtr> nodes;
    QHash<QString, ResourcePtr> resources;
    QHash<QString, PropertyPtr> properties;
    QHash<QString, SequencePtr> sequences;
    bool initialized;

    class AddToHashesVisitor;

    ModelPrivate() : id(idCounter++)
    {
        addToHashesVisitor = new AddToHashesVisitor(this);
        initialized = false;
    }

    ~ModelPrivate()
    {
        delete addToHashesVisitor;
    }

    bool operator==(const ModelPrivate &other) const
    {
        return id == other.id;
    }

    class AddToHashesVisitor : public NodeVisitor
    {
    public:

        AddToHashesVisitor(ModelPrivate *parent) : p(parent)
        {}

        bool visitResource(ResourcePtr res)
        {
            visitNode(res);
            p->resources[res->uri()] = res;
            return true;
        }

        bool visitSequence(SequencePtr seq)
        {
            visitResource(seq);
            p->sequences[seq->uri()] = seq;
            return true;
        }

        bool visitProperty(PropertyPtr prop)
        {
            visitResource(prop);
            p->properties[prop->uri()] = prop;
            return true;
        }

        bool visitNode(NodePtr node)
        {
            p->nodes[node->id()] = node;
            return true;
        }

        ModelPrivate *p;
    };

    AddToHashesVisitor *addToHashesVisitor;

    bool resourceHasProperty(const Resource *resource,
                             PropertyPtr property) const;

    StatementPtr resourceProperty(const Resource *resource,
                                  PropertyPtr property) const;

    QList<StatementPtr> resourceProperties(const Resource *resource,
                                           PropertyPtr property) const;

    NodePtr nodeByID(uint id) const;

    ResourcePtr resourceByID(uint id) const;

    PropertyPtr propertyByID(uint id) const;

    LiteralPtr literalByID(uint id) const;

    void addToHashes(NodePtr node)
    {
        addToHashesVisitor->visit(node);
    }

    void addToHashes(StatementPtr stmt, const QString &key)
    {
        statements[key] = stmt;
        stmtsBySubject[stmt->subject()->uri()].append(stmt);
    }

    void removeFromHashes(const QString &key)
    {
        StatementPtr stmt = statements[key];
        if (stmt) {
            stmtsBySubject[stmt->subject()->uri()].removeAll(stmt);
        }
        statements.remove(key);

    }

    void init(const QSharedPointer<ModelPrivate> &sharedThis)
    {
        if (!initialized) {
            Model m;
            m.d = sharedThis;
            nullLiteral = LiteralPtr(new Literal());
            nullLiteral->setModel(m);
            nullProperty = PropertyPtr(new Property());
            nullProperty->setModel(m);
            nullResource = ResourcePtr(new Resource());
            nullResource->setModel(m);
            nullStatement = StatementPtr(new Statement());
            initialized = true;
        }
    }
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_MODEL_P_H
