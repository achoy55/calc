set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

list(REMOVE_ITEM SRC_FILES src/main.cpp)

add_executable(calc ${SRC_FILES} ${COMMON_INCLUDE})

add_library(${BINARY}_lib STATIC ${SRC_FILES})