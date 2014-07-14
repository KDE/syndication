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

#include "testpersonimpl.h"
#include "person.h"
#include "personimpl.h"
#include "tools.h"
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>

using Syndication::Person;
using Syndication::PersonPtr;
using Syndication::PersonImpl;

void TestPersonImpl::fromString()
{
    QStringList s;
    QList<PersonPtr> p;



    s.append(QString());
    p.append(PersonPtr(new PersonImpl(QString(), QString(), QString())));

    s.append(QLatin1String(""));
    p.append(PersonPtr(new PersonImpl(QString(), QString(), QString())));

    s.append(QLatin1String("foo@bar.com"));
    p.append(PersonPtr(new PersonImpl(QString(), QString(), QLatin1String("foo@bar.com"))));

    s.append(QLatin1String("<foo@bar.com>"));
    p.append(PersonPtr(new PersonImpl(QString(), QString(), QLatin1String("foo@bar.com"))));

    s.append(QLatin1String("Foo"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("Foo"), QString(), QString())));

    s.append(QLatin1String("Foo M. Bar"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("Foo M. Bar"), QString(), QString())));

    s.append(QLatin1String("Foo <foo@bar.com>"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("Foo"), QString(), QLatin1String("foo@bar.com"))));

    s.append(QLatin1String("Foo Bar <foo@bar.com>"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("Foo Bar"), QString(), QLatin1String("foo@bar.com"))));

    s.append(QLatin1String("John Doe (President) <john@doe.com>"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("John Doe (President)"), QString(), QLatin1String("john@doe.com"))));

    s.append(QLatin1String("John Doe (President)"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("John Doe (President)"), QString(), QString() )));

    s.append(QLatin1String("John Doe (President)) <john@doe.com>"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("John Doe (President))"), QString(), QLatin1String("john@doe.com"))));

    s.append(QLatin1String("(President) John Doe <john@doe.com>"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("(President) John Doe"), QString(), QLatin1String("john@doe.com"))));

    s.append(QLatin1String("<foo@bar.com> (Foo Bar)"));
    p.append(PersonPtr(new PersonImpl(QLatin1String("Foo Bar"), QString(), QLatin1String("foo@bar.com"))));

    // s.append("OnAhlmann(mailto:&amp;#111;&amp;#110;&amp;#97;&amp;#104;&amp;#108;&amp;#109;&amp;#97;&amp;#110;&amp;#110;&amp;#64;&amp;#103;&amp;#109;&amp;#97;&amp;#105;&amp;#108;&amp;#46;&amp;#99;&amp;#111;&amp;#109;)");
    // p.append(PersonPtr(new PersonImpl("OnAhlmann", QString(), "onahlmann@gmail.com")));

    QList<PersonPtr> q;

    QStringList::ConstIterator it = s.constBegin();
    QStringList::ConstIterator end = s.constEnd();
    QList<PersonPtr>::ConstIterator pit = p.constBegin();

    while (it != end)
    {
        PersonPtr q(Syndication::personFromString(*it));
        QCOMPARE(q->name(), (*pit)->name());
        QCOMPARE(q->email(), (*pit)->email());
        QCOMPARE(q->uri(), (*pit)->uri());

        ++it;
        ++pit;
    }
}

QTEST_MAIN(TestPersonImpl)

