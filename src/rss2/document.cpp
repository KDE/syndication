/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2005 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <rss2/category.h>
#include <rss2/cloud.h>
#include <rss2/document.h>
#include <rss2/image.h>
#include <rss2/item.h>
#include <rss2/textinput.h>

#include <constants.h>
#include <documentvisitor.h>
#include <tools.h>

#include <QDomDocument>
#include <QList>
#include <QSet>
#include <QString>

#include <vector>

namespace Syndication
{
namespace RSS2
{
class Document::DocumentPrivate
{
public:
    DocumentPrivate()
        : itemDescriptionIsCDATA(false)
        , itemDescriptionContainsMarkup(false)
        , itemDescGuessed(false)
        , itemTitleIsCDATA(false)
        , itemTitleContainsMarkup(false)
        , itemTitlesGuessed(false)
    {
    }
    mutable bool itemDescriptionIsCDATA;
    mutable bool itemDescriptionContainsMarkup;
    mutable bool itemDescGuessed;
    mutable bool itemTitleIsCDATA;
    mutable bool itemTitleContainsMarkup;
    mutable bool itemTitlesGuessed;
};

Document::Document(const QDomElement &element)
    : SpecificDocument()
    , ElementWrapper(element)
    , d(new DocumentPrivate)
{
}

Document Document::fromXML(const QDomDocument &doc)
{
    QDomNode channelNode = doc.namedItem(QStringLiteral("rss")).namedItem(QStringLiteral("channel"));

    return Document(channelNode.toElement());
}

Document::Document()
    : SpecificDocument()
    , ElementWrapper()
    , d(new DocumentPrivate)
{
}

Document::Document(const Document &other)
    : SpecificDocument(other)
    , ElementWrapper(other)
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
    return extractElementTextNS(QString(), QStringLiteral("title"));
}

QString Document::link() const
{
    return extractElementTextNS(QString(), QStringLiteral("link"));
}

QString Document::description() const
{
    const QString desc = extractElementTextNS(QString(), QStringLiteral("description"));
    return normalize(desc);
}

QString Document::language() const
{
    const QString lang = extractElementTextNS(QString(), QStringLiteral("language"));

    if (!lang.isNull()) {
        return lang;
    } else {
        return extractElementTextNS(dublinCoreNamespace(), QStringLiteral("language"));
    }
}

QString Document::copyright() const
{
    const QString rights = extractElementTextNS(QString(), QStringLiteral("copyright"));
    if (!rights.isNull()) {
        return rights;
    } else {
        // if <copyright> is not provided, use <dc:rights>
        return extractElementTextNS(dublinCoreNamespace(), QStringLiteral("rights"));
    }
}

QString Document::managingEditor() const
{
    return extractElementTextNS(QString(), QStringLiteral("managingEditor"));
}

QString Document::webMaster() const
{
    return extractElementTextNS(QString(), QStringLiteral("webMaster"));
}

time_t Document::pubDate() const
{
    QString str = extractElementTextNS(QString(), QStringLiteral("pubDate"));

    if (!str.isNull()) {
        return parseDate(str, RFCDate);
    } else {
        // if there is no pubDate, check for dc:date
        str = extractElementTextNS(dublinCoreNamespace(), QStringLiteral("date"));
        return parseDate(str, ISODate);
    }
}

time_t Document::lastBuildDate() const
{
    const QString str = extractElementTextNS(QString(), QStringLiteral("lastBuildDate"));

    return parseDate(str, RFCDate);
}

QList<Category> Document::categories() const
{
    QList<Category> categories;

    QList<QDomElement> catNodes = elementsByTagNameNS(QString(), QStringLiteral("category"));
    categories.reserve(catNodes.count());
    QList<QDomElement>::ConstIterator it = catNodes.constBegin();
    QList<QDomElement>::ConstIterator end(catNodes.constEnd());
    for (; it != end; ++it) {
        categories.append(Category(*it));
    }

    return categories;
}

QString Document::generator() const
{
    return extractElementTextNS(QString(), QStringLiteral("generator"));
}

QString Document::docs() const
{
    return extractElementTextNS(QString(), QStringLiteral("docs"));
}

Cloud Document::cloud() const
{
    return Cloud(firstElementByTagNameNS(QString(), QStringLiteral("cloud")));
}

int Document::ttl() const
{
    bool ok;
    int c;

    QString text = extractElementTextNS(QString(), QStringLiteral("ttl"));
    c = text.toInt(&ok);
    return ok ? c : 0;
}

Image Document::image() const
{
    return Image(firstElementByTagNameNS(QString(), QStringLiteral("image")));
}

TextInput Document::textInput() const
{
    TextInput ti = TextInput(firstElementByTagNameNS(QString(), QStringLiteral("textInput")));

    if (!ti.isNull()) {
        return ti;
    }

    // Netscape's version of RSS 0.91 has textinput, not textInput
    return TextInput(firstElementByTagNameNS(QString(), QStringLiteral("textinput")));
}

QSet<int> Document::skipHours() const
{
    QSet<int> skipHours;
    QDomElement skipHoursNode = firstElementByTagNameNS(QString(), QStringLiteral("skipHours"));
    if (!skipHoursNode.isNull()) {
        ElementWrapper skipHoursWrapper(skipHoursNode);
        bool ok = false;
        QList<QDomElement> hours = skipHoursWrapper.elementsByTagNameNS(QString(), QStringLiteral("hour"));
        QList<QDomElement>::ConstIterator it = hours.constBegin();
        const QList<QDomElement>::ConstIterator end(hours.constEnd());
        for (; it != end; ++it) {
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
    QDomElement skipDaysNode = firstElementByTagNameNS(QString(), QStringLiteral("skipDays"));
    if (!skipDaysNode.isNull()) {
        ElementWrapper skipDaysWrapper(skipDaysNode);
        QHash<QString, DayOfWeek> weekDays;

        weekDays[QStringLiteral("Monday")] = Monday;
        weekDays[QStringLiteral("Tuesday")] = Tuesday;
        weekDays[QStringLiteral("Wednesday")] = Wednesday;
        weekDays[QStringLiteral("Thursday")] = Thursday;
        weekDays[QStringLiteral("Friday")] = Friday;
        weekDays[QStringLiteral("Saturday")] = Saturday;
        weekDays[QStringLiteral("Sunday")] = Sunday;

        QList<QDomElement> days = skipDaysWrapper.elementsByTagNameNS(QString(), QStringLiteral("day"));
        const QList<QDomElement>::ConstIterator daysEnd(days.constEnd());
        for (QList<QDomElement>::ConstIterator it = days.constBegin(); it != daysEnd; ++it) {
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

    QList<QDomElement> itemNodes = elementsByTagNameNS(QString(), QStringLiteral("item"));

    DocumentPtr doccpy(new Document(*this));
    items.reserve(itemNodes.count());

    const QList<QDomElement>::ConstIterator end(itemNodes.constEnd());
    for (QList<QDomElement>::ConstIterator it = itemNodes.constBegin(); it != end; ++it) {
        items.append(Item(*it, doccpy));
    }

    return items;
}
QList<QDomElement> Document::unhandledElements() const
{
    // TODO: do not hardcode this list here
    static std::vector<ElementType> handled; // QVector would require a default ctor, and ElementType is too big for QList
    if (handled.empty()) {
        handled.reserve(22);
        handled.push_back(ElementType(QStringLiteral("title")));
        handled.push_back(ElementType(QStringLiteral("link")));
        handled.push_back(ElementType(QStringLiteral("description")));
        handled.push_back(ElementType(QStringLiteral("language")));
        handled.push_back(ElementType(QStringLiteral("copyright")));
        handled.push_back(ElementType(QStringLiteral("managingEditor")));
        handled.push_back(ElementType(QStringLiteral("webMaster")));
        handled.push_back(ElementType(QStringLiteral("pubDate")));
        handled.push_back(ElementType(QStringLiteral("lastBuildDate")));
        handled.push_back(ElementType(QStringLiteral("skipDays")));
        handled.push_back(ElementType(QStringLiteral("skipHours")));
        handled.push_back(ElementType(QStringLiteral("item")));
        handled.push_back(ElementType(QStringLiteral("textinput")));
        handled.push_back(ElementType(QStringLiteral("textInput")));
        handled.push_back(ElementType(QStringLiteral("image")));
        handled.push_back(ElementType(QStringLiteral("ttl")));
        handled.push_back(ElementType(QStringLiteral("generator")));
        handled.push_back(ElementType(QStringLiteral("docs")));
        handled.push_back(ElementType(QStringLiteral("cloud")));
        handled.push_back(ElementType(QStringLiteral("language"), dublinCoreNamespace()));
        handled.push_back(ElementType(QStringLiteral("rights"), dublinCoreNamespace()));
        handled.push_back(ElementType(QStringLiteral("date"), dublinCoreNamespace()));
    }

    QList<QDomElement> notHandled;

    QDomNodeList children = element().childNodes();
    const int numChildren = children.size();
    for (int i = 0; i < numChildren; ++i) {
        QDomElement el = children.at(i).toElement();
        if (!el.isNull() //
            && std::find(handled.cbegin(), handled.cend(), ElementType(el.localName(), el.namespaceURI())) == handled.cend()) {
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

    const QList<Category>::ConstIterator end(cats.constEnd());
    for (QList<Category>::ConstIterator it = cats.constBegin(); it != end; ++it) {
        info += (*it).debugInfo();
    }
    QList<Item> litems = items();
    const QList<Item>::ConstIterator itEnd(litems.constEnd());
    for (QList<Item>::ConstIterator it = litems.constBegin(); it != itEnd; ++it) {
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

        QDomElement titleEl = (*litems.begin()).firstElementByTagNameNS(QString(), QStringLiteral("title"));
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

    if (isCDATA != nullptr) {
        *isCDATA = d->itemTitleIsCDATA;
    }
    if (containsMarkup != nullptr) {
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

        QDomElement descEl = (*litems.begin()).firstElementByTagNameNS(QString(), QStringLiteral("description"));
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

    if (isCDATA != nullptr) {
        *isCDATA = d->itemDescriptionIsCDATA;
    }
    if (containsMarkup != nullptr) {
        *containsMarkup = d->itemDescriptionContainsMarkup;
    }
}

bool Document::accept(DocumentVisitor *visitor)
{
    return visitor->visitRSS2Document(this);
}

} // namespace RSS2
} // namespace Syndication
