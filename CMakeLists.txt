cmake_minimum_required(VERSION 3.16)

project(calc)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_STANDARD 17)
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

list(REMOVE_ITEM SRC_FILES src/main.cpp)

set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(calc src/main.cpp tst/test_calc.cpp src/Expression.cpp include/Expression.h)

########################################
# Testing
########################################
#option(BUILD_TESTS "Build the tests" OFF)
#if (BUILD_TESTS)
#    add_subdirectory(./googletest)
#    enable_testing()
#    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#    file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tst/*.cpp)
#    add_executable(runUnitTests ${TEST_SRC_FILES})
#    target_link_libraries(runUnitTests gtest gtest_main)
#    add_test(UnitTests runUnitTests)
#endif ()