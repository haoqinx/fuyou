cmake_minimum_required(VERSION 3.10)
set(SRCS
    Channel.cpp
    Epoll.cpp
    EventLoop.cpp
    Timer.cpp
    Util.cpp
    EventLoopThread.cpp
    Timer.cpp
    EventLoopThreadPool.cpp
    Main.cpp
)
include_directories(${PROJECT_SOURCE_DIR}/base)


add_executable(servertest ${SRCS})
target_link_libraries(servertest fuyou_base)


add_subdirectory(base)