add_library (eNB SHARED Controller.cpp UeManager.cpp ResponseConversions.cpp)
target_link_libraries (eNB messages)

add_library (communication SHARED Sender.cpp Listener.cpp)
target_link_libraries (eNB messages zmq)

add_executable (hwserver main.cpp)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} communication messages utils eNB)
