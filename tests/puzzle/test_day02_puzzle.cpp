#include "puzzle/day02_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::NiceMock;

class Day02PuzzleTest : public testing::Test {
protected:
    Session dummy_session_;
    NiceMock<PuzzleServiceMock> puzzle_service_mock_;
    std::string puzzle_input_;

    Day02PuzzleTest() : dummy_session_(Session::fromValue("dummy")),
                        puzzle_service_mock_(dummy_session_) {
        puzzle_input_ = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n"
                        "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n"
                        "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n"
                        "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n"
                        "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    }
};

TEST_F(Day02PuzzleTest, SolvePartOne) {
    Day02Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(8, puzzle.solvePartOne(puzzle_input_));
}

TEST_F(Day02PuzzleTest, SolvePartTwo) {
    Day02Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(2286, puzzle.solvePartTwo(puzzle_input_));
}