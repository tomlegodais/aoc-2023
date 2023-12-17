#include "puzzle/day_puzzle.hpp"
#include <iostream>

template<>
int DayPuzzle<2>::solvePartOne(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    return 1;
}

template<>
int DayPuzzle<2>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    return 2;
}

template<>
const char *DayPuzzle<2>::getTitle() {
    return "Cube Conundrum";
}