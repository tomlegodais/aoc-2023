#include "puzzle/day07_puzzle.hpp"
#include <algorithm>
#include <ranges>
#include "puzzle/puzzle_registrar.hpp"
#include "util/string_utils.hpp"

struct Card
{
    std::string value_;
    int strength_;

    explicit Card(const char ch)
    {
        static const std::unordered_map<char, std::pair<std::string, int>> mapping = {
            {'A', {"Ace", 14}},
            {'K', {"King", 13}},
            {'Q', {"Queen", 12}},
            {'J', {"Jack", 11}},
            {'T', {"10", 10}},
        };

        if (const auto it = mapping.find(ch); it != mapping.end())
        {
            value_ = it->second.first;
            strength_ = it->second.second;
        } else
        {
            value_ = std::string(1, ch);
            strength_ = ch - '0';
        }
    }
};

struct Hand
{
    std::vector<Card> cards_;
    int bid_;

    explicit Hand(const std::string& str)
    {
        for (int i = 0; i < 5; i++)
        {
            cards_.emplace_back(str[i]);
        }
        bid_ = std::stoi(str.substr(6));
    }
};

enum class HandType
{
    FiveOfAKind,
    FourOfAKind,
    FullHouse,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard
};

class PokerHand : public Hand
{
    HandType type_;

    [[nodiscard]] HandType determineHandType() const
    {
        std::unordered_map<char, int> frequency;
        for (const auto& card: cards_)
        {
            frequency[card.value_[0]]++;
        }

        int pairs = 0, triplets = 0, quads = 0, quints = 0;
        for (const auto& val: frequency | std::views::values)
        {
            if (val == 2) pairs++;
            else if (val == 3) triplets++;
            else if (val == 4) quads++;
            else if (val == 5) quints++;
        }

        if (quints == 1) return HandType::FiveOfAKind;
        if (quads == 1) return HandType::FourOfAKind;
        if (triplets == 1 && pairs == 1) return HandType::FullHouse;
        if (triplets == 1) return HandType::ThreeOfAKind;
        if (pairs == 2) return HandType::TwoPair;
        if (pairs == 1) return HandType::OnePair;
        return HandType::HighCard;
    }

public:
    using Hand::Hand;

    explicit PokerHand(const std::string& str) : Hand(str)
    {
        type_ = this->determineHandType();
    }

    bool operator<(const PokerHand& other) const
    {
        if (type_ != other.type_)
            return type_ > other.type_;

        for (int i = 0; i < cards_.size(); ++i)
        {
            if (cards_[i].strength_ != other.cards_[i].strength_)
                return cards_[i].strength_ < other.cards_[i].strength_;
        }
        return false;
    }
};

int Day07Puzzle::solvePartOne(std::string& puzzleInput)
{
    std::vector<PokerHand> poker_hands;
    for (auto const& lines = StringUtils::splitOnNewline(puzzleInput); auto const& line: lines)
    {
        poker_hands.emplace_back(line);
    }

    std::sort(poker_hands.begin(), poker_hands.end());

    int total = 0;
    for (int i = 0; i < poker_hands.size(); ++i)
    {
        total += poker_hands[i].bid_ * (i + 1);
    }

    return total;
}

int Day07Puzzle::solvePartTwo(std::string& puzzleInput)
{
    return 0;
}


[[maybe_unused]] PuzzleRegistrar<7, Day07Puzzle> Day07Puzzle::registrar("Camel Cards");
