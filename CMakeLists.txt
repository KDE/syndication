cmake_minimum_required(VERSION 2.8.12)

project(Syndication)

# ECM setup
find_package(ECM 0.0.9 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(FeatureSummary)
include(ECMSetupVersion)
#include(CMakePackageConfigHelpers)
#include(KDEInstallDirs)
#include(KDEFrameworkCompilerSettings)
#include(KDECMakeSettings)

# FIXME: Do we want the same versions in kdepimlibs and kf5?
set(KF5_VERSION "5.0.0")

ecm_setup_version(${KF5_VERSION} VARIABLE_PREFIX SYNDICATION
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/syndication_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationsConfigVersion.cmake")

########### Find packages ###########
find_package(KF5 CONFIG REQUIRED COMPONENTS ItemViews KIO KDE4Support)

########### Includes ###########
include_directories(${Syndication_SOURCE_DIR} ${Syndication_BINARY_DIR} ${Boost_INCLUDE_DIR})

########### Targets ###########

add_subdirectory(atom)
add_subdirectory(rdf)
add_subdirectory(rss2)
add_subdirectory(tests)

########### Build parameters ###########

add_definitions( -DQT_STRICT_ITERATORS )
add_definitions( -DQT_NO_CAST_TO_ASCII )
add_definitions( -DQT_NO_CAST_FROM_BYTEARRAY )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")

########### next target ###########

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
    rdf/parser.cpp
    rdf/dublincorevocab.cpp
    rdf/dublincore.cpp
    rdf/syndicationvocab.cpp
    rdf/syndicationinfo.cpp
    rdf/contentvocab.cpp
    rdf/item.cpp
    rdf/image.cpp
    rdf/textinput.cpp
    rdf/document.cpp
    rdf/rssvocab.cpp
    rdf/node.cpp
    rdf/property.cpp
    rdf/literal.cpp
    rdf/resource.cpp
    rdf/model.cpp
    rdf/modelmaker.cpp
    rdf/rdfvocab.cpp
    rdf/sequence.cpp
    rdf/statement.cpp
    rdf/resourcewrapper.cpp
    rdf/nodevisitor.cpp
)

set(libatomlocal_SRCS
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
    atom/atomtools.cpp
)

set(libmapperrss2local_SRCS
    mapper/feedrss2impl.cpp
    mapper/itemrss2impl.cpp
    mapper/enclosurerss2impl.cpp
    mapper/categoryrss2impl.cpp
    mapper/imagerss2impl.cpp
)

set(libmapperrdflocal_SRCS
    mapper/feedrdfimpl.cpp
    mapper/itemrdfimpl.cpp
    mapper/imagerdfimpl.cpp
)

set(libmapperatomlocal_SRCS
    mapper/feedatomimpl.cpp
    mapper/itematomimpl.cpp
    mapper/enclosureatomimpl.cpp
    mapper/categoryatomimpl.cpp
)

set(syndication_SRCS
    ${librss2local_SRCS}
    ${librdflocal_la_SRCS}
    ${libatomlocal_SRCS}
    ${libmappercommonlocal_SRCS}
    ${libmapperrss2local_SRCS}
    ${libmapperrdflocal_SRCS}
    ${libmapperatomlocal_SRCS}
    documentsource.cpp
    documentvisitor.cpp
    elementwrapper.cpp
    constants.cpp
    feed.cpp
    item.cpp
    enclosure.cpp
    category.cpp
    image.cpp
    tools.cpp
    person.cpp
    personimpl.cpp
    loader.cpp
    global.cpp
    dataretriever.cpp
    specificitemvisitor.cpp
    specificitem.cpp
    specificdocument.cpp
    abstractparser.cpp
)

add_library(syndication ${syndication_SRCS})
generate_export_header(syndication)

target_link_libraries(syndication
    KF5::ItemViews
    KF5::KIOCore
    KF5::KDE4Support
)

set_target_properties(syndication PROPERTIES
    VERSION ${SYNDICATION_VERSION_STRING}
    SOVERSION ${SYNDICATION_SOVERSION}
    EXPORT_NAME Syndication
)

#install(TARGETS syndication EXPORT SyndicationTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############

install(FILES
    ${Syndication_BINARY_DIR}/syndication_export.h
    abstractparser.h
    category.h
    constants.h
    dataretriever.h
    documentsource.h
    documentvisitor.h
    elementwrapper.h
    enclosure.h
    feed.h
    global.h
    image.h
    item.h
    loader.h
    mapper.h
    parsercollection.h
    person.h
    specificdocument.h
    specificitem.h
    specificitemvisitor.h
    syndication.h
    tools.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/syndication COMPONENT Devel)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()