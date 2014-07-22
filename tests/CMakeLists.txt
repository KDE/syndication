set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include(ECMMarkAsTest)

find_package(Qt5Test CONFIG REQUIRED)

########### next target ###############

set(testlibsyndication_SRCS testlibsyndication.cpp)

add_executable(testlibsyndication ${testlibsyndication_SRCS})
add_test(testlibsyndication testlibsyndication)
target_link_libraries(testlibsyndication KF5Syndication)

########### next target ###############

set(testloader_SRCS testloader.cpp)
add_executable(testloader ${testloader_SRCS})
add_test(testloader testloader)
target_link_libraries(testloader KF5Syndication KF5::CoreAddons Qt5::Widgets KF5::I18n)

