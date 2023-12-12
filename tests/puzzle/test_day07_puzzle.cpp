#include "puzzle/day07_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::NiceMock;

class Day07PuzzleTest : public testing::Test {
protected:
    Session dummy_session_;
    NiceMock<PuzzleServiceMock> puzzle_service_mock_;
    std::string puzzle_input_;

    Day07PuzzleTest() : dummy_session_(Session::fromValue("dummy")),
                        puzzle_service_mock_(dummy_session_) {
        puzzle_input_ = "32T3K 765\n"
                        "T55J5 684\n"
                        "KK677 28\n"
                        "KTJJT 220\n"
                        "QQQJA 483";
    }
};

TEST_F(Day07PuzzleTest, SolvePartOne) {
    Day07Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(6440, puzzle.solvePartOne(puzzle_input_));
}

TEST_F(Day07PuzzleTest, SolvePartTwo) {
    Day07Puzzle puzzle(puzzle_service_mock_);
    EXPECT_EQ(5905, puzzle.solvePartTwo(puzzle_input_));
}
