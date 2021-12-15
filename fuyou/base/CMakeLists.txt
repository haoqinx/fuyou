cmake_minimum_required(VERSION 3.10)
set(
    LIB_SRC
    Logstream.cpp
    AsynLogging.cpp
    Thread.cpp
    FileUtil.cpp
)
add_definitions(-std=c++11)
add_library(fuyou_base ${LIB_SRC})
target_link_libraries(fuyou_base pthread rt)
set_target_properties(fuyou_base PROPERTIES OUTPUT_NAME "fuyou_base")
add_subdirectory(tests)