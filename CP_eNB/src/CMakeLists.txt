add_library (eNB SHARED Controller.cpp UeManager.cpp Timer.cpp SIBService.cpp)
target_link_libraries (eNB messages utils)

add_library (communication SHARED Sender.cpp Listener.cpp)
target_link_libraries (communication messages zmq)

add_executable (hwserver main.cpp)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} communication eNB)
