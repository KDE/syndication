
if(KDE4_BUILD_TESTS)

include_directories( ${CMAKE_SOURCE_DIR}/syndication/   )


########### next target ###############

set(testlibsyndication_SRCS testlibsyndication.cpp )

kde4_automoc(${testlibsyndication_SRCS})

kde4_add_executable(testlibsyndication ${testlibsyndication_SRCS})

target_link_libraries(testlibsyndication  syndication ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testloader_SRCS testloader.cpp )

kde4_automoc(${testloader_SRCS})

kde4_add_executable(testloader ${testloader_SRCS})

target_link_libraries(testloader  syndication ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testpersonimpl_SRCS testpersonimpl.cpp )

kde4_automoc(${testpersonimpl_SRCS})

kde4_add_executable(testpersonimpl RUN_UNINSTALLED ${testpersonimpl_SRCS})

target_link_libraries(testpersonimpl  syndication ${KDE4_KDECORE_LIBS} ${QT_QTTEST_LIBRARY} )

add_test(libsyndication-testpersonimpl ${EXECUTABLE_OUPUT_PATH}/testpersonimpl)

########### install files ###############

endif(KDE4_BUILD_TESTS)
