cmake_minimum_required(VERSION 3.10)
set(SRCS
    client_01.cpp
)

add_definitions(-std=c++11)
add_executable(client_01 ${SRCS})
target_link_libraries(client_01 pthread rt)