cmake_minimum_required(VERSION 3.14)
project(my_dynamic_array_proj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    release-1.12.1
)

FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB SRC_FILES src/*.cpp src/*.h)
file(GLOB TEST_FILES tests/*.cpp)

add_library(my_dynamic_array_lib ${SRC_FILES})
target_include_directories(my_dynamic_array_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(run_tests ${TEST_FILES})
target_link_libraries(run_tests PRIVATE my_dynamic_array_lib gtest_main)
