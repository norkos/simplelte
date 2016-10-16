add_library (eNB SHARED Controller.cpp UeManager.cpp Timer.cpp)
target_link_libraries (eNB messages utils) 
# remove zmq

add_library (server SHARED ZMQCommunicationFactory.cpp ZMQServer.cpp ZMQClient.cpp)
target_link_libraries (server messages zmq)

add_library (communication SHARED Listener.cpp)
target_link_libraries (communication messages server)

add_executable (hwserver main.cpp)

target_link_libraries(hwserver ${PROTOBUF_LIBRARY} communication eNB)
