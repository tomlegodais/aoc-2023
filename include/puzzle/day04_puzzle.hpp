#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day04Puzzle final : public DayPuzzle {
public:
    explicit Day04Puzzle(const PuzzleService &puzzle_service) : DayPuzzle(puzzle_service) {}

    int solvePartOne(std::string &puzzle_input) override;

    int solvePartTwo(std::string &puzzle_input) override;

private:
    static std::pair<std::vector<int>, std::vector<int>> extractNumbers(const std::string &str);

    [[maybe_unused]] static PuzzleRegistrar<4, Day04Puzzle> registrar_;
};
