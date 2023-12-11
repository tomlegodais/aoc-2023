#include <algorithm>
#include "puzzle/day01_puzzle.hpp"
#include "util/string_utils.hpp"

int Day01Puzzle::solvePartOne(std::string& puzzleInput)
{
    const auto lines = StringUtils::splitOnNewline(puzzleInput);
    int sum = 0;

    for (const auto& line: lines)
    {
        int firstDigit = 0, lastDigit = 0;
        for (const auto& c: line)
        {
            if (std::isdigit(c))
            {
                if (firstDigit == 0) firstDigit = c - '0';
                lastDigit = c - '0';
            }
        }

        sum += firstDigit * 10 + lastDigit;
    }

    return sum;
}

int Day01Puzzle::solvePartTwo(std::string& puzzleInput)
{
    const auto lines = StringUtils::splitOnNewline(puzzleInput);
    const std::map<std::string, char> numberMapping = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    };

    int sum = 0;
    for (const auto& line: lines)
    {
        std::vector<std::pair<int, int>> indices;
        for (auto i = 0; i < line.length(); i++)
        {
            if (std::isalpha(line[i]))
            {
                for (const auto& [fst, snd]: numberMapping)
                {
                    if (const std::string& word = fst; line.substr(i, word.length()) == word)
                    {
                        indices.emplace_back(i, snd);
                        break;
                    }
                }
            } else if (std::isdigit(line[i]))
            {
                indices.emplace_back(i, line[i] - '0');
            }
        }

        std::ranges::sort(indices, [](const auto& lhs, const auto& rhs)
        {
            return lhs.first < rhs.first;
        });

        const int firstDigit = indices[0].second;
        const int lastDigit = indices[indices.size() - 1].second;

        sum += firstDigit * 10 + lastDigit;
    }

    return sum;
}

[[maybe_unused]] PuzzleRegistrar<1, Day01Puzzle> Day01Puzzle::registrar("Trebuchet?!");
