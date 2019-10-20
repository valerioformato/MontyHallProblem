project(MontyHall)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES 
    src/main.cpp
    src/Host.cpp
    src/Player.cpp
)

add_executable(MontyHall ${SOURCES})