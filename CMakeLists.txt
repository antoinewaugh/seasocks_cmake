cmake_minimum_required(VERSION 3.9)
project(seasocks_cmake)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

include(cmake/SeasocksProject.cmake)

add_executable(seasocks_cmake main.cpp)
add_dependencies(seasocks_cmake seasocks_so)
target_link_libraries(seasocks_cmake seasocks_so ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(TARGET seasocks_cmake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/web ${CMAKE_BINARY_DIR}/web)

