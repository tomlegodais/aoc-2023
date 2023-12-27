#include "puzzle/day_puzzle.hpp"
#include "service/puzzle_service_mock.hpp"
#include "session/session.hpp"
#include <fstream>
#include <gmock/gmock-nice-strict.h>
#include <nlohmann/json.hpp>

#define PUZZLE_SIZE 9

using testing::NiceMock;
using json = nlohmann::json;
using TestFunction = std::function<void(const std::vector<std::string> &, const std::vector<std::string> &, PuzzleResult, PuzzleResult, PuzzleService &)>;

void assert_puzzle_result(const PuzzleResult &result, const PuzzleResult &expected) {
    if (std::holds_alternative<int>(expected) && std::holds_alternative<int>(result)) {
        ASSERT_EQ(std::get<int>(result), std::get<int>(expected));
    } else if (std::holds_alternative<long long>(expected) && std::holds_alternative<long long>(result)) {
        ASSERT_EQ(std::get<long long>(result), std::get<long long>(expected));
    } else {
        FAIL() << "Expected result type does not match actual result type.";
    }
}

template<int Day>
void test_day_puzzle(const std::vector<std::string> &input,
                     const std::vector<std::string> &alt_input,
                     const PuzzleResult expected_part_one,
                     const PuzzleResult expected_part_two,
                     PuzzleService &puzzle_service) {
    DayPuzzle<Day> day_puzzle;

    const PuzzleResult part_one = day_puzzle.solve_part_one(puzzle_service, input);
    const PuzzleResult part_two = day_puzzle.solve_part_two(puzzle_service, alt_input);

    assert_puzzle_result(part_one, expected_part_one);
    assert_puzzle_result(part_two, expected_part_two);
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

class DayPuzzleTest : public testing::TestWithParam<std::tuple<int, std::vector<std::string>, std::vector<std::string>, PuzzleResult, PuzzleResult>> {
protected:
    static inline std::map<int, TestFunction> test_function_map = map_test_functions(std::make_integer_sequence<int, PUZZLE_SIZE>{});

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

std::vector<std::tuple<int, std::vector<std::string>, std::vector<std::string>, PuzzleResult, PuzzleResult>> parse_json() {
    std::map<std::string, std::function<PuzzleResult(const json &)>> conversion_map;
    conversion_map["int"] = [](const json &j) { return j.get<int>(); };
    conversion_map["long long"] = [](const json &j) { return j.get<long long>(); };

    std::ifstream file("tests/data/sample_puzzle_data.json");
    json j;
    file >> j;

    std::vector<std::tuple<int, std::vector<std::string>, std::vector<std::string>, PuzzleResult, PuzzleResult>> test_cases;
    for (auto &item: j) {
        int day = item["day"];
        std::vector<std::string> input = item["input"];
        std::vector<std::string> alt_input = item.value("alt_input", input);
        std::string expected_part_one_type = item.value("expected_part_one_type", "int"),
                    expected_part_two_type = item.value("expected_part_two_type", "int");

        PuzzleResult expected_part_one = conversion_map[expected_part_one_type](item["expected_part_one"]),
                     expected_part_two = conversion_map[expected_part_two_type](item["expected_part_two"]);

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