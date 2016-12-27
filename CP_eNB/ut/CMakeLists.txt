file(GLOB SRCS *.cpp)

add_executable(testenb DeserializerUT.cpp ControllerUT.cpp main.cpp)

target_link_libraries(testenb
    messages
    eNB
    ${PROTOBUF_LIBRARY}
    libgmock
    libgtest
    communication #remove
)

install(TARGETS testenb DESTINATION bin)