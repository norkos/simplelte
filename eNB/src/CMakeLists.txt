include_directories(${CMAKE_BINARY_DIR}/messages)
add_executable (eNB main.cpp)
target_link_libraries (eNB messages)
