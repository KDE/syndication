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

#include <QString>
#include <syndication/rdf/node.h>

namespace Syndication
{
namespace RDF
{

class Literal;

//@cond PRIVATE
typedef QSharedPointer<Literal> LiteralPtr;
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
    Literal(const Literal &other);

    /**
     * creates a new literal node with a given text
     *
     * @param text the literal string
     */
    explicit Literal(const QString &text);

    /**
     * destructor
     */
    virtual ~Literal();

    /**
     * assigns another literal
     *
     * @param other the literal to assign
     */
    virtual Literal &operator=(const Literal &other);

    /**
     * two literal nodes are equal iff their text _and_ ID's
     * are equal.
     */
    bool operator==(const Node &other) const override;

    /**
     * clones the literal node.
     */
    Literal *clone() const override;

    /**
     * Used by visitors for double dispatch. See NodeVisitor
     * for more information.
     * @param visitor the visitor calling the method
     * @param ptr a shared pointer object for this node
     */
    void accept(NodeVisitor *visitor, NodePtr ptr) override;

    /**
     * returns whether this node is a null node
     */
    bool isNull() const override;

    /**
     * the identifier of this node. the ID is unique per model
     * and set by the associated model at creation time.
     */
    unsigned int id() const override;

    /**
     * returns false, as a literal is not a resource
     */
    bool isResource() const override;
    /**
     * returns false, as a literal is not a property
     */
    bool isProperty() const override;

    /**
     * returns true for literals
     */
    bool isLiteral() const override;

    /**
     * returns false, literals are not anonymous resources
     */
    bool isAnon() const override;

    /**
     * returns false, literals are not sequences
     */
    bool isSequence() const override;

    /**
     * implicit conversion to string. returns text()
     */
    virtual operator QString() const;

    /**
     * the string value of the literal
     */
    QString text() const override;

    /**
     * used in Model
     * @internal
     */
    void setModel(const Model &model) override;

    /**
     * used in Model
     * @internal
     */
    void setId(unsigned int id) override;

private:
    class LiteralPrivate;
    typedef QSharedPointer<LiteralPrivate> LiteralPrivatePtr;
    LiteralPrivatePtr d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_LITERAL_H
