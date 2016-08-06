include_directories(${CMAKE_BINARY_DIR}/CP_Util/messages)
include_directories(${CMAKE_SOURCE_DIR}/CP_Util/messages)
include_directories(${CMAKE_SOURCE_DIR}/CP_Util/include)

include_directories(include)
add_subdirectory(src)
add_subdirectory(ut)