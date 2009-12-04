/*
 * Copyright (c) 2001, 2002, 2003 Frerich Raabe <raabe@kde.org>
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. For licensing and distribution details, check the
 * accompanying file 'COPYING'.
 */

#ifndef SYNDICATION_DATARETRIEVER_H
#define SYNDICATION_DATARETRIEVER_H

#include "ksyndication_export.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QProcess>

namespace KIO
{
    class Job;
}
class KJob;
class KUrl;

class QByteArray;

namespace Syndication
{

/**
 * Abstract baseclass for all data retriever classes. Subclass this to add
 * a new retrieval algorithm which can then be plugged into the RSS loader.
 * @see Loader, FileRetriever, OutputRetriever
 */
class SYNDICATION_EXPORT DataRetriever : public QObject
{
    Q_OBJECT
    public:
        /**
         * Default constructor.
         */
        DataRetriever();

        /**
         * Destructor.
         */
        virtual ~DataRetriever();

        /**
         * Retrieve data from the given URL. This method is supposed to get
         * reimplemented by subclasses. It will be called by the Loader
         * class in case it needs to retrieve the data.
         * 
         * @param url the URL to retrieve data from
         * 
         * @see Loader::loadFrom()
         */
        virtual void retrieveData(const KUrl& url) = 0;

        /**
         * @return An error code which might give a more precise information
         * about what went wrong in case the 'success' flag returned with
         * the dataRetrieved() signal was 'false'. Note that the meaning of
         * the returned integer depends on the actual data retriever.
         */
        virtual int errorCode() const = 0;

        /**
         * aborts the retrieval process.
         */
        virtual void abort() = 0;

    Q_SIGNALS:
        /**
         * Emit this signal to tell the Loader class that the retrieval
         * process was finished.
         * @param data Should contain the retrieved data and will get
         * parsed by the Loader class.
         * @param success Indicates whether there were any problems during
         * the retrieval process. Pass 'true' to indicate that everything
         * went seamlessy, 'false' to tell the Loader that something went
         * wrong and that the data parameter might contain no or invalid
         * data.
         */

        void dataRetrieved(const QByteArray& data, bool success);

    private:
        DataRetriever(const DataRetriever& other);
        DataRetriever& operator=(const DataRetriever& other);
};


/**
 * Implements a data retriever which executes a program and stores returned
 * by the program on stdout. To be used with Loader::loadFrom().
 * @see DataRetriever, Loader::loadFrom()
 */
class SYNDICATION_EXPORT OutputRetriever : public DataRetriever
{
    Q_OBJECT

    public:

        /**
         * Default constructor.
         */
        OutputRetriever();

        /**
         * Destructor.
         */
        virtual ~OutputRetriever();

        /**
         * Executes the program referenced by the given URL and retrieves
         * the data which the program prints to stdout.
         * @param url An URL which is supposed to reference an executable
         * file.
         * @see Loader::loadFrom()
         */
        virtual void retrieveData(const KUrl& url);

        /**
         * @return The error code for the last process of retrieving data.
         * 0 is returned in case there was no error, otherwise an error
         * code which depends on the particular program which was run is
         * returned.
         */
        virtual int errorCode() const;

        virtual void abort() {}

    private Q_SLOTS:
        void slotFinished ( int exitCode, QProcess::ExitStatus exitStatus ) ;

    private:
        OutputRetriever(const OutputRetriever& other);
        OutputRetriever& operator=(const OutputRetriever& other);

        struct OutputRetrieverPrivate;
        OutputRetrieverPrivate* const d;
};

/**
 * Implements a file retriever, to be used with Loader::loadFrom().
 * @see DataRetriever, Loader::loadFrom()
 */
class SYNDICATION_EXPORT FileRetriever : public DataRetriever
{
    Q_OBJECT

    public:

        /**
         * Default constructor.
         */
        FileRetriever();

        /**
         * Destructor.
         */
        virtual ~FileRetriever();

        /**
         * Downloads the file referenced by the given URL and passes it's
         * contents on to the Loader.
         * @param url An URL referencing a file which is assumed to
         * reference valid XML.
         * @see Loader::loadFrom()
         */
        virtual void retrieveData(const KUrl& url);

        /**
         * @return The error code for the last process of retrieving data.
         * The returned numbers correspond directly to the error codes
         * <a href="http://developer.kde.org/documentation/library/cvs-api/classref/kio/KIO.html#Error">as
         * defined by KIO</a>.
         */
        virtual int errorCode() const;

        /**
         * aborts the retrieval process.
         */
        virtual void abort();

        /**
         * sets whether the retriever should use the KHTML cache or
         * always refetch the file. By default, the cache is used.
         * 
         * @param enabled whether to use the HTML cache or not
         */
        static void setUseCache(bool enabled);
        
        /**
         * sets the user agent string sent to the remote server
         * 
         * @param userAgent user agent string 
         */
        static void setUserAgent(const QString& userAgent);

    Q_SIGNALS:

        /**
         * Signals a permanent redirection. The redirection itself is
         * handled internally, so you don't need to call Loader::loadFrom()
         * with the new URL. This signal is useful in case you want to
         * notify the user, or adjust a database entry.
         * 
         * @param url the new URL after the redirection
         * 
         * @see Loader::loadFrom()
         */
        void permanentRedirection(const KUrl& url);

    protected Q_SLOTS:

        void slotTimeout();

    private Q_SLOTS:

        void slotData(KIO::Job*job, const QByteArray& data);
        void slotResult(KJob* job);
        void slotPermanentRedirection(KIO::Job* job, const KUrl& fromUrl,
                                      const KUrl& toUrl);

    private:

        static bool m_useCache;
        static QString m_userAgent;

        FileRetriever(const FileRetriever& other);
        FileRetriever& operator=(const FileRetriever& other);

        struct FileRetrieverPrivate;
        FileRetrieverPrivate* const d;
};

} // namespace Syndication

#endif // SYNDICATION_DATARETRIEVER_H
