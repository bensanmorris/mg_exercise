cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME mg_graph)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(
    ${PROJECT_NAME}_test
    test.cpp
    graph.h
)
target_link_libraries(
    ${PROJECT_NAME}_test
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)

# benchmark
set(BENCHMARK_ENABLE_TESTING FALSE)
include(FetchContent)
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark
    GIT_TAG        main
)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(${PROJECT_NAME}_benchmark benchmark.cpp)
target_link_libraries(${PROJECT_NAME}_benchmark benchmark::benchmark)
