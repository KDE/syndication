set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/syndication/ ${Boost_INCLUDE_DIR} )


########### next target ###############

set(testlibsyndication_SRCS testlibsyndication.cpp )


kde4_add_executable(testlibsyndication TEST ${testlibsyndication_SRCS})

target_link_libraries(testlibsyndication  syndication ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testloader_SRCS testloader.cpp )


kde4_add_executable(testloader TEST ${testloader_SRCS})

target_link_libraries(testloader  syndication ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testpersonimpl_SRCS testpersonimpl.cpp )


kde4_add_unit_test(testpersonimpl TESTNAME libsyndication-testpersonimpl  ${testpersonimpl_SRCS})

target_link_libraries(testpersonimpl  syndication ${KDE4_KDECORE_LIBS} ${QT_QTTEST_LIBRARY} )

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

