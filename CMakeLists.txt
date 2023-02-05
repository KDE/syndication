cmake_minimum_required(VERSION 3.16)

set(KF_VERSION "5.103.0") # handled by release scripts
set(KF_DEP_VERSION "5.103.0") # handled by release scripts

project(Syndication VERSION ${KF_VERSION})

set(REQUIRED_QT_VERSION 5.15.2)

# ECM setup
find_package(ECM ${KF_DEP_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEGitCommitHooks)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(ECMAddQch)
include(ECMGeneratePriFile)
include(ECMDeprecationSettings)

ecm_setup_version(PROJECT VARIABLE_PREFIX SYNDICATION
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/syndication_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SyndicationConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(Qt${QT_MAJOR_VERSION}Xml ${REQUIRED_QT_VERSION} CONFIG REQUIRED)

find_package(KF5Codecs ${KF_DEP_VERSION} CONFIG REQUIRED)

ecm_set_disabled_deprecation_versions(
    QT 5.15.2
    KF 5.97.0
)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

########### Targets ###########
if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif()
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
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Syndication COMPONENT Devel
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
