cmake_minimum_required(VERSION 3.10)
project(lab_3)

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

set(SOURCES
    src/figures.cpp
    src/point.cpp
    src/vector.tpp
)


add_executable(lab3_exe main.cpp ${SOURCES})

enable_testing()

add_executable(test3 test/tests.cpp ${SOURCES})
target_link_libraries(test3 gtest_main)

add_test(NAME lab3_test COMMAND test3)