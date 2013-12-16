cmake_minimum_required(VERSION 2.8.12)

project(Syndication)

# ECM setup
find_package(ECM 0.0.9 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(FeatureSummary)
include(ECMSetupVersion)
include(CMakePackageConfigHelpers)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

# FIXME: Do we want the same versions in kdepimlibs and kf5?
set(KF5_VERSION "5.0.0")

ecm_setup_version(${KF5_VERSION} VARIABLE_PREFIX SYNDICATION
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/syndication_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationsConfigVersion.cmake")

########### Find packages ###########
find_package(KF5 CONFIG REQUIRED COMPONENTS ItemViews KIO KDE4Support)

set(Boost_MINIMUM_VERSION "1.34.0")
find_package(Boost ${Boost_MINIMUM_VERSION})
set_package_properties(Boost PROPERTIES DESCRIPTION "Boost C++ Libraries"
                                                 URL "http://www.boost.org"
                                                 TYPE REQUIRED
)

########### Includes ###########
include_directories(${Syndication_SOURCE_DIR} ${Syndication_BINARY_DIR} ${Boost_INCLUDE_DIR})

########### Build parameters ###########

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")

########### Targets ###########

add_subdirectory(src)
#add_subdirectory(tests)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL   FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()