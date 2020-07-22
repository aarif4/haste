project(haste)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -g -Wunused-variable")

add_subdirectory(lib/reckless)

include_directories(inc ${CMAKE_BINARY_DIR}/lib)

add_executable(haste src/haste_writer.cpp)
target_link_libraries(haste reckless)

