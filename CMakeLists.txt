cmake_minimum_required(VERSION 3.0)
set(PIM_VERSION "5.7.40")
set(SYNDICATION_LIB_VERSION ${PIM_VERSION})

project(Syndication VERSION ${SYNDICATION_LIB_VERSION})

# ECM setup
set(KF5_VERSION "5.41.0")

find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMCoverageOption)
include(ECMQtDeclareLoggingCategory)



ecm_setup_version(${SYNDICATION_LIB_VERSION} VARIABLE_PREFIX SYNDICATION
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/syndication_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5KIO ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Codecs ${KF5_VERSION} CONFIG REQUIRED)
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
########### Targets ###########

add_subdirectory(src/syndication)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Syndication")

configure_package_config_file(
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
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
