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

#include "document.h"
#include "dublincore.h"
#include "image.h"
#include "item.h"
#include "model.h"
#include "model_p.h"
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
#include <QtCore/QStringList>
#include <QtCore/QVector>

#include <algorithm>

using namespace boost;

namespace Syndication
{
namespace RDF
{

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
    shared_ptr<Model::ModelPrivate> modelPrivate;
};

Document::Document() : Syndication::SpecificDocument(),
    ResourceWrapper(),
    d(new Private)
{
    d->modelPrivate = resource()->model().d;
}

Document::Document(ResourcePtr resource) : Syndication::SpecificDocument(),
    ResourceWrapper(resource),
    d(new Private)
{
    d->modelPrivate = resource->model().d;
}

Document::Document(const Document &other) : SpecificDocument(other),                                                      ResourceWrapper(other),
    d(new Private)
{
    *d = *(other.d);
}

Document::~Document()
{
    delete d;
}

bool Document::operator==(const Document &other) const
{
    return ResourceWrapper::operator==(other);
}

Document &Document::operator=(const Document &other)
{
    ResourceWrapper::operator=(other);
    *d = *(other.d);

    return *this;
}

bool Document::accept(DocumentVisitor *visitor)
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

struct SortItem {
    Item item;
    int index;
};

struct LessThanByIndex {
    bool operator()(const SortItem &lhs, const SortItem &rhs) const
    {
        return lhs.index < rhs.index;
    }
};

static QList<Item> sortListToMatchSequence(QList<Item> items, const QStringList &uriSequence)
{
    QVector<SortItem> toSort;
    toSort.reserve(items.size());
    Q_FOREACH (const Item &i, items) {
        SortItem item;
        item.item = i;
        item.index = uriSequence.indexOf(i.resource()->uri());
        toSort.append(item);
    }
    qSort(toSort.begin(), toSort.end(), LessThanByIndex());

    int i = 0;
    Q_FOREACH (const SortItem &sortItem, toSort) {
        items[i] = sortItem.item;
        i++;
    }

    return items;
}

struct UriLessThan {
    bool operator()(const RDF::ResourcePtr &lhs, const RDF::ResourcePtr &rhs) const
    {
        return lhs->uri() < rhs->uri();
    }
};

QList<Item> Document::items() const
{
    QList<ResourcePtr> items = resource()->model().resourcesWithType(RSSVocab::self()->item());
    // if there is no sequence, ensure sorting by URI to have a defined and deterministic order
    // important for unit tests
    std::sort(items.begin(), items.end(), UriLessThan());

    DocumentPtr doccpy(new Document(*this));

    QList<Item> list;

    Q_FOREACH (const ResourcePtr &i, items) {
        list.append(Item(i, doccpy));
    }

    if (resource()->hasProperty(RSSVocab::self()->items())) {
        NodePtr n = resource()->property(RSSVocab::self()->items())->object();
        if (n->isSequence()) {
            Sequence *seq = static_cast<Sequence *>(n.get());

            const QList<NodePtr> seqItems = seq->items();

            QStringList uriSequence;
            uriSequence.reserve(seqItems.size());

            Q_FOREACH (const NodePtr &i, seqItems)
                if (i->isResource()) {
                    uriSequence.append(static_cast<Resource *>(i.get())->uri());
                }
            list = sortListToMatchSequence(list, uriSequence);
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

void Document::getItemTitleFormatInfo(bool *containsMarkup) const
{
    if (!d->itemTitlesGuessed) {
        QString titles;
        QList<Item> litems = items();

        if (litems.isEmpty()) {
            d->itemTitlesGuessed = true;
            return;
        }

        int nmax = litems.size() < 10 ? litems.size() : 10; // we check a maximum of 10 items
        int i = 0;

        QList<Item>::ConstIterator it = litems.constBegin();

        while (i < nmax) {
            titles += (*it).originalTitle();
            ++it;
            ++i;
        }

        d->itemTitleContainsMarkup = stringContainsMarkup(titles);
        d->itemTitlesGuessed = true;
    }
    if (containsMarkup != 0L) {
        *containsMarkup = d->itemTitleContainsMarkup;
    }
}

void Document::getItemDescriptionFormatInfo(bool *containsMarkup) const
{
    if (!d->itemDescGuessed) {
        QString desc;
        QList<Item> litems = items();

        if (litems.isEmpty()) {
            d->itemDescGuessed = true;
            return;
        }

        int nmax = litems.size() < 10 ? litems.size() : 10; // we check a maximum of 10 items
        int i = 0;

        QList<Item>::ConstIterator it = litems.constBegin();

        while (i < nmax) {
            desc += (*it).originalDescription();
            ++it;
            ++i;
        }

        d->itemDescriptionContainsMarkup = stringContainsMarkup(desc);
        d->itemDescGuessed = true;
    }

    if (containsMarkup != 0L) {
        *containsMarkup = d->itemDescriptionContainsMarkup;
    }
}

QString Document::debugInfo() const
{
    QString info;
    info += QLatin1String("### Document: ###################\n");
    info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    info += QLatin1String("link: #") + link() + QLatin1String("#\n");
    info += QLatin1String("description: #") + description() + QLatin1String("#\n");
    info += dc().debugInfo();
    info += syn().debugInfo();
    Image img = image();
    if (!img.resource() == 0L) {
        info += img.debugInfo();
    }
    TextInput input = textInput();
    if (!input.isNull()) {
        info += input.debugInfo();
    }

    QList<Item> itlist = items();
    QList<Item>::ConstIterator it = itlist.constBegin();
    QList<Item>::ConstIterator end = itlist.constEnd();
    for (; it != end; ++it) {
        info += (*it).debugInfo();
    }

    info += QLatin1String("### Document end ################\n");
    return info;
}

} // namespace RDF
} // namespace Syndication
