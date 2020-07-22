project(haste)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -g -Wunused-variable")

if(NOT DEFINED RECKLESS_INCLUDE_PATH)
    set(RECKLESS_INCLUDE_PATH "/home/aarif/install/include")
endif(NOT DEFINED RECKLESS_INCLUDE_PATH)

message("=== RECKLESS_INCLUDE_PATH = ${RECKLESS_INCLUDE_PATH}")
include_directories(inc ${RECKLESS_INCLUDE_PATH})

add_executable(haste src/haste_writer.cpp)
target_link_libraries(haste reckless)

