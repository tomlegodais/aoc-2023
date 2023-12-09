cmake_minimum_required(VERSION 3.27)
project(aoc_2023)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(cpr CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(aoc_2023 main.cpp
        include/session/session.hpp src/session/session.cpp
        include/service/puzzle_service.hpp src/service/puzzle_service.cpp
        include/util/string_utils.hpp src/util/string_utils.cpp
        include/puzzle/day_puzzle.hpp include/puzzle/puzzle_registrar.hpp
        include/puzzle/puzzle_registry.hpp src/puzzle/puzzle_registry.cpp
        include/puzzle/day01_puzzle.hpp src/puzzle/day01_puzzle.cpp)

target_link_libraries(aoc_2023 PRIVATE cpr::cpr)