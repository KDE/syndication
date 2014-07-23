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

#include "syndicationinfo.h"
#include "property.h"
#include "statement.h"
#include "syndicationvocab.h"

#include <tools.h>

#include <QtCore/QString>

namespace Syndication
{
namespace RDF
{

SyndicationInfo::SyndicationInfo(ResourcePtr resource) : ResourceWrapper(resource)
{
}

SyndicationInfo::~SyndicationInfo()
{
}

SyndicationInfo::Period SyndicationInfo::updatePeriod() const
{
    return stringToPeriod(resource()->property(SyndicationVocab::self()->updatePeriod())->asString());
}

int SyndicationInfo::updateFrequency() const
{
    QString freqStr =  resource()->property(SyndicationVocab::self()->updateFrequency())->asString();

    if (freqStr.isEmpty()) {
        return 1;    // 1 is default
    }

    bool ok = false;
    int freq = freqStr.toInt(&ok);

    if (ok) {
        return freq;
    } else {
        return 1;    // 1 is default
    }
}

time_t SyndicationInfo::updateBase() const
{
    QString str =  resource()->property(SyndicationVocab::self()->updateBase())->asString();

    return parseDate(str, ISODate);
}

QString SyndicationInfo::debugInfo() const
{
    QString info;
    if (updatePeriod() != Daily) {
        info += QString::fromLatin1("syn:updatePeriod: #%1#\n").arg(periodToString(updatePeriod()));
    }
    info += QString::fromLatin1("syn:updateFrequency: #%1#\n").arg(QString::number(updateFrequency()));

    QString dbase = dateTimeToString(updateBase());
    if (!dbase.isNull()) {
        info += QString::fromLatin1("syn:updateBase: #%1#\n").arg(dbase);
    }

    return info;
}

QString SyndicationInfo::periodToString(Period period)
{
    switch (period) {
    case Daily:
        return QLatin1String("daily");
    case Hourly:
        return QLatin1String("hourly");
    case Monthly:
        return QLatin1String("monthly");
    case Weekly:
        return QLatin1String("weekly");
    case Yearly:
        return QLatin1String("yearly");
    default: // should never happen
        return QString();
    }
}

SyndicationInfo::Period SyndicationInfo::stringToPeriod(const QString &str)
{
    if (str.isEmpty()) {
        return Daily;    // default is "daily"
    }

    if (str == QLatin1String("hourly")) {
        return Hourly;
    }
    if (str == QLatin1String("monthly")) {
        return Monthly;
    }
    if (str == QLatin1String("weekly")) {
        return Weekly;
    }
    if (str == QLatin1String("yearly")) {
        return Yearly;
    }

    return Daily;  // default is "daily"
}

} // namespace RDF
} // namespace Syndication
