cmake_minimum_required(VERSION 3.9)
project(seasocks_cmake)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

# Seasocks
include(DownloadProject.cmake)
download_project(PROJ seasocks
        GIT_REPOSITORY https://github.com/mattgodbolt/seasocks.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
option(DEFLATE_SUPPORT "Include support for deflate (requires zlib)." ON)
if (DEFLATE_SUPPORT)
    set(DEFLATE_SUPPORT_BOOL "true")
else ()
    set(DEFLATE_SUPPORT_BOOL "false")
endif ()

configure_file(${seasocks_SOURCE_DIR}/cmake/Config.h.in internal/Config.h)
add_subdirectory(${seasocks_SOURCE_DIR} ${seasocks_BINARY_DIR})
add_executable(seasocks_cmake main.cpp)
add_dependencies(seasocks_cmake seasocks_so)
target_link_libraries(seasocks_cmake seasocks_so ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(TARGET seasocks_cmake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/web ${CMAKE_BINARY_DIR}/web)

