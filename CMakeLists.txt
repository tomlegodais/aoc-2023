set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

cmake_minimum_required(VERSION 3.27)
project(aoc_2023)
set(CMAKE_CXX_STANDARD 23)

foreach (CONFIG_TYPE IN LISTS CMAKE_CONFIGURATION_TYPES CMAKE_BUILD_TYPE)
    string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/lib)
endforeach ()

enable_testing()

find_package(GTest CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/tests)
include(GoogleTest)

add_executable(aoc_2023 main.cpp
        include/session/session.hpp src/session/session.cpp
        include/service/puzzle_service.hpp src/service/puzzle_service.cpp
        include/util/string_utils.hpp src/util/string_utils.cpp
        include/util/time_utils.hpp
        include/puzzle/day_puzzle.hpp include/puzzle/puzzle_registrar.hpp
        include/puzzle/puzzle_registry.hpp src/puzzle/puzzle_registry.cpp
        include/puzzle/day01_puzzle.hpp src/puzzle/day01_puzzle.cpp
        include/puzzle/day02_puzzle.hpp src/puzzle/day02_puzzle.cpp
        include/puzzle/day03_puzzle.hpp src/puzzle/day03_puzzle.cpp
        include/puzzle/day04_puzzle.hpp src/puzzle/day04_puzzle.cpp
        include/puzzle/day07_puzzle.hpp src/puzzle/day07_puzzle.cpp)
add_executable(aoc_2023_test
        tests/service/puzzle_service_mock.hpp
        tests/puzzle/test_day01_puzzle.cpp tests/puzzle/test_day02_puzzle.cpp
        tests/puzzle/test_day07_puzzle.cpp
        include/service/puzzle_service.hpp src/service/puzzle_service.cpp
        include/util/string_utils.hpp src/util/string_utils.cpp
        include/puzzle/day01_puzzle.hpp src/puzzle/day01_puzzle.cpp
        include/puzzle/day02_puzzle.hpp src/puzzle/day02_puzzle.cpp
        include/puzzle/day07_puzzle.hpp src/puzzle/day07_puzzle.cpp)

target_link_libraries(aoc_2023 PRIVATE cpr::cpr)
target_link_libraries(aoc_2023_test PRIVATE
        cpr::cpr
        GTest::gtest GTest::gtest_main
        GTest::gmock GTest::gmock_main)

gtest_discover_tests(aoc_2023_test)