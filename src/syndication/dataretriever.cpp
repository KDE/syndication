/*
 * dataretriever.cpp
 *
 * Copyright (c) 2001, 2002, 2003 Frerich Raabe <raabe@kde.org>
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. For licensing and distribution details, check the
 * accompanying file 'COPYING'.
 */

#include "dataretriever.h"
#include "global.h"
#include "syndication_version.h"

#include <KProcess>
#include <QUrl>

#include <QBuffer>
#include <QTimer>

namespace Syndication
{

DataRetriever::DataRetriever()
{
}

DataRetriever::~DataRetriever()
{
}

struct OutputRetriever::OutputRetrieverPrivate {
    OutputRetrieverPrivate() : process(nullptr), buffer(nullptr), lastError(0)
    {
    }

    ~OutputRetrieverPrivate()
    {
        delete process;
        delete buffer;
    }

    KProcess *process;
    QBuffer *buffer;
    int lastError;
};

OutputRetriever::OutputRetriever() : d(new OutputRetrieverPrivate)
{
}

OutputRetriever::~OutputRetriever()
{
    delete d;
}

void OutputRetriever::retrieveData(const QUrl &url)
{
    // Ignore subsequent calls if we didn't finish the previous job yet.
    if (d->buffer || d->process) {
        return;
    }

    d->buffer = new QBuffer;
    d->buffer->open(QIODevice::WriteOnly);

    d->process = new KProcess();
    connect(d->process, QOverload<int,QProcess::ExitStatus>::of(&KProcess::finished), this, &OutputRetriever::slotFinished);
    d->process->setShellCommand(url.path());
    d->process->start();
}

int OutputRetriever::errorCode() const
{
    return d->lastError;
}

void OutputRetriever::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    if (!d->process->exitCode()) {
        d->lastError = d->process->exitCode();
    }

    QByteArray data = d->process->readAllStandardOutput();

    delete d->buffer;
    d->buffer = nullptr;

    int code = d->process->exitCode();

    delete d->process;
    d->process = nullptr;

    emit dataRetrieved(data, exitStatus == QProcess::NormalExit && code == 0);
}

} // namespace Syndication

