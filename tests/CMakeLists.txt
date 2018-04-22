set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include(ECMMarkAsTest)

find_package(Qt5Test CONFIG REQUIRED)

########### next target ###############

set(testloader_SRCS testloader.cpp)
add_executable(testloader ${testloader_SRCS})
target_link_libraries(testloader KF5Syndication Qt5::Widgets Qt5::Network)

