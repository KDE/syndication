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

#include "cloud.h"

#include <QtCore/QString>

namespace Syndication
{
namespace RSS2
{

Cloud::Cloud() : ElementWrapper()
{
}

Cloud::Cloud(const QDomElement &element) : ElementWrapper(element)
{
}

QString Cloud::domain() const
{
    return attribute(QLatin1String("domain"));
}

int Cloud::port() const
{
    if (hasAttribute(QLatin1String("port"))) {
        bool ok;
        int c = attribute(QLatin1String("port")).toInt(&ok);
        return ok ? c : -1;
    }

    return -1;
}

QString Cloud::path() const
{
    return attribute(QLatin1String("path"));
}

QString Cloud::registerProcedure() const
{
    return attribute(QLatin1String("registerProcedure"));
}

QString Cloud::protocol() const
{

    return attribute(QLatin1String("protocol"));
}

QString Cloud::debugInfo() const
{
    QString info;
    info += QLatin1String("### Cloud: ###################\n");
    if (!domain().isNull()) {
        info += QLatin1String("domain: #") + domain() + QLatin1String("#\n");
    }
    if (port() != -1) {
        info += QLatin1String("port: #") + QString::number(port()) + QLatin1String("#\n");
    }
    if (!path().isNull()) {
        info += QLatin1String("path: #") + path() + QLatin1String("#\n");
    }
    if (!registerProcedure().isNull()) {
        info += QLatin1String("registerProcedure: #") + registerProcedure() + QLatin1String("#\n");
    }
    if (!protocol().isNull()) {
        info += QLatin1String("protocol: #") + protocol() + QLatin1String("#\n");
    }
    info += QLatin1String("### Cloud end ################\n");
    return info;
}

} // namespace RSS2
} // namespace Syndication

