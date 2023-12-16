#pragma once

#include "service/puzzle_service.hpp"
#include <boost/preprocessor/repetition/repeat.hpp>

template<int Day>
class DayPuzzle {
public:
    static constexpr int day = Day;

    static int solvePartOne(PuzzleService &, const std::vector<std::string> &) {
        static_assert(Day != day, "DayPuzzle::solvePartOne not implemented for this day.");
        return 0;
    }

    static const char *getTitle() {
        static_assert(Day != day, "DayPuzzle::getTitle not implemented for this day.");
        return "";
    }
};

#define DEFINE_DAY_PUZZLE(z, n, data)                                                      \
    template<>                                                                             \
    int DayPuzzle<n + 1>::solvePartOne(PuzzleService &, const std::vector<std::string> &); \
                                                                                           \
    template<>                                                                             \
    const char *DayPuzzle<n + 1>::getTitle();

BOOST_PP_REPEAT(4, DEFINE_DAY_PUZZLE, ~)