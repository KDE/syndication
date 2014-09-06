cmake_minimum_required(VERSION 2.8.12)

project(Syndication)

# ECM setup
find_package(ECM 1.2.0 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)


# FIXME: Do we want the same versions in kdepimlibs and kf5?
set(KF5_VERSION "5.2.0")
set(KDEPIMLIBS_VERSION "4.71.0")

ecm_setup_version(${KDEPIMLIBS_VERSION} VARIABLE_PREFIX SYNDICATION
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/syndication_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5KIO ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Codecs ${KF5_VERSION} CONFIG REQUIRED)

set(Boost_MINIMUM_VERSION "1.34.0")
find_package(Boost ${Boost_MINIMUM_VERSION})
set_package_properties(Boost PROPERTIES
                             DESCRIPTION "Boost C++ Libraries"
                             URL "http://www.boost.org"
                             TYPE REQUIRED
)
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")

########### Targets ###########

add_subdirectory(src/syndication)
add_subdirectory(autotests)
add_subdirectory(tests)
########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Syndication")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5SyndicationConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5SyndicationTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5SyndicationTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/syndication_version.h
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR} COMPONENT Devel
)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()
