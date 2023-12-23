#include "puzzle/day_puzzle.hpp"
#include "util/utils.hpp"
#include <functional>
#include <future>
#include <iostream>
#include <ranges>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using i64 = long long;
using MapNames = std::vector<std::string>;
using SeedRange = std::vector<std::pair<i64, i64>>;

std::vector<i64> parse_seeds(const std::string &line) {
    std::vector<i64> seeds;
    const auto str = line.substr(line.find("seeds: ") + 7);
    std::stringstream ss(str);
    i64 seed;
    while (ss >> seed) {
        seeds.push_back(seed);
    }
    return seeds;
}

SeedRange parse_seed_range(const std::string &line) {
    SeedRange seed_range;
    const auto str = line.substr(line.find("seeds: ") + 7);
    std::stringstream ss(str);
    i64 seed_start, length;
    while (ss >> seed_start >> length) {
        seed_range.emplace_back(seed_start, length);
    }
    return seed_range;
}

size_t calculate_total_seeds(const SeedRange &seed_range) {
    size_t total = 0;
    for (const auto &length: seed_range | std::views::values) {
        total += static_cast<size_t>(length);
    }
    return total;
}

std::vector<SeedRange> split_seed_range(const SeedRange &seed_range, const size_t split_size) {
    const size_t total_seeds = calculate_total_seeds(seed_range);
    const size_t seeds_per_split = total_seeds / split_size;
    const size_t remainder = total_seeds % split_size;

    std::vector<SeedRange> split_ranges(split_size);
    auto it = seed_range.begin();

    i64 current_start = it->first;
    i64 seeds_allocated = 0;

    for (size_t i = 0; i < split_size && it != seed_range.end(); ++i) {
        size_t seeds_to_allocate = seeds_per_split + (i < remainder ? 1 : 0);
        split_ranges[i] = SeedRange();

        while (seeds_to_allocate > 0 && it != seed_range.end()) {
            i64 range_length = std::min<i64>(seeds_to_allocate, static_cast<i64>(it->second) - seeds_allocated);
            split_ranges[i].emplace_back(current_start, range_length);

            seeds_allocated += range_length;
            seeds_to_allocate -= range_length;
            current_start += range_length;

            if (seeds_allocated == it->second) {
                ++it;
                if (it != seed_range.end()) {
                    current_start = it->first;
                    seeds_allocated = 0;
                }
            }
        }
    }
    return split_ranges;
}

class SeedGenerator {
    std::vector<std::pair<i64, i64>>::const_iterator current_;
    std::vector<std::pair<i64, i64>>::const_iterator end_;
    i64 current_seed_;
    i64 range_end_;
    size_t batch_size_;
    std::unique_ptr<i64[]> batch_array_;

public:
    explicit SeedGenerator(const SeedRange &seed_range, const size_t batch_size)
        : current_(seed_range.begin()), end_(seed_range.end()),
          current_seed_(current_->first), range_end_(current_->first + current_->second),
          batch_size_(batch_size), batch_array_(std::make_unique<i64[]>(batch_size)) {}

    SeedGenerator(const SeedGenerator &) = delete;
    SeedGenerator &operator=(const SeedGenerator &) = delete;

    i64 *next_batch(size_t &actual_batch_size) {
        actual_batch_size = 0;

        while (actual_batch_size < batch_size_) {
            if (current_ == end_) break;

            i64 remaining_in_range = range_end_ - current_seed_;
            i64 space_in_batch = batch_size_ - actual_batch_size;
            const i64 seeds_to_add = std::min(remaining_in_range, space_in_batch);

            for (i64 i = 0; i < seeds_to_add; ++i) {
                batch_array_[actual_batch_size++] = current_seed_ + i;
            }

            current_seed_ += seeds_to_add;
            if (current_seed_ >= range_end_) {
                ++current_;
                if (current_ != end_) {
                    current_seed_ = current_->first;
                    range_end_ = current_seed_ + current_->second;
                }
            }
        }

        return actual_batch_size > 0 ? batch_array_.get() : nullptr;
    }
};

struct Interval {
    i64 start;
    i64 end;
    i64 offset;

    Interval(const i64 start, const i64 end, const i64 offset)
        : start(start), end(end), offset(offset) {}
};

