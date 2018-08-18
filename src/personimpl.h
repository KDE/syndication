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

#ifndef SYNDICATION_PERSONIMPL_H
#define SYNDICATION_PERSONIMPL_H

#include <syndication/person.h>
#include "syndication_export.h"

#include <QString>

namespace Syndication
{

class PersonImpl;

//@cond PRIVATE
typedef QSharedPointer<PersonImpl> PersonImplPtr;

/**
 * @internal
 */
class SYNDICATION_EXPORT PersonImpl : public Person
{
public:

    PersonImpl();
    PersonImpl(const QString &name, const QString &uri, const QString &email);

    Q_REQUIRED_RESULT bool isNull() const override
    {
        return m_null;
    }
    Q_REQUIRED_RESULT QString name() const override
    {
        return m_name;
    }
    Q_REQUIRED_RESULT QString uri() const override
    {
        return m_uri;
    }
    Q_REQUIRED_RESULT QString email() const override
    {
        return m_email;
    }

private:

    bool m_null;
    QString m_name;
    QString m_uri;
    QString m_email;
};
//@endcond

} // namespace Syndication

#endif // SYNDICATION_PERSONIMPL_H
