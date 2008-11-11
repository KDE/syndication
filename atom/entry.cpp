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
#include "entry.h"
#include "category.h"
#include "constants.h"
#include "content.h"
#include "link.h"
#include "person.h"
#include "source.h"
#include "atomtools.h"

#include <specificitemvisitor.h>
#include <tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QString>

namespace Syndication {
namespace Atom {

Entry::Entry() : ElementWrapper()
{
}

Entry::Entry(const QDomElement& element) : ElementWrapper(element)
{
}

QList<Person> Entry::authors() const
{
    QList<QDomElement> a = 
            elementsByTagNameNS(atom1Namespace(), 
                                QString::fromUtf8("author"));
    QList<Person> list;
                                       
    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();
    
    
    for ( ; it != end; ++it)
    {
        list.append(Person(*it));
    }
        
    return list;
}

QList<Person> Entry::contributors() const
{
    QList<QDomElement> a = 
            elementsByTagNameNS(atom1Namespace(),
                                QString::fromUtf8("contributor"));
    QList<Person> list;
                                       
    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();
    
    
    for ( ; it != end; ++it)
    {
        list.append(Person(*it));
    }
        
    return list;
}

QList<Category> Entry::categories() const
{
    QList<QDomElement> a = 
            elementsByTagNameNS(atom1Namespace(),
                                QString::fromUtf8("category"));
    QList<Category> list;
    
    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();


    for ( ; it != end; ++it)
    {
        list.append(Category(*it));
    }

    return list;
}

QString Entry::id() const
{
    return extractElementTextNS(atom1Namespace(),
                                QString::fromUtf8("id"));

}

QList<Link> Entry::links() const
{
    QList<QDomElement> a = 
            elementsByTagNameNS(atom1Namespace(), 
                                QString::fromUtf8("link"));
    QList<Link> list;
    
    QList<QDomElement>::ConstIterator it = a.constBegin();
    QList<QDomElement>::ConstIterator end = a.constEnd();


    for ( ; it != end; ++it)
    {
        list.append(Link(*it));
    }

    return list;
}

QString Entry::rights() const
{
    return extractAtomText(*this, QString::fromUtf8("rights"));
}

Source Entry::source() const
{
    return Source(firstElementByTagNameNS(atom1Namespace(),
                  QString::fromUtf8("source")));
}

time_t Entry::published() const
{
    QString pub = extractElementTextNS(atom1Namespace(),
                                       QString::fromUtf8("published"));
    return parseDate(pub, ISODate);
}

time_t Entry::updated() const
{
    QString upd = extractElementTextNS(atom1Namespace(),
                                       QString::fromUtf8("updated"));
    return parseDate(upd, ISODate);
}

QString Entry::summary() const
{
    return extractAtomText(*this, QString::fromUtf8("summary"));
}

QString Entry::title() const
{
    return extractAtomText(*this, QString::fromUtf8("title"));
}

Content Entry::content() const
{
    return Content(firstElementByTagNameNS(atom1Namespace(),
                   QString::fromUtf8("content")));
}

QList<QDomElement> Entry::unhandledElements() const
{
    // TODO: do not hardcode this list here
    QList<ElementType> handled;
    handled.append(ElementType(QString::fromUtf8("author"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("contributor"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("category"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("id"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("link"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("rights"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("source"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("published"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("updated"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("summary"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("title"), atom1Namespace()));
    handled.append(ElementType(QString::fromUtf8("content"), atom1Namespace()));
    
    QList<QDomElement> notHandled;
    
    QDomNodeList children = element().childNodes();
    for (int i = 0; i < children.size(); ++i)
    {
        QDomElement el = children.at(i).toElement();
        if (!el.isNull() 
             && !handled.contains(ElementType(el.localName(), el.namespaceURI())))
        {
            notHandled.append(el);
        }
    }
    
    return notHandled;
}

QString Entry::debugInfo() const
{
    QString info;
    info += "### Entry: ###################\n";
    if (!title().isEmpty())
        info += "title: #" + title() + "#\n";
    if (!summary().isEmpty())
        info += "summary: #" + summary() + "#\n";
    if (!id().isEmpty())
        info += "id: #" + id() + "#\n";
    if (!content().isNull())
        info += content().debugInfo();
    
    if (!rights().isEmpty())
        info += "rights: #" + rights() + "#\n";
    
    
    QString dupdated = dateTimeToString(updated());
    if (!dupdated.isNull())
        info += "updated: #" + dupdated + "#\n";
    
    QString dpublished = dateTimeToString(published());
    if (!dpublished.isNull())
        info += "published: #" + dpublished + "#\n";
    
    QList<Link> dlinks = links();
    QList<Link>::ConstIterator endlinks = dlinks.constEnd();
    for (QList<Link>::ConstIterator it = dlinks.constBegin(); it != endlinks; ++it)
        info += (*it).debugInfo();
    
    QList<Category> dcats = categories();
    QList<Category>::ConstIterator endcats = dcats.constEnd();
    for (QList<Category>::ConstIterator it = dcats.constBegin(); it != endcats; ++it)
        info += (*it).debugInfo();

    info += "### Authors: ###################\n";
    
    QList<Person> dauthors = authors();
    QList<Person>::ConstIterator endauthors = dauthors.constEnd();
    for (QList<Person>::ConstIterator it = dauthors.constBegin(); it != endauthors; ++it)
        info += (*it).debugInfo();

    info += "### Contributors: ###################\n";
    
    QList<Person> dcontri = contributors();
    QList<Person>::ConstIterator endcontri = dcontri.constEnd();
    for (QList<Person>::ConstIterator it = dcontri.constBegin(); it != endcontri; ++it)
        info += (*it).debugInfo();
    
    if (!source().isNull())
        info += source().debugInfo();
    
    info += "### Entry end ################\n";

    return info;
}

bool Entry::accept(SpecificItemVisitor* visitor)
{
    return visitor->visitAtomEntry(this);
}

} // namespace Atom
} //namespace Syndication

