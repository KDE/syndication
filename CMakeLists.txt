cmake_minimum_required(VERSION 3.5)

set(KF5_VERSION "5.63.0") # handled by release scripts
set(KF5_DEP_VERSION "5.62.0") # handled by release scripts

project(Syndication VERSION ${KF5_VERSION})

set(REQUIRED_QT_VERSION 5.11.0)

# ECM setup
find_package(ECM ${KF5_DEP_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMCoverageOption)
include(ECMQtDeclareLoggingCategory)
include(ECMAddQch)
include(ECMGeneratePriFile)

ecm_setup_version(PROJECT VARIABLE_PREFIX SYNDICATION
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/syndication_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(Qt5Xml ${REQUIRED_QT_VERSION} CONFIG REQUIRED)

find_package(KF5Codecs ${KF5_DEP_VERSION} CONFIG REQUIRED)

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

########### Targets ###########
add_definitions(-DQT_NO_FOREACH)
add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Syndication")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5Syndication_QCH
        FILE KF5SyndicationQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5SyndicationQchTargets.cmake\")")
endif()

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

install(FILES syndication.categories  DESTINATION  ${KDE_INSTALL_LOGGINGCATEGORIESDIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
