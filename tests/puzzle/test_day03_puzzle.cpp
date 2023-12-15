#include "puzzle/day03_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::NiceMock;

class Day03PuzzleTest : public testing::Test {
protected:
    Session dummy_session_;
    NiceMock<PuzzleServiceMock> puzzle_service_mock_;
    std::vector<std::string> puzzle_input_;

    Day03PuzzleTest() : dummy_session_(Session::fromValue("dummy")),
                        puzzle_service_mock_(dummy_session_) {
        puzzle_input_ = {
                "467..114..",
                "...*......",
                "..35..633.",
                "......#...",
                "617*......",
                ".....+.58.",
                "..592.....",
                "......755.",
                "...$.*....",
                ".664.598.."};
    }
};

TEST_F(Day03PuzzleTest, SolvePartOne) {
    Day03Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(4361, puzzle.solvePartOne(puzzle_input_));
}

TEST_F(Day03PuzzleTest, SolvePartTwo) {
    Day03Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(467835, puzzle.solvePartTwo(puzzle_input_));
}
