set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

remove_definitions( -DQT_NO_CAST_FROM_ASCII )
remove_definitions( -DQT_NO_CAST_TO_ASCII )
remove_definitions( -DQT_NO_CAST_FROM_BYTEARRAY )


include_directories(
    ${syndication_SOURCE_DIR}
    ${syndication_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
)

########### next target ###############

set(testlibsyndication_SRCS testlibsyndication.cpp)

add_executable(testlibsyndication ${testlibsyndication_SRCS})
add_test(testlibsyndication testlibsyndication)

target_link_libraries(testlibsyndication syndication ${KDE4_KDECORE_LIBS} ${QT_QTCORE_LIBRARY})

########### next target ###############

set(testloader_SRCS testloader.cpp)

# Qt5: Port
# kde4_add_executable(testloader ${testloader_SRCS})
# add_test(testloader testloader)
#
# target_link_libraries(testloader syndication ${KDE4_KDEUI_LIBS})

########### next target ###############

#set(testpersonimpl_SRCS testpersonimpl.cpp)
#add_test(testpersonimpl TESTNAME libsyndication-testpersonimpl  ${testpersonimpl_SRCS})
#target_link_libraries(testpersonimpl syndication ${QT_QTTEST_LIBRARY})

########### next target ###############

FILE(GLOB_RECURSE atomFiles atom/*xml)
FILE(GLOB_RECURSE rdfFiles rdf/*xml)
FILE(GLOB_RECURSE rss2Files rss2/*xml)

FOREACH( file ${atomFiles} )
  ADD_TEST( \"Atom-${file}\" ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
ENDFOREACH(file)
FOREACH( file ${rdfFiles} )
  ADD_TEST( \"Rdf-${file}\" ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
ENDFOREACH(file)
FOREACH( file ${rss2Files} )
  ADD_TEST( \"Rss2-${file}\" ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
ENDFOREACH(file)

