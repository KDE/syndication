/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_IMAGE_H
#define SYNDICATION_IMAGE_H

#include <QSharedPointer>
#include <QString>

#include "syndication_export.h"

namespace Syndication
{
class Image;
typedef QSharedPointer<Image> ImagePtr;

/*!
 * \class Syndication::Image
 * \inmodule Syndication
 * \inheaderfile Syndication/Image
 *
 * \brief This class represents an image file on the web.
 *
 * It is usually some kind of feed logo which can be displayed when showing the
 * feed description.
 */
class SYNDICATION_EXPORT Image
{
public:
    virtual ~Image();

    /*!
     * returns whether this image is a null object.
     */
    virtual bool isNull() const = 0;

    /*!
     * the URL of a GIF, JPEG or PNG image
     */
    virtual QString url() const = 0;

    /*!
     * Describes the image, can be used in the ALT attribute of the
     * HTML <img> tag when the channel is rendered in HTML.
     */
    virtual QString title() const = 0;

    /*!
     * The URL of the site, when the channel is rendered, the image should
     * be a link to the site. If not set, use Feed::link().
     *
     * Returns the url the rendered image should link to, or a null string
     * if not specified in the feed.
     */
    virtual QString link() const = 0;

    /*!
     * optional text that can be included in the TITLE attribute of the link
     * formed around the image in HTML rendering.
     */
    virtual QString description() const = 0;

    /*!
     * Returns the image width in pixels or 0 if not specified in the feed.
     */
    virtual uint width() const = 0;

    /*!
     * Returns the image height in pixels or 0 of not specified in the feed.
     */
    virtual uint height() const = 0;

    /*!
     * returns a description of the image for debugging purposes
     */
    virtual QString debugInfo() const;
};

} // namespace Syndication

#endif // SYNDICATION_IMAGE_H
