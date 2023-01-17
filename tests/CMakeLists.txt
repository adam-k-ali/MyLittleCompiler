project(tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Include the test_res directory
SET(TEST_RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_res)

include_directories(${TEST_RES_DIR})

FILE(GLOB TEST_RES_FILES ${TEST_RES_DIR}/*)

# Print TEST_RES_FILES
MESSAGE(STATUS "TEST_RES_FILES: ${TEST_RES_FILES}")

add_executable(runUnitTests tests.cpp ${SOURCE_FILES} ${INCLUDE_FILES} ${TEST_RES_FILES})
target_link_libraries(runUnitTests gtest gtest_main)