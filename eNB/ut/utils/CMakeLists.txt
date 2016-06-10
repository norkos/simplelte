file(GLOB SRCS *.cpp)

add_executable(testutils ${SRCS})

target_link_libraries(testutils
    utils
    libgmock
    libgtest
)

install(TARGETS testutils DESTINATION bin)