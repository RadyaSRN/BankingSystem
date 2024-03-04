cmake_minimum_required(VERSION 3.14)
project(banking-system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(main_cpp_path ${CMAKE_SOURCE_DIR}/src/main.cpp)
set(main_test_path ${CMAKE_SOURCE_DIR}/tests/main.test.cpp)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/banking_system/*.cpp)

add_executable(banking-system ${main_cpp_path} ${SOURCES})
target_include_directories(banking-system PUBLIC ${CMAKE_SOURCE_DIR}/include)


include(GoogleTest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(run-all-tests ${main_test_path} ${SOURCES})
target_include_directories(run-all-tests PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(run-all-tests PUBLIC ${CMAKE_SOURCE_DIR}/tests/banking_system/*.cpp)
target_link_libraries(run-all-tests GTest::GTest GTest::Main)

add_test(
  NAME unit_tests
  COMMAND run-all-tests)

gtest_discover_tests(run-all-tests)
