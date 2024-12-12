cmake_minimum_required(VERSION 3.10)
project(lab_7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Add threading support
find_package(Threads REQUIRED)

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
    src/npc.cpp
    src/orc.cpp
    src/squirrel.cpp
    src/bear.cpp
    src/npcFactory.cpp
    src/fileObserver.cpp
    src/consoleObserver.cpp
    src/fightVisitor.cpp
    src/gameManager.cpp
    src/coroutineGameManager.cpp
)

add_executable(lab7_exe main.cpp ${SOURCES})
target_link_libraries(lab7_exe Threads::Threads)

add_executable(lab7_pro main_pro.cpp ${SOURCES})
target_link_libraries(lab7_pro Threads::Threads)

enable_testing()

add_executable(test7 test/tests.cpp ${SOURCES})
target_link_libraries(test7 gtest_main Threads::Threads)

add_test(NAME lab7_test COMMAND test7)