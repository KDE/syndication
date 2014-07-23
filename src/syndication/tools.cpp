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

#include "tools.h"
#include "personimpl.h"

#include <kcharsets.h>
#include <kcodecs.h>

#include <QtCore/QByteArray>
#include <QtCore/QCryptographicHash>
#include <QtCore/QDateTime>
#include <QtCore/QRegExp>
#include <QtCore/QString>

namespace Syndication
{

QCryptographicHash md5Machine(QCryptographicHash::Md5);

unsigned int calcHash(const QString &str)
{
    return calcHash(str.toUtf8());
}

unsigned int calcHash(const QByteArray &array)
{
    if (array.isEmpty()) {
        return 0;
    } else {
        const char *s = array.data();
        unsigned int hash = 5381;
        int c;
        while ((c = *s++)) {
            hash = ((hash << 5) + hash) + c;    // hash*33 + c
        }
        return hash;
    }
}

static uint toTimeT(QDateTime &kdt)
{
    if (kdt.isValid()) {
        //work around unspecified timezones/date-only timestamps by setting the time to 12:00 UTC
        if (kdt.time().isNull() || (kdt.time() == QTime(0, 0) && kdt.timeSpec() == Qt::LocalTime)) {
            kdt.setTimeSpec(Qt::UTC);
            kdt.setTime(QTime(12, 0));
        }
        return kdt.toTime_t();
    } else {
        return 0;
    }
}

uint parseISODate(const QString &str)
{
    QDateTime kdt = QDateTime::fromString(str, Qt::ISODate);
    return toTimeT(kdt);
}

uint parseRFCDate(const QString &str)
{
    QDateTime kdt = QDateTime::fromString(str, Qt::RFC2822Date);
    return toTimeT(kdt);
}

uint parseDate(const QString &str, DateFormat hint)
{
    if (str.isEmpty()) {
        return 0;
    }

    if (hint == RFCDate) {
        time_t t = parseRFCDate(str);
        return t != 0 ? t : parseISODate(str);
    } else {
        time_t t = parseISODate(str);
        return t != 0 ? t : parseRFCDate(str);
    }
}

QString dateTimeToString(uint date)
{
    if (date == 0) {
        return QString();
    }

    const QString format = QLatin1String("ddd MMM d HH:mm:ss yyyy");
    QDateTime dt;
    dt.setTime_t(date);
    return dt.toUTC().toString(format);
}

QString calcMD5Sum(const QString &str)
{
    md5Machine.reset();
    md5Machine.addData(str.toUtf8());
    return QLatin1String(md5Machine.result().toHex().constData());
}

QString resolveEntities(const QString &str)
{
    return KCharsets::resolveEntities(str);
}

QString escapeSpecialCharacters(const QString &strp)
{
    QString str(strp);
    str.replace(QLatin1Char('&'), QLatin1String("&amp;"));
    str.replace(QLatin1Char('\"'), QLatin1String("&quot;"));
    str.replace(QLatin1Char('<'), QLatin1String("&lt;"));
    str.replace(QLatin1Char('>'), QLatin1String("&gt;"));
    str.replace(QLatin1Char('\''), QLatin1String("&apos;"));
    return str.trimmed();
}

QString convertNewlines(const QString &strp)
{
    QString str(strp);
    str.replace(QLatin1Char('\n'), QLatin1String("<br/>"));
    return str;
}

QString plainTextToHtml(const QString &plainText)
{
    QString str(plainText);
    str.replace(QLatin1Char('&'), QLatin1String("&amp;"));
    str.replace(QLatin1Char('\"'), QLatin1String("&quot;"));
    str.replace(QLatin1Char('<'), QLatin1String("&lt;"));
    //str.replace(QLatin1Char('>'), QLatin1String("&gt;"));
    str.replace(QLatin1Char('\n'), QLatin1String("<br/>"));
    return str.trimmed();
}

QString htmlToPlainText(const QString &html)
{
    QString str(html);
    //TODO: preserve some formatting, such as line breaks
    str.remove(QRegExp(QLatin1String("<[^>]*>"))); // remove tags
    str = resolveEntities(str);
    return str.trimmed();
}

namespace
{
static QRegExp tagRegExp;
static bool tagRegExpSet = false;
}

bool stringContainsMarkup(const QString &str)
{
    //check for entities
    if (str.contains(QRegExp(QLatin1String("&[a-zA-Z0-9#]+;")))) {
        return true;
    }

    const int ltc = str.count(QLatin1Char('<'));
    if (ltc == 0) {
        return false;
    }

    if (!tagRegExpSet) {
        tagRegExp = QRegExp(QLatin1String("<\\w+.*/?>"));
        tagRegExpSet = true;
    }
    return str.contains(tagRegExp);
}

bool isHtml(const QString &str)
{
    //check for entities
    if (str.contains(QRegExp(QLatin1String("&[a-zA-Z0-9#]+;")))) {
        return true;
    }

    const int ltc = str.count(QLatin1Char('<'));
    if (ltc == 0) {
        return false;
    }

    if (!tagRegExpSet) {
        tagRegExp = QRegExp(QLatin1String("<\\w+.*/?>"));
        tagRegExpSet = true;
    }
    if (str.contains(tagRegExp)) {
        return true;
    }

    return false;
}

QString normalize(const QString &str)
{
    return isHtml(str) ? str.trimmed() : plainTextToHtml(str);
}

QString normalize(const QString &strp, bool isCDATA, bool containsMarkup)
{
    if (containsMarkup) {
        return strp.trimmed();
    } else {
        if (isCDATA) {
            QString str = resolveEntities(strp);
            str = escapeSpecialCharacters(str);
            str = convertNewlines(str);
            str = str.trimmed();
            return str;
        } else {
            QString str = escapeSpecialCharacters(strp);
            str = str.trimmed();
            return str;
        }
    }
}

PersonPtr personFromString(const QString &strp)
{
    QString str = strp.trimmed();
    if (str.isEmpty()) {
        return PersonPtr(new PersonImpl());
    }

    str = resolveEntities(str);
    QString name;
    QString uri;
    QString email;

    // look for something looking like a mail address ("foo@bar.com",
    // "<foo@bar.com>") and extract it

    QRegExp remail(QLatin1String("<?([^@\\s<]+@[^>\\s]+)>?")); // FIXME: user "proper" regexp,
    // search kmail source for it

    int pos = remail.indexIn(str);
    if (pos != -1) {
        QString all = remail.cap(0);
        email = remail.cap(1);
        str.remove(all); // remove mail address
    }

    // replace "mailto", "(", ")" (to be extended)
    email.remove(QLatin1String("mailto:"));
    email.remove(QRegExp(QLatin1String("[\\(\\)]")));

    // simplify the rest and use it as name

    name = str.simplified();

    // after removing the email, str might have
    // the format "(Foo M. Bar)". We cut off
    // parentheses if there are any. However, if
    // str is of the format "Foo M. Bar (President)",
    // we should not cut anything.

    QRegExp rename(QLatin1String("^\\(([^\\)]*)\\)"));

    if (rename.exactMatch(name)) {
        name = rename.cap(1);
    }

    name = name.isEmpty() ? QString() : name;
    email = email.isEmpty() ? QString() : email;
    uri = uri.isEmpty() ? QString() : uri;

    if (name.isEmpty() && email.isEmpty() && uri.isEmpty()) {
        return PersonPtr(new PersonImpl());
    }

    return PersonPtr(new PersonImpl(name, uri, email));
}

ElementType::ElementType(const QString &localnamep,
                         const QString &nsp) : ns(nsp), localname(localnamep)
{
}

bool ElementType::operator==(const ElementType &other) const
{
    return localname == other.localname && ns == other.ns;
}

} // namespace Syndication

