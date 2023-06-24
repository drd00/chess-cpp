cmake_minimum_required(VERSION 3.20)
project(chess)

set(CMAKE_CXX_STANDARD  17)

set(SOURCE_FILES main.cpp)
add_executable(Chess_run ${SOURCE_FILES})

include_directories(Chess_lib)
add_subdirectory(Chess_lib)

target_link_libraries(Chess_run Chess_lib)

add_subdirectory(Google_tests)