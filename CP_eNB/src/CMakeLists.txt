add_library (eNB SHARED Controller.cpp UeManager.cpp)
target_link_libraries (eNB messages)

add_executable (hwserver hwserver.cpp)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} zmq messages utils eNB)
