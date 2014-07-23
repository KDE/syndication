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

#ifndef SYNDICATION_MAPPER_IMAGEATOMIMPL_H
#define SYNDICATION_MAPPER_IMAGEATOMIMPL_H

#include <image.h>

#include <QtCore/QMultiMap>
#include <QtCore/QString>

namespace Syndication
{

class ImageAtomImpl;
typedef boost::shared_ptr<ImageAtomImpl> ImageAtomImplPtr;

/**
 *
 * @internal
 * @author Frank Osterfeld
 */
class ImageAtomImpl : public Syndication::Image
{
public:

    explicit ImageAtomImpl(const QString &logoURI) : m_logoURI(logoURI)
    {}

    bool isNull() const
    {
        return m_logoURI.isEmpty();
    }

    QString url() const
    {
        return m_logoURI;
    }

    QString title() const
    {
        return QString();
    }

    QString link() const
    {
        return QString();
    }

    QString description() const
    {
        return QString();
    }

    uint width() const
    {
        return 0;
    }

    uint height() const
    {
        return 0;
    }

private:

    QString m_logoURI;
};

} // namespace Syndication

#endif // SYNDICATION_MAPPER_IMAGEATOMIMPL_H
