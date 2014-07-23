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

#include "property.h"
#include "nodevisitor.h"

namespace Syndication
{
namespace RDF
{

Property::Property() : Resource()
{
}

Property::Property(const QString &uri) : Resource(uri)
{
}

Property::~Property()
{
}

bool Property::isProperty() const
{
    return true;
}

void Property::accept(NodeVisitor *visitor, NodePtr ptr)
{
    PropertyPtr pptr = boost::static_pointer_cast<Syndication::RDF::Property>(ptr);

    if (!visitor->visitProperty(pptr)) {
        Resource::accept(visitor, ptr);
    }
}

Property *Property::clone() const
{
    return new Property(*this);
}

} // namespace RDF
} // namespace Syndication
