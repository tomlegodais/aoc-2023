#pragma once

#include "service/puzzle_service.hpp"
#include <boost/preprocessor/repetition/repeat.hpp>
#include <stdexcept>

template<int Day>
class DayPuzzle {
public:
    static int solvePartOne(PuzzleService &puzzle_service, const std::vector<std::string> &puzzle_input) {
        static_assert(Day != Day, "DayPuzzle::solvePartOne not implemented for this day.");
        return 0;
    }
};

#define DEFINE_DAY_PUZZLE(z, n, data) \
    template<>                        \
    int DayPuzzle<n + 1>::solvePartOne(PuzzleService &, const std::vector<std::string> &);

BOOST_PP_REPEAT(4, DEFINE_DAY_PUZZLE, ~)