cmake_minimum_required(VERSION 3.16)

project(calc)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_STANDARD 17)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(./googletest)
