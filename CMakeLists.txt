cmake_minimum_required(VERSION 3.14)
project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)


add_executable(Lab4 main.cpp)


find_package(GTest QUIET)

if(GTest_FOUND)
    add_executable(Lab4Tests tests.cpp)
    target_link_libraries(Lab4Tests GTest::gtest GTest::gtest_main)

    enable_testing()
    add_test(NAME AllTests COMMAND Lab4Tests)

else()
    message(WARNING "GoogleTest не найден — тесты пропущены")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()