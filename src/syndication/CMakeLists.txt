
set(librss2local_SRCS
    rss2/category.cpp
    rss2/cloud.cpp
    rss2/document.cpp
    rss2/enclosure.cpp
    rss2/image.cpp
    rss2/item.cpp
    rss2/parser.cpp
    rss2/source.cpp
    rss2/textinput.cpp
    rss2/tools_p.cpp
)

set(librdflocal_la_SRCS
    rdf/contentvocab.cpp
    rdf/document.cpp
    rdf/dublincore.cpp
    rdf/dublincorevocab.cpp
    rdf/image.cpp
    rdf/item.cpp
    rdf/literal.cpp
    rdf/model.cpp
    rdf/modelmaker.cpp
    rdf/node.cpp
    rdf/nodevisitor.cpp
    rdf/parser.cpp
    rdf/property.cpp
    rdf/rdfvocab.cpp
    rdf/resource.cpp
    rdf/resourcewrapper.cpp
    rdf/rssvocab.cpp
    rdf/sequence.cpp
    rdf/statement.cpp
    rdf/syndicationinfo.cpp
    rdf/syndicationvocab.cpp
    rdf/textinput.cpp
)

set(libatomlocal_SRCS
    atom/atomtools.cpp
    atom/category.cpp
    atom/constants.cpp
    atom/content.cpp
    atom/document.cpp
    atom/entry.cpp
    atom/generator.cpp
    atom/link.cpp
    atom/parser.cpp
    atom/person.cpp
    atom/source.cpp
)

set(libmapperrss2local_SRCS
    mapper/categoryrss2impl.cpp
    mapper/enclosurerss2impl.cpp
    mapper/feedrss2impl.cpp
    mapper/imagerss2impl.cpp
    mapper/itemrss2impl.cpp
)

set(libmapperrdflocal_SRCS
    mapper/feedrdfimpl.cpp
    mapper/imagerdfimpl.cpp
    mapper/itemrdfimpl.cpp
)

set(libmapperatomlocal_SRCS
    mapper/categoryatomimpl.cpp
    mapper/enclosureatomimpl.cpp
    mapper/feedatomimpl.cpp
    mapper/itematomimpl.cpp
)
set(libsyndicationlocal_SRCS
    abstractparser.cpp
    category.cpp
    constants.cpp
    dataretriever.cpp
    documentsource.cpp
    documentvisitor.cpp
    elementwrapper.cpp
    enclosure.cpp
    feed.cpp
    global.cpp
    image.cpp
    item.cpp
    loader.cpp
    person.cpp
    personimpl.cpp
    specificdocument.cpp
    specificitem.cpp
    specificitemvisitor.cpp
    tools.cpp
)

set(syndication_SRCS
    ${librss2local_SRCS}
    ${librdflocal_la_SRCS}
    ${libatomlocal_SRCS}
    ${libmappercommonlocal_SRCS}
    ${libmapperrss2local_SRCS}
    ${libmapperrdflocal_SRCS}
    ${libmapperatomlocal_SRCS}
    ${libsyndicationlocal_SRCS}
)

add_library(KF5Syndication ${syndication_SRCS})

generate_export_header(KF5Syndication BASE_NAME syndication)

add_library(KF5::Syndication ALIAS KF5Syndication)

target_include_directories(KF5Syndication INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/Syndication;${Boost_INCLUDE_DIR}>")
target_include_directories(KF5Syndication PUBLIC "$<BUILD_INTERFACE:${Syndication_SOURCE_DIR}/src;${Syndication_BINARY_DIR}/src>")
target_include_directories(KF5Syndication  PUBLIC "$<BUILD_INTERFACE:${Syndication_BINARY_DIR}>")

kde_target_enable_exceptions(KF5Syndication PUBLIC)

target_link_libraries(KF5Syndication
    PUBLIC
    Qt5::Core
    PRIVATE
    KF5::KIOCore
    KF5::KDELibs4Support
)

set_target_properties(KF5Syndication PROPERTIES
    VERSION ${SYNDICATION_VERSION_STRING}
    SOVERSION ${SYNDICATION_SOVERSION}
    EXPORT_NAME Syndication
)

add_subdirectory(atom)
add_subdirectory(rdf)
add_subdirectory(rss2)

ecm_generate_headers(Syndication_CamelCase_HEADERS
  HEADER_NAMES
  AbstractParser
  Category
  Constants
  DataRetriever
  DocumentSource
  DocumentVisitor
  ElementWrapper
  Enclosure
  Feed
  Global
  Image
  Item
  Loader
  Mapper
  ParserCollection
  Person
  SpecificDocument
  SpecificItem
  SpecificItemVisitor
  Syndication
  Tools

  PREFIX Syndication
  REQUIRED_HEADERS Syndication_HEADERS
)


install(TARGETS KF5Syndication EXPORT KF5SyndicationTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/syndication_export.h
    ${Syndication_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/syndication
    COMPONENT Devel
)

install(FILES
    ${Syndication_CamelCase_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/Syndication
    COMPONENT Devel

)

ecm_generate_pri_file(BASE_NAME Syndication LIB_NAME KF5Syndication DEPS "KIOCore KDELibs4Support" FILENAME_VAR PRI_FILENAME)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
