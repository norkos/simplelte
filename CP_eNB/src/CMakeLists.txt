add_library (eNB SHARED Controller.cpp UeManager.cpp Timer.cpp SIBService.cpp)
target_link_libraries (eNB messages utils zmq) 
# remove zmq

add_library (communication SHARED Sender.cpp Listener.cpp TCPServer.cpp)
target_link_libraries (communication messages zmq)

add_executable (hwserver main.cpp)
add_executable (hwserver2 TCPServer.cpp)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} communication eNB)
target_link_libraries(hwserver2 ${PROTOBUF_LIBRARY} communication eNB)
