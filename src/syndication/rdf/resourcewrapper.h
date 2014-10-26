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
#ifndef SYNDICATION_RDF_RESOURCEWRAPPER_H
#define SYNDICATION_RDF_RESOURCEWRAPPER_H

#include <QtCore/QSharedPointer>

#include <syndication_export.h>

namespace Syndication
{
namespace RDF
{

class Resource;
typedef QSharedPointer<Resource> ResourcePtr;

/**
 * A wrapper for RDF resources. Base class for convenience wrappers
 * such as Document, Item etc.
 *
 * @author Frank Osterfeld
 */
class SYNDICATION_EXPORT ResourceWrapper
{
public:
    /**
     * creates a wrapper wrapping a null resource, isNull() will be
     * @p true.
     */
    ResourceWrapper();

    /**
     * Copy constructor.
     * Due to the shared d pointer, this is a cheap operation.
     *
     * @param other resource wrapper to copy
     */
    ResourceWrapper(const ResourceWrapper &other);

    /**
     * creates a resource wrapper for a given resource.
     * If a null pointer is passed, a null resource is
     * created internally (resource() will _not_ return a null
     * pointer!)
     * @param resource a resource wrapper instance
     */
    explicit ResourceWrapper(ResourcePtr resource);

    /**
     * destructor
     */
    virtual ~ResourceWrapper();

    /**
     * Assignment oeprator
     * Due to the shared d pointer, this is a cheap operation.
     *
     * @param other resource wrapper to assign.
     */
    ResourceWrapper &operator=(const ResourceWrapper &other);

    /**
     * compares two resource wrapper instances.
     * Two resource wrappers are equal when the wrapped resources
     * are equal, i.e. they have the same URI.
     * @see Resource::uri()
     * @param other resource wrapper instance to compare to
     */
    bool operator==(const ResourceWrapper &other) const;

    /**
     * returns the wrapped resource. Whether a null resource or
     * not, the returned pointer itself is never a null
     * _pointer_!
     */
    ResourcePtr resource() const;

    /**
     * returns whether the wrapped resource is a null resource
     * @return @c true if isNull() is true for the wrapped resource,
     * @c false otherwise
     */
    bool isNull() const;

private:

    class ResourceWrapperPrivate;
    QSharedPointer<ResourceWrapperPrivate> d;
};

} // namespace RDF
} // namespace Syndication

#endif // SYNDICATION_RDF_RESOURCEWRAPPER_H
