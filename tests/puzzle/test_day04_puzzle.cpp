#include "puzzle/day04_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::NiceMock;

class Day04PuzzleTest : public testing::Test {
protected:
    Session dummy_session_;
    NiceMock<PuzzleServiceMock> puzzle_service_mock_;
    std::vector<std::string> puzzle_input_;

    Day04PuzzleTest() : dummy_session_(Session::fromValue("dummy")),
                        puzzle_service_mock_(dummy_session_) {
        puzzle_input_ = {
                "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53",
                "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19",
                "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1",
                "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83",
                "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36",
                "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11"};
    }
};

TEST_F(Day04PuzzleTest, SolvePartOne) {
    Day04Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(13, puzzle.solvePartOne(puzzle_input_));
}

TEST_F(Day04PuzzleTest, SolvePartTwo) {
    Day04Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(30, puzzle.solvePartTwo(puzzle_input_));
}
