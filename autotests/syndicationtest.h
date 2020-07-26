/*
    This file is part of LibSyndication.
    SPDX-FileCopyrightText: Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/

#ifndef SYNDICATIONTEST_H
#define SYNDICATIONTEST_H

#include <QObject>

class SyndicationTest : public QObject
{
    Q_OBJECT
public:
    explicit SyndicationTest(QObject *parent = nullptr);
    ~SyndicationTest() = default;
private Q_SLOTS:
    void testSyncationFile_data();
    void testSyncationFile();
};

#endif // SYNDICATIONTEST_H
