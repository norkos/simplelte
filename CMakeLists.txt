cmake_minimum_required (VERSION 2.8)
project (SimpleLTE)
include(ExternalProject)

include_directories(externals/cppzmq)
include_directories(externals/libzmq/include)

ExternalProject_Add(project_zmg
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ../externals/libzmq

    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/project_zmg
    INSTALL_DIR ${CMAKE_BINARY_DIR}/install
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)

add_subdirectory (eNB)
add_subdirectory (messages)
