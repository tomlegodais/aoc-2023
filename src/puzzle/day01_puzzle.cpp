#include "puzzle/day_puzzle.hpp"
#include <iostream>

template<>
int DayPuzzle<1>::solvePartOne(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    return 1;
}

template<>
int DayPuzzle<1>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    return 2;
}

template<>
const char *DayPuzzle<1>::getTitle() {
    return "Trebuchet?!";
}