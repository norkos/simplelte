ExternalProject_Get_Property(project_zmg install_dir)

add_executable (hwserver hwserver.cpp)
add_dependencies(hwserver project_zmg)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} ${install_dir}/lib/libzmq.so messages utils)