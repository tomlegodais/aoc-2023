#include "puzzle/day_puzzle.hpp"
#include "service/puzzle_service.hpp"
#include "session/session.hpp"
#include "util/utils.hpp"
#include <iostream>

template<int Day>
void solvePuzzle(PuzzleService &puzzle_service) {
    auto puzzleInput = puzzle_service.readPuzzleInput(Day);

    const int partOne = DayPuzzle<Day>::solvePartOne(puzzle_service, puzzleInput);
    std::cout << "Part One: " << partOne << std::endl;
}

int main() {
    try {
        std::cout << "Advent of Code 2023" << std::endl;
        std::cout << "===================" << std::endl;

        // TODO: Implement a way to select a day

        auto session = Session::init(".session");
        auto puzzleService = PuzzleService(session);

        solvePuzzle<1>(puzzleService);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
