cmake_minimum_required(VERSION 3.10)
set(SRCS
    threadpool.cpp
)
add_definitions(-std=c++11)

add_executable(threadpool ${SRCS})
target_link_libraries(threadpool pthread rt)


