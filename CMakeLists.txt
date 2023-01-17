cmake_minimum_required(VERSION 3.24)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)

# Source files
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

FILE(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
FILE(GLOB INCLUDE_FILES ${INCLUDE_DIR}/*.h)
FILE(GLOB RESOURCE_FILES ${RESOURCE_DIR}/*)

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

# T_PLUS tests directory
add_subdirectory(googletest)
add_subdirectory(tests)
enable_testing()

#add_executable(Compiler ${SOURCE_FILES} ${INCLUDE_FILES} ${RESOURCE_FILES})