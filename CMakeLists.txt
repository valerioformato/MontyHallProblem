project(MontyHall)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES )

add_subdirectory(src)

add_executable(MontyHall ${SOURCES})