#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day03Puzzle final : public DayPuzzle {
public:
    explicit Day03Puzzle(const PuzzleService &puzzle_service) : DayPuzzle(puzzle_service) {}

    int solvePartOne(std::string &puzzle_input) override;

    int solvePartTwo(std::string &puzzle_input) override;

private:
    static bool isSymbol(char c);

    static bool isAdjacent(const std::vector<std::string> &schematic, int x, int y);

    static int findPartNumber(const std::vector<std::string> &schematic, int x, int y);

    [[maybe_unused]] static PuzzleRegistrar<3, Day03Puzzle> registrar_;
};
