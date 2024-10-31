cmake_minimum_required(VERSION 3.10)
project(lab_4)

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

include_directories(include)

add_executable(lab4_exe main.cpp)

enable_testing()

add_executable(test4 test/tests.cpp)
target_link_libraries(test4 gtest_main)

add_test(NAME lab4_test COMMAND test4)