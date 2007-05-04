/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2006 Frank Osterfeld <frank.osterfeld@kdemail.net>
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

#include "document.h"
#include "dublincore.h"
#include "image.h"
#include "item.h"
#include "model.h"
#include "resource.h"
#include "rssvocab.h"
#include "sequence.h"
#include "statement.h"
#include "syndicationinfo.h"
#include "textinput.h"

#include <documentvisitor.h>
#include <tools.h>

#include <QtCore/QList>
#include <QtCore/QString>

namespace Syndication {
namespace RDF {

class Document::Private
{
    public:
    Private() : itemTitleContainsMarkup(false),
                itemTitlesGuessed(false),
                itemDescriptionContainsMarkup(false),
                itemDescGuessed(false)
    {}
    mutable bool itemTitleContainsMarkup;
    mutable bool itemTitlesGuessed;
    mutable bool itemDescriptionContainsMarkup;
    mutable bool itemDescGuessed;
};

Document::Document() : Syndication::SpecificDocument(), 
                       ResourceWrapper(),
                       d(new Private)
{
}

Document::Document(ResourcePtr resource) : Syndication::SpecificDocument(),
                                           ResourceWrapper(resource),
                                           d(new Private)
{
}

Document::Document(const Document& other) : SpecificDocument(other),                                                      ResourceWrapper(other),
                                            d(new Private)
{
    *d = *(other.d);
}

Document::~Document()
{
    delete d;
    d = 0;
}


bool Document::operator==(const Document& other) const
{
    return ResourceWrapper::operator==(other);
}


Document& Document::operator=(const Document& other)
{
    ResourceWrapper::operator=(other);
    *d = *(other.d);
    
    return *this;
}

        
bool Document::accept(DocumentVisitor* visitor)
{
    return visitor->visitRDFDocument(this);
}

bool Document::isValid() const
{
    return !isNull();
}
        
QString Document::title() const
{
    QString str = resource()->property(RSSVocab::self()->title())->asString();
    return normalize(str);

}

QString Document::description() const
{
    QString str = resource()->property(RSSVocab::self()->description())->asString();
    return normalize(str);
}

QString Document::link() const
{
    return resource()->property(RSSVocab::self()->link())->asString();
}

DublinCore Document::dc() const
{
    return DublinCore(resource());
}

SyndicationInfo Document::syn() const
{
    return SyndicationInfo(resource());
}

QList<Item> Document::items() const
{
    QList<Item> list;
    if (!resource()->hasProperty(RSSVocab::self()->items()))
        return list;
    
    NodePtr n = resource()->property(RSSVocab::self()->items())->object();
    if (n->isSequence())
    {
        Sequence* seq = static_cast<Sequence*>(n.get());
        
        QList<NodePtr> items = seq->items();
        QList<NodePtr>::Iterator it = items.begin();
        QList<NodePtr>::Iterator end = items.end();
        
        DocumentPtr doccpy(new Document(*this));
        
        for ( ; it != end; ++it)
        {
            if ((*it)->isResource())
            {
                // well, we need it as ResourcePtr
                // maybe this should go to the node
                // interface ResourcePtr asResource()?
                ResourcePtr ptr = resource()->model().createResource((static_cast<Resource*>((*it).get()))->uri());
                
                list.append(Item(ptr, doccpy));
            }
        }
    
    }
    return list;
}

Image Document::image() const
{
    ResourcePtr img = resource()->property(RSSVocab::self()->image())->asResource();
    
    return img ? Image(img) : Image();
}

TextInput Document::textInput() const
{
    ResourcePtr ti = resource()->property(RSSVocab::self()->textinput())->asResource();
    
    return ti ? TextInput(ti) : TextInput();
}

void Document::getItemTitleFormatInfo(bool* containsMarkup) const
{
    if (!d->itemTitlesGuessed)
    {
        QString titles;
        QList<Item> litems = items();
        
        if (litems.isEmpty())
        {
            d->itemTitlesGuessed = true;
            return;
        }
        
        int nmax = litems.size() < 10 ? litems.size() : 10; // we check a maximum of 10 items
        int i = 0;
        
        QList<Item>::ConstIterator it = litems.begin(); 
        
        while (i < nmax)
        {
            titles += (*it).originalTitle();
            ++it;
            ++i;
        }
        
        d->itemTitleContainsMarkup = stringContainsMarkup(titles);
        d->itemTitlesGuessed = true;
    }
    if (containsMarkup != 0L)
        *containsMarkup = d->itemTitleContainsMarkup;
}
        
void Document::getItemDescriptionFormatInfo(bool* containsMarkup) const
{
    if (!d->itemDescGuessed)
    {
        QString desc;
        QList<Item> litems = items();
        
        
        if (litems.isEmpty())
        {
            d->itemDescGuessed = true;
            return;
        }
        
        int nmax = litems.size() < 10 ? litems.size() : 10; // we check a maximum of 10 items
        int i = 0;

        QList<Item>::ConstIterator it = litems.begin(); 

        while (i < nmax)
        {
            desc += (*it).originalDescription();
            ++it;
            ++i;
        }

        d->itemDescriptionContainsMarkup = stringContainsMarkup(desc);
        d->itemDescGuessed = true;
    }
    
    if (containsMarkup != 0L)
        *containsMarkup = d->itemDescriptionContainsMarkup;
}

QString Document::debugInfo() const
{
    QString info;
    info += "### Document: ###################\n";
    info += "title: #" + title() + "#\n";
    info += "link: #" + link() + "#\n";
    info += "description: #" + description() + "#\n";
    info += dc().debugInfo();
    info += syn().debugInfo();
    Image img = image();
    if (!img.resource() == 0L)
        info += img.debugInfo();
    TextInput input = textInput();
    if (!input.isNull())
        info += input.debugInfo();

    QList<Item> itlist = items();
    QList<Item>::ConstIterator it = itlist.begin();
    QList<Item>::ConstIterator end = itlist.end();
    for ( ; it != end; ++it)
        info += (*it).debugInfo();
    
    
    info += "### Document end ################\n";
    return info;
}

} // namespace RDF
} // namespace Syndication
