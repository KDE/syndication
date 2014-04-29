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
#ifndef SYNDICATION_RDF_ITEM_H
#define SYNDICATION_RDF_ITEM_H

#include <syndication/rdf/document.h>
#include <syndication/rdf/resourcewrapper.h>

#include <syndication/specificitem.h>

class QString;

namespace Syndication {

class SpecificItemVisitor;

namespace RDF {

class DublinCore;
class Item;

/**
 * An RSS 1.0 item.
 * (It is a convenience wrapper for the
 * underlying RDF resource, which can be accessed via resource()).
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT Item : public ResourceWrapper, public SpecificItem
{

    public:

        /**
         * creates an item object wrapping a null resource, isNull() is
         * @c true.
         */
        Item();

        /**
         * Creates an item wrapping the given resource
         * @param resource resource to wrap, should be of type
         * of rss1:item, otherwise the wrapper will not return useful
         * information.
         * @param doc the document this item is part of. Used by Document
         */
        explicit Item(ResourcePtr resource, DocumentPtr doc=DocumentPtr());

        /**
         * copies an item
         *
         * @param other item to copy
         */
        Item(const Item& other);

        /**
         * virtual destructor
         */
        virtual ~Item();

        /**
         * assigns another item
         *
         * @param other the item to assign
         */
        Item& operator=(const Item& other);

        /**
         * compares two item instances. Two instances are equal,
         * if the wrapped resources are equal. See ResourceWrapper::operator==()
         * for details.
         *
         * @param other the item to compare this item to
         */
        bool operator==(const Item& other) const;

        /**
         * interface for item visitors. See SpecificItemVisitor for
         * more information.
         *
         * @param visitor a visitor visiting this object
         */
        bool accept(SpecificItemVisitor* visitor);

        /**
         * The item's title (required).
         *
         * @return The item's title as HTML, or a null string if not specified
         */
        QString title() const;

        /**
         * A brief description/abstract of the item.
         * if encodedContent() is not provided, this can also contain the full
         * content.
         *
         * @return description as HTML, or a null string if not specified
         */
        QString description() const;

        /**
         * The item's URL, usually pointing to a website containing the
         * full content (news article, blog entry etc.).
         *
         * @return the link
         */
        QString link() const;

        /**
         * returns a dublin core description of this
         * item (including metadata such as item author
         * or subject)
         */
        DublinCore dc() const;

        /**
         * returns content (@c content:encoded) as HTML.
         *
         * @return content as HTML, or a null string if not specified
         */
        QString encodedContent() const;

        //@cond PRIVATE
        /**
         * @internal
         * returns the title unmodified
         * used by Document
         */
        QString originalTitle() const;

        /**
         * @internal
         * returns the description unmodified
         * used by Document
         */
        QString originalDescription() const;

        //@endcond

        /**
         * Returns a description of the item for debugging purposes.
         *
         * @return debug string
         */
        QString debugInfo() const;

    private:

        class Private;
        Private* const d;
};

} // namespace RDF
} // namespace Syndication

#endif //  SYNDICATION_RDF_ITEM_H
