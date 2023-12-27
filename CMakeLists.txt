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

file(COPY ${CMAKE_SOURCE_DIR}/tests/data/ DESTINATION ${CMAKE_BINARY_DIR}/tests/data/)
enable_testing()

find_package(GTest CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/tests)
include(GoogleTest)

add_executable(aoc_2023 main.cpp
        include/session/session.hpp src/session/session.cpp
        include/service/puzzle_service.hpp src/service/puzzle_service.cpp
        include/puzzle/day_puzzle.hpp
        src/puzzle/day01_puzzle.cpp src/puzzle/day02_puzzle.cpp
        src/puzzle/day03_puzzle.cpp src/puzzle/day04_puzzle.cpp
        src/puzzle/day05_puzzle.cpp src/puzzle/day06_puzzle.cpp
        src/puzzle/day07_puzzle.cpp src/puzzle/day08_puzzle.cpp
        src/puzzle/day09_puzzle.cpp
        include/util/utils.hpp)

add_executable(aoc_2023_test tests/puzzle/test_day_puzzle.cpp
        include/service/puzzle_service.hpp src/service/puzzle_service.cpp
        include/puzzle/day_puzzle.hpp
        tests/service/puzzle_service_mock.hpp
        src/puzzle/day01_puzzle.cpp src/puzzle/day02_puzzle.cpp
        src/puzzle/day03_puzzle.cpp src/puzzle/day04_puzzle.cpp
        src/puzzle/day05_puzzle.cpp src/puzzle/day06_puzzle.cpp
        src/puzzle/day07_puzzle.cpp src/puzzle/day08_puzzle.cpp
        src/puzzle/day09_puzzle.cpp)

target_link_libraries(aoc_2023 PRIVATE cpr::cpr)
target_link_libraries(aoc_2023_test PRIVATE
        cpr::cpr
        GTest::gtest GTest::gtest_main
        GTest::gmock GTest::gmock_main
        nlohmann_json::nlohmann_json)

gtest_discover_tests(aoc_2023_test)