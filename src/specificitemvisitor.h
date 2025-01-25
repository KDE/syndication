/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_SPECIFICITEMVISITOR_H
#define SYNDICATION_SPECIFICITEMVISITOR_H

#include "syndication_export.h"

namespace Syndication
{
class SpecificItem;

namespace Atom
{
class Entry;
}

namespace RDF
{
class Item;
}

namespace RSS2
{
class Item;
}

/*!
 * \class Syndication::SpecificItemVisitor
 * \inmodule Syndication
 * \inheaderfile Syndication/SpecificItemVisitor
 *
 * \brief Visitor interface, following the Visitor design pattern.
 *
 * Use this if you
 * want to process items and the way how to handle the items depends
 * on it's concrete type (e.g. RSS2::Item, RDF::Item...).
 *
 * TODO: insert code example
 */
class SYNDICATION_EXPORT SpecificItemVisitor // krazy:exclude=dpointer
{
public:
    virtual ~SpecificItemVisitor();

    /*!
     * call this method to handle an item. Depending on the concrete type
     * of the item, a specialized visit method is called.
     *
     * \a item the item to process
     *
     * Returns whether this visitor handles the type of the item
     */
    virtual bool visit(SpecificItem *item);

    /*!
     * reimplement this method to handle RSS2 items.
     *
     * \a item the RSS2 item to visit
     *
     * Returns whether the visitor handled the item.
     *
     * Reimplementations of this method must return \c true.
     */
    virtual bool visitRSS2Item(Syndication::RSS2::Item *item);

    /*!
     * reimplement this method to handle RDF items.
     *
     * \a item the RDF item to visit
     *
     * Returns whether the visitor handled the item.
     *
     * Reimplementations of this method must return \c true.
     */
    virtual bool visitRDFItem(Syndication::RDF::Item *item);

    /*!
     * reimplement this method to handle Atom entries.
     *
     * \a item the Atom entry to visit
     *
     * Returns whether the visitor handled the entry.
     *
     * Reimplementations of this method must return \c true.
     */
    virtual bool visitAtomEntry(Syndication::Atom::Entry *item);
};

} // namespace Syndication

#endif // SYNDICATION_SPECIFICITEMVISITOR_H
