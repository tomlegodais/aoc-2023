#include "puzzle/puzzle_registry.hpp"
#include "service/puzzle_service_mock.hpp"
#include "session/session.hpp"
#include <fstream>
#include <gmock/gmock-nice-strict.h>
#include <nlohmann/json.hpp>

using testing::NiceMock;
using json = nlohmann::json;

std::vector<std::tuple<int, std::vector<std::string>, std::vector<std::string>, int, int>> loadPuzzleData() {
    std::ifstream file("tests/data/sample_puzzle_data.json");
    json j;
    file >> j;

    std::vector<std::tuple<int, std::vector<std::string>, std::vector<std::string>, int, int>> test_cases;
    for (auto &item: j) {
        int day = item["day"];
        std::vector<std::string> input = item["input"];
        std::vector<std::string> _input = item.value("_input", input);
        int expected_part_one = item["expected_part_one"];
        int expected_part_two = item["expected_part_two"];

        test_cases.emplace_back(day, input, _input, expected_part_one, expected_part_two);
    }

    return test_cases;
}

class DayPuzzleTest : public testing::TestWithParam<std::tuple<int, std::vector<std::string>, std::vector<std::string>, int, int>> {
protected:
    Session session_mock_;
    NiceMock<PuzzleServiceMock> puzzle_service_mock_;

    DayPuzzleTest() : session_mock_(Session::fromValue("dummy")),
                      puzzle_service_mock_(session_mock_) {}
};

TEST_P(DayPuzzleTest, SolvePuzzle) {
    auto [day, puzzle_input, _puzzle_input, expected_part_one, expected_part_two] = GetParam();
    const auto puzzle = PuzzleRegistry::getInstance().createPuzzle(day, puzzle_service_mock_);

    EXPECT_EQ(expected_part_one, puzzle->solvePartOne(puzzle_input));
    EXPECT_EQ(expected_part_two, puzzle->solvePartTwo(_puzzle_input));
}

INSTANTIATE_TEST_SUITE_P(
        DayPuzzles,
        DayPuzzleTest,
        testing::ValuesIn(loadPuzzleData()));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}