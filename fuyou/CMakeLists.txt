cmake_minimum_required(VERSION 3.10)
set(SRCS
    Main.cpp
)
include_directories(${PROJECT_SOURCE_DIR}/base)
include_directories(${PROJECT_SOURCE_DIR}/net)
include_directories(${PROJECT_SOURCE_DIR}/tests)

add_executable(servertest ${SRCS})
target_link_libraries(servertest fuyou_net)
add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(tests)