set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include(ECMMarkAsTest)

find_package(Qt5Test CONFIG REQUIRED)

########### next target ###############

set(testlibsyndication_SRCS testlibsyndication.cpp)

add_executable(testlibsyndication ${testlibsyndication_SRCS})
target_link_libraries(testlibsyndication KF5Syndication)

########### next target ###############

FILE(GLOB_RECURSE atomFiles atom/*xml)
FILE(GLOB_RECURSE rdfFiles rdf/*xml)
FILE(GLOB_RECURSE rss2Files rss2/*xml)

foreach( file ${atomFiles} )
  add_test( \"Atom-${file}\" ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
  ecm_mark_as_test(Atom-${file})
endforeach()
foreach( file ${rdfFiles} )
  add_test( \"Rdf-${file}\" ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
  ecm_mark_as_test(Rdf-${file})
endforeach()
foreach( file ${rss2Files} )
  add_test( \"Rss2-${file}\" ${EXECUTABLE_OUTPUT_PATH}/testlibsyndication ${file} --compare ${file}.expected )
  ecm_mark_as_test(Rss2-${file})
endforeach()

########### next target ###############

set(testloader_SRCS testloader.cpp)
add_executable(testloader ${testloader_SRCS})
add_test(testloader testloader)
target_link_libraries(testloader KF5Syndication KF5::CoreAddons Qt5::Widgets KF5::I18n)

########### next target ###############

add_executable(testpersonimpl testpersonimpl.cpp)
add_test(testpersonimpl testpersonimpl)
ecm_mark_as_test(testpersonimpl)
target_link_libraries(testpersonimpl KF5Syndication Qt5::Test)
