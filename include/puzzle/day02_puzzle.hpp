#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day02Puzzle final : public DayPuzzle {
public:
    explicit Day02Puzzle(const PuzzleService &puzzle_service) : DayPuzzle(puzzle_service) {}

    int solvePartOne(std::string &puzzle_input) override;

    int solvePartTwo(std::string &puzzle_input) override;

private:
    static std::vector<std::string> parseGroups(const std::string &line);

    static std::map<std::string, int> countColors(const std::string &group);

    static bool isGroupValid(const std::string &group);

    static std::vector<int> getHighestValues(const std::map<std::string, std::vector<int>> &total_counts);

    [[maybe_unused]] static PuzzleRegistrar<2, Day02Puzzle> registrar_;
};
