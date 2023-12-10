#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "puzzle/day01_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"

using ::testing::NiceMock;

class Day01PuzzleTest : public ::testing::Test {
protected:
    Session dummySession;
    NiceMock<PuzzleServiceMock> puzzleServiceMock;

    Day01PuzzleTest() : dummySession(Session::fromValue("dummy")),
                        puzzleServiceMock(dummySession) {};
};

TEST_F(Day01PuzzleTest, SolvePartOne) {
    Day01Puzzle puzzle(puzzleServiceMock);
    std::string puzzleInput = "1abc2\n"
                              "pqr3stu8vwx\n"
                              "a1b2c3d4e5f\n"
                              "treb7uchet";
    EXPECT_EQ(142, puzzle.solvePartOne(puzzleInput));
}

TEST_F(Day01PuzzleTest, SolvePartTwo) {
    Day01Puzzle puzzle(puzzleServiceMock);
    std::string puzzleInput = "two1nine\n"
                              "eightwothree\n"
                              "abcone2threexyz\n"
                              "xtwone3four\n"
                              "4nineeightseven2\n"
                              "zoneight234\n"
                              "7pqrstsixteen";
    EXPECT_EQ(285, puzzle.solvePartTwo(puzzleInput));

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}