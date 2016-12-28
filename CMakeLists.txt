cmake_minimum_required (VERSION 2.8)
project (SimpleLTE CXX C)
include(ExternalProject)

find_package(Threads REQUIRED)
    
macro (add_my_external lib_name lib_path)
    ExternalProject_Add(
        ${lib_name}
        DOWNLOAD_COMMAND ""
        SOURCE_DIR ../externals/${lib_path}
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${lib_name}
        BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/${lib_name}/src/${lib_name}-build/lib${lib_name}.a
        INSTALL_COMMAND ""
    )
    
    add_library(lib${lib_name} IMPORTED STATIC GLOBAL)
    add_dependencies(lib${lib_name}  ${lib_name})
    ExternalProject_Get_Property( ${lib_name} source_dir binary_dir)
    set_target_properties(lib${lib_name} PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/lib${lib_name}.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )
    include_directories("${source_dir}/include")
endmacro (add_my_external)

add_my_external(gtest gtest-1.7.0)
add_my_external(gmock gmock-1.7.0)

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++1y -fPIC")

include_directories("externals/sml/include")

add_subdirectory(CP_eNB)
add_subdirectory(CP_Util)