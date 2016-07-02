file(GLOB SRCS *.cpp)

add_executable(testutils MessageHandlerUT.cpp HandlerFunctionUT.cpp main.cpp)

target_link_libraries(testutils
    utils
    libgmock
    libgtest
)

install(TARGETS testutils DESTINATION bin)