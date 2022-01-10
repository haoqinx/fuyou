cmake_minimum_required(VERSION 3.10)
set(
    LIB_SRC
    Channel.cpp
    Epoll.cpp
    EventLoop.cpp
    Timer.cpp
    Util.cpp
    EventLoopThread.cpp
    Timer.cpp
    EventLoopThreadPool.cpp
    Server.cpp
    Httpdata.cpp
    Tcpconn.cpp
)

add_definitions(-std=c++11)
add_library(fuyou_net ${LIB_SRC})
target_link_libraries(fuyou_net fuyou_base pthread rt)
set_target_properties(fuyou_net PROPERTIES OUTPUT_NAME "fuyou_net")