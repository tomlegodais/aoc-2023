#include "puzzle/day_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"
#include "session/session.hpp"
#include <fstream>
#include <gmock/gmock-nice-strict.h>
#include <nlohmann/json.hpp>

using testing::NiceMock;
using json = nlohmann::json;
using TestFunction = std::function<void(const std::vector<std::string> &, const std::vector<std::string> &, int, int, PuzzleService &)>;

template<int Day>
void test_day_puzzle(const std::vector<std::string> &input,
                     const std::vector<std::string> &alt_input,
                     const int expected_part_one,
                     const int expected_part_two,
                     PuzzleService &puzzle_service) {
    const int partOne = DayPuzzle<Day>::solve_part_one(puzzle_service, input);
    ASSERT_EQ(partOne, expected_part_one);

    const int partTwo = DayPuzzle<Day>::solve_part_two(puzzle_service, alt_input);
    ASSERT_EQ(partTwo, expected_part_two);
}

void populate_test_function_map(std::map<int, TestFunction> &) {}

template<int Day, int... Days>
void populate_test_function_map(std::map<int, TestFunction> &test_map) {
    test_map[Day + 1] = &test_day_puzzle<Day + 1>;
    if constexpr (sizeof...(Days) > 0) {
        populate_test_function_map<Days...>(test_map);
    }
}

template<int... Days>
std::map<int, TestFunction> map_test_functions(std::integer_sequence<int, Days...>) {
    std::map<int, TestFunction> test_map;
    populate_test_function_map<Days...>(test_map);
    return test_map;
}

class DayPuzzleTest : public testing::TestWithParam<std::tuple<int, std::vector<std::string>, std::vector<std::string>, int, int>> {
protected:
    static inline std::map<int, TestFunction> test_function_map = map_test_functions(std::make_integer_sequence<int, 7>{});

    Session session_mock_;
    NiceMock<PuzzleServiceMock> puzzle_service_mock_;

    DayPuzzleTest() : session_mock_(Session::from_value("dummy")),
                      puzzle_service_mock_(session_mock_) {}
};

TEST_P(DayPuzzleTest, SolvePuzzle) {
    auto [day, input, alt_input, expected_part_one, expected_part_two] = GetParam();
    if (const auto it = test_function_map.find(day); it != test_function_map.end()) {
        it->second(input, alt_input, expected_part_one, expected_part_two, puzzle_service_mock_);
    } else {
        FAIL() << "Test case for day " << day << " not implemented.";
    }
}

std::vector<std::tuple<int, std::vector<std::string>, std::vector<std::string>, int, int>> parse_json() {
    std::ifstream file("tests/data/sample_puzzle_data.json");
    json j;
    file >> j;

    std::vector<std::tuple<int, std::vector<std::string>, std::vector<std::string>, int, int>> test_cases;
    for (auto &item: j) {
        int day = item["day"];
        std::vector<std::string> input = item["input"];
        std::vector<std::string> alt_input = item.value("alt_input", input);
        int expected_part_one = item["expected_part_one"];
        int expected_part_two = item["expected_part_two"];

        test_cases.emplace_back(day, input, alt_input, expected_part_one, expected_part_two);
    }

    return test_cases;
}

INSTANTIATE_TEST_SUITE_P(
        DayPuzzles,
        DayPuzzleTest,
        testing::ValuesIn(parse_json()));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}