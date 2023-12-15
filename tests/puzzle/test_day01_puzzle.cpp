#include "puzzle/day01_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::NiceMock;

class Day01PuzzleTest : public testing::Test {
protected:
    Session dummy_session_;
    NiceMock<PuzzleServiceMock> puzzle_service_mock_;

    Day01PuzzleTest() : dummy_session_(Session::fromValue("dummy")),
                        puzzle_service_mock_(dummy_session_) {}
};

TEST_F(Day01PuzzleTest, SolvePartOne) {
    Day01Puzzle puzzle(puzzle_service_mock_);
    std::vector<std::string> puzzle_input = {"1abc2",
                                             "pqr3stu8vwx",
                                             "a1b2c3d4e5f",
                                             "treb7uchet"};
    EXPECT_EQ(142, puzzle.solvePartOne(puzzle_input));
}

TEST_F(Day01PuzzleTest, SolvePartTwo) {
    Day01Puzzle puzzle(puzzle_service_mock_);
    std::vector<std::string> puzzle_input = {"two1nine",
                                             "eightwothree",
                                             "abcone2threexyz",
                                             "xtwone3four",
                                             "4nineeightseven2",
                                             "zoneight234",
                                             "7pqrstsixteen"};
    EXPECT_EQ(281, puzzle.solvePartTwo(puzzle_input));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
