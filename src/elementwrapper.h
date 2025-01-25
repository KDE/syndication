/*
    This file is part of the syndication library
    SPDX-FileCopyrightText: 2006 Frank Osterfeld <osterfeld@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SYNDICATION_ELEMENTWRAPPER_H
#define SYNDICATION_ELEMENTWRAPPER_H

#include <QSharedPointer>
#include <QString>

#include "syndication_export.h"

class QDomElement;
template<class T>
class QList;

namespace Syndication
{
/*!
 * \class Syndication::ElementWrapper
 * \inmodule Syndication
 * \inheaderfile Syndication/ElementWrapper
 *
 * \brief A wrapper for XML elements.
 *
 * This is the base class for the (lazy) wrappers
 * used in the RSS2 and Atom parsers. The wrapped element can be accessed
 * via element(). It also contains several helper functions for XML processing.
 */
class SYNDICATION_EXPORT ElementWrapper
{
public:
    /*!
     * Creates a element wrapper wrapping a null element.
     * isNull() will return \c true for these instances.
     */
    ElementWrapper();

    /*!
     * Copy constructor. The instances share the same element.
     *
     * \a other the element wrapper to copy
     */
    ElementWrapper(const ElementWrapper &other);

    /*!
     * Creates an element wrapper wrapping the DOM element \a element
     *
     * \a element the element to wrap
     */
    ElementWrapper(const QDomElement &element); // implicit

    virtual ~ElementWrapper();

    /*!
     * Assigns another element wrapper to this one. Both instances
     * share the same wrapped element instance.
     *
     * \a other the element wrapper to assign
     *
     * Returns reference to this instance
     */
    ElementWrapper &operator=(const ElementWrapper &other);

    /*!
     * Compares two wrappers.
     *
     * Two wrappers are equal if and only if
     * the wrapped elements are equal.
     *
     * \a other another element wrapper to compare to
     */
    bool operator==(const ElementWrapper &other) const;

    /*!
     * returns the wrapped resource.
     */
    const QDomElement &element() const;

    /*!
     * Returns \c true if isNull() is true for the wrapped element,
     * \c false otherwise
     */
    Q_REQUIRED_RESULT bool isNull() const;

    /*!
     * Returns the xml:base value to be used for the wrapped element.
     *
     * The xml:base attribute establishes the base URI for resolving any
     * relative references found in its scope (its own element and all
     * descendants). (See also completeURI())
     */
    Q_REQUIRED_RESULT QString xmlBase() const;

    /*!
     * Returns the xml:lang value to be used for the wrapped element.
     *
     * The xml:lang attribute indicates the natural language for its element
     * and all descendants.
     */
    Q_REQUIRED_RESULT QString xmlLang() const;

    /*!
     * Completes relative URIs with a prefix specified via xml:base.
     *
     * Example:
     * \code
     * xml:base="http://www.foo.org/", uri="announcements/bar.html"
     * \endcode
     *
     * is completed to \c http://www.foo.org/announcements/bar.html
     *
     * See also xmlBase().
     *
     * \a uri a possibly relative URI
     *
     * Returns the resolved, absolute URI (using xml:base), if \a uri is
     * a relative, valid URI.
     *
     * If \a uri is not valid, absolute, or no
     * xml:base is set in the scope of this element, \a uri is returned
     * unmodified.
     */
    Q_REQUIRED_RESULT QString completeURI(const QString &uri) const;

    /*!
     * Extracts the text from a child element, respecting namespaces.
     * If there is more than one child with the same tag name, the first one is
     * processed.
     *
     * For instance, when the wrapped element is \c <thisElement>:
     * \badcode
     * <thisElement>
     *     <atom:title>Hi there</atom:title>
     * </thisElement>
     * \endcode
     * \code
     * extractElementText("http://www.w3.org/2005/Atom", "title")
     * \endcode
     * will return the text content of \c atom:title, "Hi there".
     * (Assuming that "atom" is defined as "http://www.w3.org/2005/Atom")
     *
     * \a namespaceURI the namespace URI of the element to extract
     *
     * \a localName the local name (local within its namespace) of the
     * element to extract
     *
     * Returns the (trimmed) text content of \c localName, or a null string
     * if there is no such tag
     */
    Q_REQUIRED_RESULT QString extractElementTextNS(const QString &namespaceURI, const QString &localName) const;