class IntervalTree {
    std::vector<Interval> intervals_;

public:
    void add_interval(i64 start, const i64 length, const i64 destination_start) {
        intervals_.emplace_back(start, start + length, destination_start - start);
    }

    void build_tree() {
        std::ranges::sort(intervals_, [](const Interval &a, const Interval &b) {
            return a.start < b.start;
        });
    }

    [[nodiscard]] i64 map_value(const i64 value) const {
        int low = 0, high = intervals_.size() - 1;
        while (low <= high) {
            const int mid = low + (high - low) / 2;
            if (const auto &interval = intervals_[mid]; value >= interval.start && value < interval.end) {
                return value + interval.offset;
            } else if (value < interval.start) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return value;
    }
};

std::unordered_map<std::string, IntervalTree> parse_interval_trees(const std::vector<std::string> &input) {
    std::string current_map;
    std::unordered_map<std::string, IntervalTree> interval_trees;
    for (const auto &line: input) {
        if (line.back() == ':') {
            current_map = line.substr(0, line.size() - 1);
            interval_trees[current_map] = IntervalTree();
        } else {
            std::istringstream iss(line);
            i64 desination_start, source_start;
            if (i64 length; iss >> desination_start >> source_start >> length) {
                interval_trees[current_map].add_interval(source_start, length, desination_start);
            }
        }
    }

    for (auto &tree: interval_trees | std::views::values) {
        tree.build_tree();
    }

    return interval_trees;
}

i64 process_seed(const std::unordered_map<std::string, IntervalTree> &interval_trees, const MapNames &map_names, i64 seed) {
    for (const auto &map_name: map_names) {
        seed = interval_trees.at(map_name).map_value(seed);
    }
    return seed;
}

i64 process_batch(const SeedRange &seed_range, const std::unordered_map<std::string, IntervalTree> &interval_trees, const MapNames &map_names) {
    SeedGenerator seed_generator(seed_range, 5000);
    size_t actual_batch_size;
    i64 lowest_location = LLONG_MAX;

    while (true) {
        const i64 *seeds = seed_generator.next_batch(actual_batch_size);
        if (actual_batch_size == 0) break;

        for (size_t i = 0; i < actual_batch_size; ++i) {
            const i64 seed = seeds[i];
            if (const i64 location = process_seed(interval_trees, map_names, seed); location < lowest_location) {
                lowest_location = location;
            }
        }
    }
    return lowest_location;
}

template<>
int DayPuzzle<5>::solve_part_one(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto seeds = parse_seeds(puzzle_input.front());
    const auto interval_trees = parse_interval_trees(puzzle_input);
    const MapNames map_names = {"seed-to-soil map", "soil-to-fertilizer map", "fertilizer-to-water map",
                                "water-to-light map", "light-to-temperature map", "temperature-to-humidity map",
                                "humidity-to-location map"};


    i64 lowest_location = LLONG_MAX;
    for (const auto &seed: seeds) {
        if (const i64 location = process_seed(interval_trees, map_names, seed); location < lowest_location) {
            lowest_location = location;
        }
    }

    return lowest_location;
}

template<>
int DayPuzzle<5>::solve_part_two(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto seed_range = parse_seed_range(puzzle_input.front());
    const unsigned int thread_count = std::thread::hardware_concurrency();
    const auto split_range = split_seed_range(seed_range, thread_count);
    const auto interval_trees = parse_interval_trees(puzzle_input);
    const MapNames map_names = {"seed-to-soil map", "soil-to-fertilizer map", "fertilizer-to-water map",
                                "water-to-light map", "light-to-temperature map", "temperature-to-humidity map",
                                "humidity-to-location map"};

    std::vector<std::future<i64>> futures;
    for (unsigned int i = 0; i < thread_count; ++i) {
        futures.push_back(std::async(std::launch::async, process_batch, split_range[i], interval_trees, map_names));
    }

    i64 lowest_location = LLONG_MAX;
    for (auto &f: futures) {
        if (const auto &location = f.get(); location < lowest_location) {
            lowest_location = location;
        }
    }

    return lowest_location;
}

template<>
const char *DayPuzzle<5>::get_title() {
    return "If You Give A Seed A Fertilizer";
}