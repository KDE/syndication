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

#include <rss2/document.h>
#include <rss2/category.h>
#include <rss2/cloud.h>
#include <rss2/image.h>
#include <rss2/item.h>
#include <rss2/textinput.h>

#include <constants.h>
#include <documentvisitor.h>
#include <tools.h>

#include <QtXml/QDomDocument>
#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QString>

namespace Syndication
{
namespace RSS2
{

class Document::DocumentPrivate
{
public:
    DocumentPrivate() : itemDescriptionIsCDATA(false),
        itemDescriptionContainsMarkup(false),
        itemDescGuessed(false),
        itemTitleIsCDATA(false),
        itemTitleContainsMarkup(false),
        itemTitlesGuessed(false)
    {}
    mutable bool itemDescriptionIsCDATA;
    mutable bool itemDescriptionContainsMarkup;
    mutable bool itemDescGuessed;
    mutable bool itemTitleIsCDATA;
    mutable bool itemTitleContainsMarkup;
    mutable bool itemTitlesGuessed;
};

Document::Document(const QDomElement &element) : SpecificDocument(),
    ElementWrapper(element),
    d(new DocumentPrivate)
{
}

Document Document::fromXML(const QDomDocument &doc)
{
    QDomNode channelNode = doc.namedItem(QLatin1String("rss")).namedItem(QLatin1String("channel"));

    return Document(channelNode.toElement());
}

Document::Document() : SpecificDocument(), ElementWrapper(), d(new DocumentPrivate)
{
}

Document::Document(const Document &other) : SpecificDocument(other), ElementWrapper(other)
{
    d = other.d;
}

Document::~Document()
{
}

Document &Document::operator=(const Document &other)
{
    ElementWrapper::operator=(other);
    d = other.d;
    return *this;
}
bool Document::isValid() const
{
    return !isNull();
}

QString Document::title() const
{
    return extractElementTextNS(QString(), QLatin1String("title"));
}

QString Document::link() const
{
    return extractElementTextNS(QString(), QLatin1String("link"));
}

QString Document::description() const
{
    QString desc = extractElementTextNS(QString(), QLatin1String("description"));
    return normalize(desc);
}

QString Document::language() const
{
    QString lang = extractElementTextNS(QString(),
                                        QLatin1String("language"));

    if (!lang.isNull()) {
        return lang;
    } else {
        return extractElementTextNS(
                   dublinCoreNamespace(), QLatin1String("language"));
    }

}

QString Document::copyright() const
{
    QString rights = extractElementTextNS(QString(),
                                          QLatin1String("copyright"));
    if (!rights.isNull()) {
        return rights;
    } else {
        // if <copyright> is not provided, use <dc:rights>
        return extractElementTextNS(dublinCoreNamespace(),
                                    QLatin1String("rights"));
    }
}

QString Document::managingEditor() const
{
    return extractElementTextNS(QString(), QLatin1String("managingEditor"));
}

QString Document::webMaster() const
{
    return extractElementTextNS(QString(), QLatin1String("webMaster"));
}

time_t Document::pubDate() const
{
    QString str = extractElementTextNS(QString(), QLatin1String("pubDate"));

    if (!str.isNull()) {
        return parseDate(str, RFCDate);
    } else {
        // if there is no pubDate, check for dc:date
        str = extractElementTextNS(dublinCoreNamespace(), QLatin1String("date"));
        return parseDate(str, ISODate);
    }
}

time_t Document::lastBuildDate() const
{
    QString str = extractElementTextNS(QString(), QLatin1String("lastBuildDate"));

    return parseDate(str, RFCDate);
}

QList<Category> Document::categories() const
{
    QList<Category> categories;

    QList<QDomElement> catNodes = elementsByTagNameNS(QString(),
                                  QLatin1String("category"));
    QList<QDomElement>::ConstIterator it = catNodes.constBegin();
    for (; it != catNodes.constEnd(); ++it) {
        categories.append(Category(*it));
    }

    return categories;
}

QString Document::generator() const
{
    return extractElementTextNS(QString(), QLatin1String("generator"));
}

QString Document::docs() const
{
    return extractElementTextNS(QString(), QLatin1String("docs"));
}

Cloud Document::cloud() const
{
    return Cloud(firstElementByTagNameNS(QString(), QLatin1String("cloud")));
}

int Document::ttl() const
{
    bool ok;
    int c;

    QString text = extractElementTextNS(QString(), QLatin1String("ttl"));
    c = text.toInt(&ok);
    return ok ? c : 0;
}

Image Document::image() const
{
    return Image(firstElementByTagNameNS(QString(), QLatin1String("image")));
}

TextInput Document::textInput() const
{
    TextInput ti = TextInput(firstElementByTagNameNS(QString(), QLatin1String("textInput")));

    if (!ti.isNull()) {
        return ti;
    }

    // Netscape's version of RSS 0.91 has textinput, not textInput
    return TextInput(firstElementByTagNameNS(QString(), QLatin1String("textinput")));
}

QSet<int> Document::skipHours() const
{
    QSet<int> skipHours;
    QDomElement skipHoursNode = firstElementByTagNameNS(QString(),
                                QLatin1String("skipHours"));
    if (!skipHoursNode.isNull()) {
        ElementWrapper skipHoursWrapper(skipHoursNode);
        bool ok = false;
        QList<QDomElement> hours =
            skipHoursWrapper.elementsByTagNameNS(QString(),
                    QLatin1String("hour"));
        QList<QDomElement>::ConstIterator it = hours.constBegin();
        for (; it != hours.constEnd(); ++it) {
            int h = (*it).text().toInt(&ok);
            if (ok) {
                skipHours.insert(h);
            }
        }
    }

    return skipHours;
}

QSet<Document::DayOfWeek> Document::skipDays() const
{
    QSet<DayOfWeek> skipDays;
    QDomElement skipDaysNode = firstElementByTagNameNS(QString(), QLatin1String("skipDays"));
    if (!skipDaysNode.isNull()) {
        ElementWrapper skipDaysWrapper(skipDaysNode);
        QHash<QString, DayOfWeek> weekDays;

        weekDays[QLatin1String("Monday")] = Monday;
        weekDays[QLatin1String("Tuesday")] = Tuesday;
        weekDays[QLatin1String("Wednesday")] = Wednesday;
        weekDays[QLatin1String("Thursday")] = Thursday;
        weekDays[QLatin1String("Friday")] = Friday;
        weekDays[QLatin1String("Saturday")] = Saturday;
        weekDays[QLatin1String("Sunday")] = Sunday;

        QList<QDomElement> days = skipDaysWrapper.elementsByTagNameNS(QString(), QLatin1String("day"));
        for (QList<QDomElement>::ConstIterator it = days.constBegin(); it != days.constEnd(); ++it) {
            if (weekDays.contains((*it).text())) {
                skipDays.insert(weekDays[(*it).text()]);
            }
        }
    }

    return skipDays;
}

QList<Item> Document::items() const
{
    QList<Item> items;

    QList<QDomElement> itemNodes = elementsByTagNameNS(QString(), QLatin1String("item"));

    DocumentPtr doccpy(new Document(*this));

    for (QList<QDomElement>::ConstIterator it = itemNodes.constBegin(); it != itemNodes.constEnd(); ++it) {
        items.append(Item(*it, doccpy));
    }

    return items;
}
QList<QDomElement> Document::unhandledElements() const
{
    // TODO: do not hardcode this list here
    QList<ElementType> handled;
    handled.append(ElementType(QLatin1String("title")));
    handled.append(ElementType(QLatin1String("link")));
    handled.append(ElementType(QLatin1String("description")));
    handled.append(ElementType(QLatin1String("language")));
    handled.append(ElementType(QLatin1String("copyright")));
    handled.append(ElementType(QLatin1String("managingEditor")));
    handled.append(ElementType(QLatin1String("webMaster")));
    handled.append(ElementType(QLatin1String("pubDate")));
    handled.append(ElementType(QLatin1String("lastBuildDate")));
    handled.append(ElementType(QLatin1String("skipDays")));
    handled.append(ElementType(QLatin1String("skipHours")));
    handled.append(ElementType(QLatin1String("item")));
    handled.append(ElementType(QLatin1String("textinput")));
    handled.append(ElementType(QLatin1String("textInput")));
    handled.append(ElementType(QLatin1String("image")));
    handled.append(ElementType(QLatin1String("ttl")));
    handled.append(ElementType(QLatin1String("generator")));
    handled.append(ElementType(QLatin1String("docs")));
    handled.append(ElementType(QLatin1String("cloud")));
    handled.append(ElementType(QLatin1String("language"), dublinCoreNamespace()));
    handled.append(ElementType(QLatin1String("rights"), dublinCoreNamespace()));
    handled.append(ElementType(QLatin1String("date"), dublinCoreNamespace()));

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

QString Document::debugInfo() const
{
    QString info;
    info += QLatin1String("### Document: ###################\n");
    if (!title().isNull()) {
        info += QLatin1String("title: #") + title() + QLatin1String("#\n");
    }
    if (!description().isNull()) {
        info += QLatin1String("description: #") + description() + QLatin1String("#\n");
    }
    if (!link().isNull()) {
        info += QLatin1String("link: #") + link() + QLatin1String("#\n");
    }
    if (!language().isNull()) {
        info += QLatin1String("language: #") + language() + QLatin1String("#\n");
    }
    if (!copyright().isNull()) {
        info += QLatin1String("copyright: #") + copyright() + QLatin1String("#\n");
    }
    if (!managingEditor().isNull()) {
        info += QLatin1String("managingEditor: #") + managingEditor() + QLatin1String("#\n");
    }
    if (!webMaster().isNull()) {
        info += QLatin1String("webMaster: #") + webMaster() + QLatin1String("#\n");
    }

    QString dpubdate = dateTimeToString(pubDate());
    if (!dpubdate.isNull()) {
        info += QLatin1String("pubDate: #") + dpubdate + QLatin1String("#\n");
    }

    QString dlastbuilddate = dateTimeToString(lastBuildDate());
    if (!dlastbuilddate.isNull()) {
        info += QLatin1String("lastBuildDate: #") + dlastbuilddate + QLatin1String("#\n");
    }

    if (!textInput().isNull()) {
        info += textInput().debugInfo();
    }
    if (!cloud().isNull()) {
        info += cloud().debugInfo();
    }
    if (!image().isNull()) {
        info += image().debugInfo();
    }

    QList<Category> cats = categories();

    for (QList<Category>::ConstIterator it = cats.constBegin(); it != cats.constEnd(); ++it) {
        info += (*it).debugInfo();
    }
    QList<Item> litems = items();
    for (QList<Item>::ConstIterator it = litems.constBegin(); it != litems.constEnd(); ++it) {
        info += (*it).debugInfo();
    }
    info += QLatin1String("### Document end ################\n");
    return info;
}

void Document::getItemTitleFormatInfo(bool *isCDATA, bool *containsMarkup) const
{
    if (!d->itemTitlesGuessed) {
        QString titles;
        QList<Item> litems = items();

        if (litems.isEmpty()) {
            d->itemTitlesGuessed = true;
            return;
        }

        QDomElement titleEl = (*litems.begin()).firstElementByTagNameNS(QString(), QLatin1String("title"));
        d->itemTitleIsCDATA = titleEl.firstChild().isCDATASection();

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

    if (isCDATA != 0L) {
        *isCDATA = d->itemTitleIsCDATA;
    }
    if (containsMarkup != 0L) {
        *containsMarkup = d->itemTitleContainsMarkup;
    }
}

void Document::getItemDescriptionFormatInfo(bool *isCDATA, bool *containsMarkup) const
{
    if (!d->itemDescGuessed) {
        QString desc;
        QList<Item> litems = items();

        if (litems.isEmpty()) {
            d->itemDescGuessed = true;
            return;
        }

        QDomElement descEl = (*litems.begin()).firstElementByTagNameNS(QString(), QLatin1String("description"));
        d->itemDescriptionIsCDATA = descEl.firstChild().isCDATASection();

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

    if (isCDATA != 0L) {
        *isCDATA = d->itemDescriptionIsCDATA;
    }
    if (containsMarkup != 0L) {
        *containsMarkup = d->itemDescriptionContainsMarkup;
    }
}

bool Document::accept(DocumentVisitor *visitor)
{
    return visitor->visitRSS2Document(this);
}

} // namespace RSS2
} // namespace Syndication
