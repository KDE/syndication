if(KDE4_BUILD_TESTS)

# Test apps should be in the bin dir so that add_test can locate them
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_SOURCE_DIR}/syndication/   )


########### next target ###############

set(testlibsyndication_SRCS testlibsyndication.cpp )

kde4_automoc(${testlibsyndication_SRCS})

kde4_add_executable(testlibsyndication NOGUI ${testlibsyndication_SRCS})

target_link_libraries(testlibsyndication  syndication ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testloader_SRCS testloader.cpp )

kde4_automoc(${testloader_SRCS})

kde4_add_executable(testloader NOGUI ${testloader_SRCS})

target_link_libraries(testloader  syndication ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testpersonimpl_SRCS testpersonimpl.cpp )

kde4_automoc(${testpersonimpl_SRCS})

kde4_add_executable(testpersonimpl NOGUI RUN_UNINSTALLED ${testpersonimpl_SRCS})

target_link_libraries(testpersonimpl  syndication ${KDE4_KDECORE_LIBS} ${QT_QTTEST_LIBRARY} )

add_test(libsyndication-testpersonimpl ${EXECUTABLE_OUPUT_PATH}/testpersonimpl)

########### next target ###############

FILE( GLOB_RECURSE atomFiles atom/*xml )
FILE( GLOB_RECURSE rdfFiles rdf/*xml )
FILE( GLOB_RECURSE rss2Files rss2/*xml )

FOREACH( file ${atomFiles} )
  ADD_TEST( Atom-${file} ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
ENDFOREACH(file)
FOREACH( file ${rdfFiles} )
  ADD_TEST( Rdf-${file} ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
ENDFOREACH(file)
FOREACH( file ${rss2Files} )
  ADD_TEST( Rss2-${file} ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
ENDFOREACH(file)

########### install files ###############

endif(KDE4_BUILD_TESTS)
