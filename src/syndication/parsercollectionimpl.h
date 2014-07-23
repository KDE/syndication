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

#ifndef SYNDICATION_PARSERCOLLECTIONIMPL_H
#define SYNDICATION_PARSERCOLLECTIONIMPL_H

#include <syndication/specificdocument.h>
#include <syndication/abstractparser.h>
#include <syndication/documentsource.h>
#include <syndication/parsercollection.h>
#include <syndication/feed.h>
#include <syndication/global.h>
#include <syndication/mapper.h>

#include <QtXml/QDomDocument>
#include <QtCore/QHash>
#include <QtCore/QString>

namespace Syndication
{

//@cond PRIVATE
/** @internal
 */
// default implementation of ParserCollection. This is separated
// from the interface to move the implementation out of the public API
// (template classes require implementations to be in the header)

template <class T>
class SYNDICATION_EXPORT ParserCollectionImpl : public ParserCollection<T>
{
public:

    ParserCollectionImpl();

    virtual ~ParserCollectionImpl();

    boost::shared_ptr<T> parse(const DocumentSource &source,
                               const QString &formatHint = QString());

    bool registerParser(AbstractParser *parser, Mapper<T> *mapper);

    void changeMapper(const QString &format, Mapper<T> *mapper);

    ErrorCode lastError() const;

private:

    ParserCollectionImpl(const ParserCollectionImpl &);
    ParserCollectionImpl &operator=(const ParserCollectionImpl &);
    QHash<QString, AbstractParser *> m_parsers;
    QHash<QString, Mapper<T>*> m_mappers;
    QList<AbstractParser *> m_parserList;

    ErrorCode m_lastError;
};

//@endcond

//template <class T>
//class ParserCollectionImpl<T>::ParserCollectionImplPrivate

template <class T>
ParserCollectionImpl<T>::ParserCollectionImpl()
{
}

template <class T>
ParserCollectionImpl<T>::~ParserCollectionImpl()
{
    QList<AbstractParser *> list = m_parsers.values();
    QList<AbstractParser *>::ConstIterator it = list.constBegin();
    QList<AbstractParser *>::ConstIterator end = list.constEnd();

    for (; it != end; ++it) {
        delete *it;
    }

    QList<QString> m = m_mappers.keys();
    QList<QString>::ConstIterator itm = m.constBegin();
    QList<QString>::ConstIterator endm = m.constEnd();

    for (; itm != endm; ++itm) {
        delete m_mappers[*itm];
    }

}

template <class T>
bool ParserCollectionImpl<T>::registerParser(AbstractParser *parser, Mapper<T> *mapper)
{
    if (m_parsers.contains(parser->format())) {
        return false;
    }

    m_parserList.append(parser);
    m_parsers.insert(parser->format(), parser);
    m_mappers.insert(parser->format(), mapper);
    return true;
}
template <class T>
void ParserCollectionImpl<T>::changeMapper(const QString &format, Mapper<T> *mapper)
{
    m_mappers[format] = mapper;
}

template <class T>
boost::shared_ptr<T> ParserCollectionImpl<T>::parse(const DocumentSource &source, const QString &formatHint)
{
    m_lastError = Syndication::Success;

    if (!formatHint.isNull() && m_parsers.contains(formatHint)) {
        if (m_parsers[formatHint]->accept(source)) {
            SpecificDocumentPtr doc = m_parsers[formatHint]->parse(source);
            if (!doc->isValid()) {
                m_lastError = InvalidFormat;
                return FeedPtr();
            }

            return m_mappers[formatHint]->map(doc);
        }
    }

    Q_FOREACH (AbstractParser *i, m_parserList) {
        if (i->accept(source)) {
            SpecificDocumentPtr doc = i->parse(source);
            if (!doc->isValid()) {
                m_lastError = InvalidFormat;
                return FeedPtr();
            }

            return m_mappers[i->format()]->map(doc);
        }
    }
    if (source.asDomDocument().isNull()) {
        m_lastError = InvalidXml;
    } else {
        m_lastError = XmlNotAccepted;
    }

    return FeedPtr();
}

template <class T>
Syndication::ErrorCode ParserCollectionImpl<T>::lastError() const
{
    return m_lastError;
}

template <class T>
ParserCollectionImpl<T>::ParserCollectionImpl(const ParserCollectionImpl &)
{
}

template <class T>
ParserCollectionImpl<T> &ParserCollectionImpl<T>::operator=(const ParserCollectionImpl &)
{
    return *this;
}

} // namespace Syndication

#endif // SYNDICATION_PARSERCOLLECTIONIMPL_H
