/*
 * This file is part of the syndication library
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
 * You must have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */
#ifndef SYNDICATION_SPECIFICITEMVISITOR_H
#define SYNDICATION_SPECIFICITEMVISITOR_H

#include "ksyndication_export.h"

namespace Syndication {

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

/**
 * Visitor interface, following the Visitor design pattern. Use this if you
 * want to process items and the way how to handle the items depends
 * on it's concrete type (e.g. RSS2::Item, RDF::Item...).
 *
 * TODO: insert code example
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT SpecificItemVisitor
{
    public:

        /**
         * destructor
         */
        virtual ~SpecificItemVisitor();

        /**
         * call this method to handle an item. Depending on the concrete type
         * of the item, a specialized visit method is called.
         *
         * @param item the item to process
         * @return whether this visitor handles the type of the item
         */
        virtual bool visit(SpecificItem* item);

        /**
         * reimplement this method to handle RSS2 items.
         *
         * @param item the RSS2 item to visit
         * @return whether the visitor handled the item.
         * Reimplementations of this method must return @c true.
         */
        virtual bool visitRSS2Item(Syndication::RSS2::Item* item);

        /**
         * reimplement this method to handle RDF items.
         *
         * @param item the RDF item to visit
         * @return whether the visitor handled the item.
         * Reimplementations of this method must return @c true.
         */
        virtual bool visitRDFItem(Syndication::RDF::Item* item);

        /**
         * reimplement this method to handle Atom entries.
         *
         * @param item the Atom entry to visit
         * @return whether the visitor handled the entry.
         * Reimplementations of this method must return @c true.
         */
        virtual bool visitAtomEntry(Syndication::Atom::Entry* item);
};

} // namespace Syndication

#endif // SYNDICATION_SPECIFICITEMVISITOR_H
