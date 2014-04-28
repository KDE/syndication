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
#ifndef SYNDICATION_ATOM_ATOM_H
#define SYNDICATION_ATOM_ATOM_H

#include <Syndication/atom/category.h>
#include <Syndication/atom/constants.h>
#include <Syndication/atom/content.h>
#include <Syndication/atom/document.h>
#include <Syndication/atom/entry.h>
#include <Syndication/atom/generator.h>
#include <Syndication/atom/link.h>
#include <Syndication/atom/parser.h>
#include <Syndication/atom/person.h>
#include <Syndication/atom/source.h>

namespace Syndication {

/**
 * Atom parser and model classes, representing
 * Atom 1.0 documents (Atom 0.3 documents are
 * converted by the parser)
 */
namespace Atom {}

}

#endif // SYNDICATION_ATOM_ATOM_H
