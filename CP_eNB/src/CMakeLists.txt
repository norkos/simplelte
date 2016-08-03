add_library (eNB SHARED Controller.cpp UeManager.cpp)
target_link_libraries (eNB messages)

add_library (communication SHARED Sender.cpp)
target_link_libraries (eNB messages zmq)

add_executable (hwserver hwserver.cpp)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} communication messages utils eNB)
