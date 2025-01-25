/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2005 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_SPECIFICDOCUMENT_H
#define SYNDICATION_SPECIFICDOCUMENT_H

#include "syndication_export.h"

#include <QSharedPointer>

class QString;

namespace Syndication
{
class DocumentVisitor;
class SpecificDocument;

typedef QSharedPointer<SpecificDocument> SpecificDocumentPtr;

/*!
 * \class Syndication::SpecificDocument
 * \inmodule Syndication
 * \inheaderfile Syndication/SpecificDocument
 *
 * \brief Document interface for format-specific feed documents as parsed from a
 * document source (see DocumentSource).
 *
 * The Document classes from the several syndication formats must implement
 * this interface. It's main purpose is to provide access for document visitors
 * (see DocumentVisitor).
 *
 * Usually it is not necessary to access the format-specific document at all,
 * use Feed for a format-agnostic interface to all feed documents supported by
 * the library.
 */
class SYNDICATION_EXPORT SpecificDocument
{
public:
    virtual ~SpecificDocument();

    /*!
     * This must be implemented for the double dispatch
     * technique (Visitor pattern).
     *
     * The usual implementation is
     * \code
     * return visitor->visit(this);
     * \endcode
     *
     * See also DocumentVisitor.
     *
     * \a visitor the visitor "visiting" this object
     */
    virtual bool accept(DocumentVisitor *visitor) = 0;

    /*!
     * Returns whether this document is valid or not.
     *
     * Invalid documents do not contain any useful
     * information.
     */
    virtual bool isValid() const = 0;

    /*!
     * Returns a description of the document for debugging purposes.
     */
    virtual QString debugInfo() const = 0;
};

} // namespace Syndication

#endif // SYNDICATION_SPECIFICDOCUMENT_H
