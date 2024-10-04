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

add_library(lab2_lib src/five.cpp include/five.h)
target_include_directories(lab2_lib PUBLIC include)

add_executable(lab2_exe main.cpp include/five.h src/five.cpp)
target_link_libraries(lab2_exe PRIVATE lab2_lib)

enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests lab2_lib gtest_main)


add_test(NAME MyProjectTests COMMAND tests)

