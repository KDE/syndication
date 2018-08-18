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

#include <syndication/rdf/contentvocab.h>
#include <syndication/rdf/document.h>
#include <syndication/rdf/dublincore.h>
#include <syndication/rdf/dublincorevocab.h>
#include <syndication/rdf/image.h>
#include <syndication/rdf/item.h>
#include <syndication/rdf/literal.h>
#include <syndication/rdf/model.h>
#include <syndication/rdf/modelmaker.h>
#include <syndication/rdf/node.h>
#include <syndication/rdf/nodevisitor.h>
#include <syndication/rdf/parser.h>
#include <syndication/rdf/property.h>
#include <syndication/rdf/rdfvocab.h>
#include <syndication/rdf/resource.h>
#include <syndication/rdf/resourcewrapper.h>
#include <syndication/rdf/rssvocab.h>
#include <syndication/rdf/sequence.h>
#include <syndication/rdf/statement.h>
#include <syndication/syndication.h>
#include <syndication/rdf/syndicationvocab.h>
#include <syndication/rdf/textinput.h>

namespace Syndication
{

/**
 * Syndication's parser for the RDF-based
 * RSS 0.9 and RSS 1.0 formats
 */
namespace RDF {}

}

#endif // SYNDICATION_RDF_RDF_H
