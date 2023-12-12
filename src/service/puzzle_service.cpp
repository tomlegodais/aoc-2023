#include "service/puzzle_service.hpp"
#include <cpr/cpr.h>

std::string PuzzleService::readPuzzleInput(const int day) {
    auto url = cpr::Url{"https://adventofcode.com/2023/day/" + std::to_string(day) + "/input"};
    auto cookies = cpr::Cookies{{"session", session_.getValue()}};
    auto response = Get(url, cookies);

    if (response.status_code != 200) {
        throw std::runtime_error("Unable to read puzzle input for day " + std::to_string(day) + "\n" +
                                 "Please check if your session value is correct.");
    }

    return response.text;
}
