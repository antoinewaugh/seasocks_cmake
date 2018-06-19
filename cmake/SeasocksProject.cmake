# Seasocks
include(cmake/DownloadProject.cmake)
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