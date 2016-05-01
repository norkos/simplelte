include_directories(${CMAKE_BINARY_DIR}/messages)
add_library (eNB SHARED main.cpp)
target_link_libraries (eNB messages)

add_subdirectory (server_client)
