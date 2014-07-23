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

#ifndef SYNDICATION_RDF_IMAGE_H
#define SYNDICATION_RDF_IMAGE_H

#include <QtCore/QString>
#include <syndication/rdf/resourcewrapper.h>

namespace Syndication
{
namespace RDF
{

class Resource;
//@cond PRIVATE
typedef boost::shared_ptr<Resource> ResourcePtr;
//@endcond

/**
 * An image to be associated with an HTML rendering of the channel.
 */
class SYNDICATION_EXPORT Image : public ResourceWrapper
{

public:

    /**
     * creates a wrapper wrapping a null resource
     */
    Image();

    /**
     * creates an image object by wrapping an image resource
     *
     * @param resource the image resource to wrap
     */
    explicit Image(ResourcePtr resource);

    /**
     * destructor
     */
    virtual ~Image();

    /**
     * Describes the image, can be used in the ALT attribute of the
     * HTML @c &lt;img> tag when the channel is rendered in HTML.
     *
     * @return TODO: specify format
     */
    QString title() const;

    /**
     * The URL of the site, when the channel is rendered, the image should
     * be a link to the site.
     */
    QString link() const;

    /**
      * the URL of the image file
      */
    QString url() const;

    /**
    * Returns a description of the image for debugging purposes.
    *
    * @return debug string
    */
    QString debugInfo() const;
};

} // namespace RDF
} // namespace Syndication

#endif //  SYNDICATION_RDF_IMAGE_H
