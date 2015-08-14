/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2005 Frank Osterfeld <osterfeld@kde.org>
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

#include <rss2/item.h>
#include <rss2/category.h>
#include <rss2/enclosure.h>
#include <rss2/source.h>
#include <rss2/tools_p.h>
#include <constants.h>
#include <specificitem.h>
#include <specificitemvisitor.h>
#include <tools.h>

#include <QtXml/QDomElement>
#include <QtCore/QString>
#include <QtCore/QList>

namespace Syndication
{
namespace RSS2
{

class Item::ItemPrivate
{
public:

    QSharedPointer<Document> doc;
};

Item::Item(QSharedPointer<Document> doc) : ElementWrapper(), d(new ItemPrivate)
{
    d->doc = doc;
}

Item::Item(const QDomElement &element, QSharedPointer<Document> doc) : ElementWrapper(element), d(new ItemPrivate)
{
    d->doc = doc;
}

Item::~Item()
{
}

Item::Item(const Item &other) : ElementWrapper(other), SpecificItem(other)
{
    d = other.d;
}

Item &Item::operator=(const Item &other)
{
    ElementWrapper::operator=(other);
    SpecificItem::operator=(other);
    d = other.d;
    return *this;
}

QString Item::title() const
{
    if (!d->doc) {
        return originalTitle();
    }

    bool isCDATA = false;
    bool containsMarkup = false;
    d->doc->getItemTitleFormatInfo(&isCDATA, &containsMarkup);

    return normalize(originalTitle(), isCDATA, containsMarkup);
}

QString Item::originalDescription() const
{
    return extractElementTextNS(QString(), QStringLiteral("description"));
}

QString Item::originalTitle() const
{
    return extractElementTextNS(QString(), QStringLiteral("title"));
}

QString Item::link() const
{
    QString url = extractElementTextNS(QString(), QStringLiteral("link"));
    if (url.startsWith(QLatin1String("http://")) || url.startsWith(QLatin1String("https://"))) {
        return url;
    }
    if (url.isEmpty()) {
        return QString();
    }
    if (d->doc->link().isEmpty()) {
        return url;
    }
    // link does not look like a complete url, assume the feed author expects
    // the doc link to provide the base of the url.
    QString baseUrl = d->doc->link();
    if (url.startsWith(QLatin1Char('/')) || baseUrl.endsWith(QLatin1Char('/'))) {
        return baseUrl + url;
    } else {
        return baseUrl + QLatin1Char('/') + url;
    }
}

QString Item::description() const
{
    if (!d->doc) {
        return originalDescription();
    }

    bool isCDATA = false;
    bool containsMarkup = false;
    d->doc->getItemDescriptionFormatInfo(&isCDATA, &containsMarkup);

    return normalize(originalDescription(), isCDATA, containsMarkup);
}

QString Item::content() const
{
    // parse encoded stuff from content:encoded, xhtml:body and friends into content
    return extractContent(*this);
}

QList<Category> Item::categories() const
{
    QList<QDomElement> cats = elementsByTagNameNS(QString(),
                              QStringLiteral("category"));

    QList<Category> categories;
    categories.reserve(cats.count());

    QList<QDomElement>::ConstIterator it = cats.constBegin();
    for (; it != cats.constEnd(); ++it) {
        categories.append(Category(*it));
    }
    return categories;
}

QString Item::comments() const
{
    return extractElementTextNS(QString(), QStringLiteral("comments"));
}

QString Item::author() const
{
    QString a = extractElementTextNS(QString(), QStringLiteral("author"));
    if (!a.isNull()) {
        return a;
    } else {
        // if author is not available, fall back to dc:creator
        return extractElementTextNS(dublinCoreNamespace(),
                                    QStringLiteral("creator"));
    }

}

QList<Enclosure> Item::enclosures() const
{
    QList<QDomElement> encs = elementsByTagNameNS(QString(),
                              QStringLiteral("enclosure"));

    QList<Enclosure> enclosures;
    enclosures.reserve(encs.count());

    QList<QDomElement>::ConstIterator it = encs.constBegin();
    for (; it != encs.constEnd(); ++it) {
        enclosures.append(Enclosure(*it));
    }
    return enclosures;
}

QString Item::guid() const
{
    return extractElementTextNS(QString(), QStringLiteral("guid"));
}

bool Item::guidIsPermaLink() const
{
    bool guidIsPermaLink = true;  // true is default

    QDomElement guidNode = firstElementByTagNameNS(QString(),
                           QStringLiteral("guid"));
    if (!guidNode.isNull()) {
        if (guidNode.attribute(QStringLiteral("isPermaLink"))
                == QLatin1String("false")) {
            guidIsPermaLink = false;
        }
    }

    return guidIsPermaLink;
}

time_t Item::pubDate() const
{
    QString str = extractElementTextNS(QString(), QStringLiteral("pubDate"));

    if (!str.isNull()) {
        return parseDate(str, RFCDate);
    }

    // if there is no pubDate, check for dc:date
    str = extractElementTextNS(dublinCoreNamespace(), QStringLiteral("date"));
    return parseDate(str, ISODate);
}

time_t Item::expirationDate() const
{
    QString str = extractElementTextNS(QString(), QStringLiteral("expirationDate"));
    return parseDate(str, RFCDate);
}

Source Item::source() const
{
    return Source(firstElementByTagNameNS(QString(), QStringLiteral("source")));
}

QString Item::rating() const
{
    return extractElementTextNS(QString(), QStringLiteral("rating"));
}

QString Item::debugInfo() const
{
    QString info;
    info += QLatin1String("### Item: ###################\n");
    if (!title().isNull()) {
        info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    }
    if (!link().isNull()) {
        info += QLatin1String("link: #") + link() + QLatin1String("#\n");
    }
    if (!description().isNull()) {
        info += QLatin1String("description: #") + description() + QLatin1String("#\n");
    }
    if (!content().isNull()) {
        info += QLatin1String("content: #") + content() + QLatin1String("#\n");
    }
    if (!author().isNull()) {
        info += QLatin1String("author: #") + author() + QLatin1String("#\n");
    }
    if (!comments().isNull()) {
        info += QLatin1String("comments: #") + comments() + QLatin1String("#\n");
    }
    QString dpubdate = dateTimeToString(pubDate());
    if (!dpubdate.isNull()) {
        info += QLatin1String("pubDate: #") + dpubdate + QLatin1String("#\n");
    }
    if (!guid().isNull()) {
        info += QLatin1String("guid: #") + guid() + QLatin1String("#\n");
    }
    if (guidIsPermaLink()) {
        info += QLatin1String("guid is PL: #true#\n");
    }
    if (!source().isNull()) {
        info += source().debugInfo();
    }

    QList<Category> cats = categories();
    for (QList<Category>::ConstIterator it = cats.constBegin(); it != cats.constEnd(); ++it) {
        info += (*it).debugInfo();
    }
    QList<Enclosure> encs = enclosures();
    for (QList<Enclosure>::ConstIterator it = encs.constBegin(); it != encs.constEnd(); ++it) {
        info += (*it).debugInfo();
    }

    info += QLatin1String("### Item end ################\n");
    return info;
}

QList<QDomElement> Item::unhandledElements() const
{
    // TODO: do not hardcode this list here
    static QList<ElementType> handled;
    if (handled.isEmpty()) {
        handled.reserve(11);
        handled.append(ElementType(QStringLiteral("title")));
        handled.append(ElementType(QStringLiteral("link")));
        handled.append(ElementType(QStringLiteral("description")));
        handled.append(ElementType(QStringLiteral("pubDate")));
        handled.append(ElementType(QStringLiteral("expirationDate")));
        handled.append(ElementType(QStringLiteral("rating")));
        handled.append(ElementType(QStringLiteral("source")));
        handled.append(ElementType(QStringLiteral("guid")));
        handled.append(ElementType(QStringLiteral("comments")));
        handled.append(ElementType(QStringLiteral("author")));
        handled.append(ElementType(QStringLiteral("date"), dublinCoreNamespace()));
    }

    QList<QDomElement> notHandled;

    QDomNodeList children = element().childNodes();
    for (int i = 0; i < children.size(); ++i) {
        QDomElement el = children.at(i).toElement();
        if (!el.isNull()
                && !handled.contains(ElementType(el.localName(), el.namespaceURI()))) {
            notHandled.append(el);
        }
    }

    return notHandled;
}

bool Item::accept(SpecificItemVisitor *visitor)
{
    return visitor->visitRSS2Item(this);
}

} // namespace RSS2
} // namespace Syndication
