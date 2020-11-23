set(BINARY ${CMAKE_PROJECT_NAME})

#set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

list(REMOVE_ITEM SRC_FILES src/main.cpp)

add_executable(calc main.cpp ${SRC_FILES} ${COMMON_INCLUDE})

add_library(${BINARY}_lib STATIC ${SRC_FILES})