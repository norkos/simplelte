file(GLOB SRCS *.cpp)

add_executable(testenb ControllerUT.cpp main.cpp)

target_link_libraries(testenb
    messages
    eNB
    libgmock
    libgtest
)

install(TARGETS testenb DESTINATION bin)