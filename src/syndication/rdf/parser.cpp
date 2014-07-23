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

#include "parser.h"
#include "document.h"
#include "model.h"
#include "modelmaker.h"
#include "property.h"
#include "rdfvocab.h"
#include "resource.h"
#include "rssvocab.h"
#include "statement.h"

#include <documentsource.h>

#include <QtXml/QDomDocument>
#include <QtXml/QDomNodeList>
#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace Syndication
{
namespace RDF
{

class Parser::ParserPrivate
{
public:
    QDomDocument addEnumeration(const QDomDocument &doc);
    void map09to10(Model model);
    void addSequenceFor09(Model model);

    QString strInternalNs;
    QString strItemIndex;
};

bool Parser::accept(const DocumentSource &source) const
{
    QDomDocument doc = source.asDomDocument();

    if (doc.isNull()) {
        return false;
    }
    QDomElement root = doc.documentElement();

    if (!root.isElement()) {
        return false;
    }

    return root.namespaceURI() == RDFVocab::self()->namespaceURI();
}

SpecificDocumentPtr Parser::parse(const DocumentSource &source) const
{
    QDomDocument doc = source.asDomDocument();

    if (doc.isNull()) {
        return Syndication::SpecificDocumentPtr(new Document());
    }

    doc = d->addEnumeration(doc);

    ModelMaker maker;
    Model model = maker.createFromXML(doc);

    bool is09 = !model.resourcesWithType(RSS09Vocab::self()->channel()).isEmpty();

    if (is09) {
        d->map09to10(model);
        d->addSequenceFor09(model);
    }

    QList<ResourcePtr> channels = model.resourcesWithType(RSSVocab::self()->channel());

    if (channels.isEmpty()) {
        return Syndication::SpecificDocumentPtr(new Document());
    }

    return DocumentPtr(new Document(*(channels.begin())));
}

QDomDocument Parser::ParserPrivate::addEnumeration(const QDomDocument &docp)
{
    QDomDocument doc(docp);

    QDomNodeList list = doc.elementsByTagNameNS(RSS09Vocab::self()->namespaceURI(),
                        QLatin1String("item"));

    for (int i = 0; i < list.size(); ++i) {
        QDomElement item = list.item(i).toElement();
        if (!item.isNull()) {
            QDomElement ie = doc.createElementNS(strInternalNs, strItemIndex);
            item.appendChild(ie);
            ie.appendChild(doc.createTextNode(QString::number(i)));

        }
    }

    return doc;
}

void Parser::ParserPrivate::map09to10(Model model)
{
    QHash<QString, PropertyPtr> hash;

    hash.insert(RSS09Vocab::self()->title()->uri(), RSSVocab::self()->title());
    hash.insert(RSS09Vocab::self()->description()->uri(), RSSVocab::self()->description());
    hash.insert(RSS09Vocab::self()->link()->uri(), RSSVocab::self()->link());
    hash.insert(RSS09Vocab::self()->name()->uri(), RSSVocab::self()->name());
    hash.insert(RSS09Vocab::self()->url()->uri(), RSSVocab::self()->url());
    hash.insert(RSS09Vocab::self()->image()->uri(), RSSVocab::self()->image());
    hash.insert(RSS09Vocab::self()->textinput()->uri(), RSSVocab::self()->textinput());

    QStringList uris09 = RSS09Vocab::self()->properties();

    // map statement predicates to RSS 1.0

    QList<StatementPtr> statements = model.statements();
    QList<StatementPtr>::ConstIterator it = statements.constBegin();
    QList<StatementPtr>::ConstIterator end = statements.constEnd();

    for (; it != end; ++it) {
        StatementPtr stmt = *it;

        QString predUri = stmt->predicate()->uri();
        if (uris09.contains(predUri)) {
            model.addStatement(stmt->subject(), hash[predUri], stmt->object());
        }
    }
    // map channel type
    QList<ResourcePtr> channels = model.resourcesWithType(RSS09Vocab::self()->channel());

    ResourcePtr channel;

    if (!channels.isEmpty()) {
        channel = *(channels.begin());

        model.removeStatement(channel, RDFVocab::self()->type(), RSS09Vocab::self()->channel());
        model.addStatement(channel, RDFVocab::self()->type(), RSSVocab::self()->channel());
    }
}

void Parser::ParserPrivate::addSequenceFor09(Model model)
{
    //RDF 0.9 doesn't contain an item sequence, and the items don't have rdf:about, so add both

    const QList<ResourcePtr> items = model.resourcesWithType(RSS09Vocab::self()->item());

    if (items.isEmpty()) {
        return;
    }

    const QList<ResourcePtr> channels = model.resourcesWithType(RSSVocab::self()->channel());

    if (channels.isEmpty()) {
        return;
    }

    PropertyPtr itemIndex = model.createProperty(strInternalNs + strItemIndex);

    // use QMap here, not QHash. as we need the sorting functionality
    QMap<uint, ResourcePtr> sorted;

    foreach (const ResourcePtr &i, items) {
        QString numstr = i->property(itemIndex)->asString();
        bool ok = false;
        uint num = numstr.toUInt(&ok);
        if (ok) {
            sorted[num] = i;
        }
    }

    SequencePtr seq = model.createSequence();
    model.addStatement(channels.first(), RSSVocab::self()->items(), seq);

    foreach (const ResourcePtr &i, sorted) {
        seq->append(i);
        // add rdf:about (type)
        model.addStatement(i, RDFVocab::self()->type(), RSSVocab::self()->item());

        //add to items sequence
        model.addStatement(seq, RDFVocab::self()->li(), i);
    }
}

Parser::Parser() : d(new ParserPrivate)
{
    d->strInternalNs = QLatin1String("http://akregator.sf.net/libsyndication/internal#");
    d->strItemIndex = QLatin1String("itemIndex");
}

Parser::~Parser()
{
    delete d;
}

Parser::Parser(const Parser &other) : AbstractParser(other), d(0) {}
Parser &Parser::operator=(const Parser & /*other*/)
{
    return *this;
}

QString Parser::format() const
{
    return QLatin1String("rdf");
}

} // namespace RDF
} // namespace Syndication
