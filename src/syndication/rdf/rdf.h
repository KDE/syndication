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
#ifndef SYNDICATION_RDF_RDF_H
#define SYNDICATION_RDF_RDF_H

#include <Syndication/rdf/contentvocab.h>
#include <Syndication/rdf/document.h>
#include <Syndication/rdf/dublincore.h>
#include <Syndication/rdf/dublincorevocab.h>
#include <Syndication/rdf/image.h>
#include <Syndication/rdf/item.h>
#include <Syndication/rdf/literal.h>
#include <Syndication/rdf/model.h>
#include <Syndication/rdf/modelmaker.h>
#include <Syndication/rdf/node.h>
#include <Syndication/rdf/nodevisitor.h>
#include <Syndication/rdf/parser.h>
#include <Syndication/rdf/property.h>
#include <Syndication/rdf/rdfvocab.h>
#include <Syndication/rdf/resource.h>
#include <Syndication/rdf/resourcewrapper.h>
#include <Syndication/rdf/rssvocab.h>
#include <Syndication/rdf/sequence.h>
#include <Syndication/rdf/statement.h>
#include <Syndication/syndication.h>
#include <Syndication/rdf/syndicationvocab.h>
#include <Syndication/rdf/textinput.h>

namespace Syndication {

/**
 * Syndication's parser for the RDF-based
 * RSS 0.9 and RSS 1.0 formats
 */
namespace RDF {}

}

#endif // SYNDICATION_RDF_RDF_H