    /*!
     * Extracts the text from a child element, ignoring namespaces.
     * For instance, when the wrapped element is \c <thisElement>:
     * \badcode
     * <thisElement>
     *     <title>Hi there</title>
     * </thisElement>
     * \endcode
     *
     * extractElementText("title") will return the text content
     * of \c title, "Hi there".
     *
     * \a tagName the name of the element to extract
     *
     * Returns the (trimmed) text content of \a tagName, or a null string if
     * there is no such tag
     */
    Q_REQUIRED_RESULT QString extractElementText(const QString &tagName) const;

    /*!
     * Returns all child elements with tag name \a tagName
     *
     * Contrary to QDomElement::elementsByTagName() only direct descendents
     * are returned.
     *
     * \a tagName the tag name of the elements to extract
     *
     * Returns a list of child elements with the given tag name
     */
    Q_REQUIRED_RESULT QList<QDomElement> elementsByTagName(const QString &tagName) const;

    /*!
     * Returns the child nodes of the wrapped element as XML.
     *
     * See childNodesAsXML(const QDomElement& parent) for details
     *
     * Returns XML serialization of the wrapped element's children
     */
    Q_REQUIRED_RESULT QString childNodesAsXML() const;

    /*!
     * Concatenates the XML representations of all children.
     *
     * Example: If \a parent is an \c xhtml:body element like
     * \badcode
     * <xhtml:body><p>foo</p><blockquote>bar</blockquote></xhtml:body>
     * \endcode
     * this function returns
     * \badcode
     * <p>foo</p><blockquote>bar</blockquote>
     * \endcode
     *
     * namespace and xml:base information are preserved.
     *
     * \a parent the DOM element whose children should be returned as
     * XML
     *
     * Returns XML serialization of parent's children
     */
    Q_REQUIRED_RESULT static QString childNodesAsXML(const QDomElement &parent);

    /*!
     * Returns all child elements with tag name \a tagName
     * and namespace URI \a nsURI.
     *
     * Contrary to QDomElement::elementsByTagNameNS() only direct
     * descendents are returned
     *
     * \a nsURI the namespace URI
     *
     * \a tagName the local name (local within its namespace) of the
     * element to search for
     *
     * Returns a list of child elements with the given namespace URI
     * and tag name
     */
    Q_REQUIRED_RESULT QList<QDomElement> elementsByTagNameNS(const QString &nsURI, const QString &tagName) const;

    /*!
     * Searches the direct children of the wrapped element for an element
     * with a given namespace and tag name.
     *
     * \a nsURI the namespace URI
     *
     * \a tagName the local name (local within its namespace) of the
     * element to search for
     *
     * Returns the first child element with the given namespace URI and tag
     * name, or a null element if no such element was found.
     */
    Q_REQUIRED_RESULT QDomElement firstElementByTagNameNS(const QString &nsURI, const QString &tagName) const;

    /*!
     * Returns the wrapped element's text or an empty string.
     *
     * For more information, see QDomElement::text();
     */
    Q_REQUIRED_RESULT QString text() const;

    /*!
     * Returns the attribute called name.
     *
     * If the attribute does not exist
     * defValue is returned.
     * (which is a null string by default).
     *
     * \a name tag name
     *
     * \a defValue the default value
     */
    Q_REQUIRED_RESULT QString attribute(const QString &name, const QString &defValue = QString()) const;

    /*!
     * Returns the attribute with the local name \a localName and the
     * namespace URI \a nsURI.
     *
     * If the attribute does not exist \a defValue is returned (which is a
     * null string by default).
     *
     * \a nsURI namespace URI
     *
     * \a localName local tag name
     *
     * \a defValue the default value
     */
    Q_REQUIRED_RESULT QString attributeNS(const QString &nsURI, const QString &localName, const QString &defValue = QString()) const;

    /*!
     * Returns \c true if this element has an attribute called \a name;
     * otherwise returns \c false.
     *
     * \a name the attribute name (without namespace)
     */
    Q_REQUIRED_RESULT bool hasAttribute(const QString &name) const;

    /*!
     * Returns \c true if this element has an attribute with the local name
     * \a localName and the namespace URI \a nsURI; otherwise returns \c false.
     *
     * \a nsURI namespace URI
     *
     * \a localName local attribute name
     */
    Q_REQUIRED_RESULT bool hasAttributeNS(const QString &nsURI, const QString &localName) const;

private:
    class ElementWrapperPrivate;
    QSharedPointer<ElementWrapperPrivate> d;
};

} // namespace Syndication

#endif // SYNDICATION_ELEMENTWRAPPER_H
