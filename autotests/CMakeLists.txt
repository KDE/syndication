set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include(ECMMarkAsTest)

find_package(Qt5Test CONFIG REQUIRED)

########### next target ###############

set(testlibsyndication_SRCS testlibsyndication.cpp)
add_executable(testlibsyndication ${testlibsyndication_SRCS})
target_link_libraries(testlibsyndication KF5Syndication)

FILE(GLOB_RECURSE atomFiles atom/*xml)
FILE(GLOB_RECURSE rdfFiles rdf/*xml)
FILE(GLOB_RECURSE rss2Files rss2/*xml)

macro(get_test_name filename outname)
  get_filename_component(_tmp "${filename}" NAME)
  set(${outname} "${_tmp}")
endmacro()

foreach( file ${atomFiles} )
  get_test_name("${file}" name)
  add_test( NAME  \"Atom-${name}\" COMMAND testlibsyndication ${file} --compare ${file}.expected )
  ecm_mark_as_test(Atom-${name})
endforeach()
foreach( file ${rdfFiles} )
  get_test_name("${file}" name)
  add_test( NAME \"Rdf-${name}\" COMMAND testlibsyndication ${file} --compare ${file}.expected )
  ecm_mark_as_test(Rdf-${name})
endforeach()
foreach( file ${rss2Files} )
  get_test_name("${file}" name)
  add_test( NAME \"Rss2-${name}\" COMMAND testlibsyndication ${file} --compare ${file}.expected )
  ecm_mark_as_test(Rss2-${name})
endforeach()

########### next target ###############

add_executable(testpersonimpl testpersonimpl.cpp)
add_test(NAME testpersonimpl COMMAND testpersonimpl)
ecm_mark_as_test(testpersonimpl)
target_link_libraries(testpersonimpl KF5Syndication Qt5::Test)
