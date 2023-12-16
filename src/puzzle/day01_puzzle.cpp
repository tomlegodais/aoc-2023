#include "puzzle/day_puzzle.hpp"
#include <iostream>

template<>
int DayPuzzle<1>::solvePartOne(PuzzleService &puzzle_service, const std::vector<std::string> &puzzle_input) {
    std::cout << "Hello from day 1 part 1." << std::endl;
    return 1;
}

template<>
const char *DayPuzzle<1>::getTitle() {
    return "Trebuchet?!";
}