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

#include "textinput.h"
#include "rssvocab.h"
#include "property.h"
#include "resource.h"
#include "statement.h"

#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

TextInput::TextInput() : ResourceWrapper()
{
}

TextInput::TextInput(ResourcePtr resource) : ResourceWrapper(resource)
{
}

TextInput::~TextInput()
{
}

QString TextInput::title() const
{
    return resource()->property(RSSVocab::self()->title())->asString();
}

QString TextInput::description() const
{
    return resource()->property(RSSVocab::self()->description())->asString();
}

QString TextInput::link() const
{
    return resource()->property(RSSVocab::self()->link())->asString();
}

QString TextInput::name() const
{
    return resource()->property(RSSVocab::self()->name())->asString();
}

QString TextInput::debugInfo() const
{
    QString info;
    info += QLatin1String("### TextInput: ###################\n");
    info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    info += QLatin1String("link: #") + link() + QLatin1String("#\n");
    info += QLatin1String("description: #") + description() + QLatin1String("#\n");
    info += QLatin1String("name: #") + name() + QLatin1String("#\n");
    info += QLatin1String("### TextInput end ################\n");
    return info;
}

} // namespace RDF
} // namespace Syndication
