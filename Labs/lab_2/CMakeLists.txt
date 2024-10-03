cmake_minimum_required(VERSION 3.10)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(lab2_lib five.cpp)
add_executable(lab2_exe main.cpp)

target_link_libraries(lab2_exe PRIVATE lab2_lib)

enable_testing()

add_executable(test_2 test_2.cpp)
target_link_libraries(test_2 lab2_lib gtest_main)


add_test(NAME MyProjectTests COMMAND test_2)

