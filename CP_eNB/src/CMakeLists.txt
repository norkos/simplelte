add_library (eNB SHARED Controller.cpp UeManager.cpp)
target_link_libraries (eNB messages)
ExternalProject_Get_Property(libzmq install_dir)

add_executable (hwserver hwserver.cpp)
add_dependencies(hwserver libzmq)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} ${install_dir}/lib/libzmq.so messages utils eNB)
