#include "puzzle/day_puzzle.hpp"
#include "util/utils.hpp"
#include <functional>
#include <future>
#include <iostream>
#include <ranges>
#include <sstream>
#include <unordered_map>

using i64 = long long;
using MapNames = std::vector<std::string>;
using SeedRange = std::vector<std::pair<i64, i64>>;

std::vector<i64> parseSeeds(const std::string &line) {
    std::vector<i64> seeds;
    const auto str = line.substr(line.find("seeds: ") + 7);
    std::stringstream ss(str);
    i64 seed;
    while (ss >> seed) {
        seeds.push_back(seed);
    }
    return seeds;
}

SeedRange parseSeedRange(const std::string &line) {
    SeedRange seed_range;
    const auto str = line.substr(line.find("seeds: ") + 7);
    std::stringstream ss(str);
    i64 seed_start, length;
    while (ss >> seed_start >> length) {
        seed_range.emplace_back(seed_start, length);
    }
    return seed_range;
}

size_t calculateTotalSeeds(const SeedRange &seed_range) {
    size_t total = 0;
    for (const auto &length: seed_range | std::views::values) {
        total += static_cast<size_t>(length);
    }
    return total;
}

std::vector<SeedRange> splitSeedRange(const SeedRange &seed_range, const size_t split_size) {
    const size_t total_seeds = calculateTotalSeeds(seed_range);
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
    std::vector<std::pair<i64, i64>>::const_iterator current;
    std::vector<std::pair<i64, i64>>::const_iterator end;
    i64 current_seed;
    i64 range_end;
    size_t batch_size;
    std::unique_ptr<i64[]> batch_array;

public:
    explicit SeedGenerator(const SeedRange &seed_range, const size_t batch_size)
        : current(seed_range.begin()), end(seed_range.end()),
          current_seed(current->first), range_end(current->first + current->second),
          batch_size(batch_size), batch_array(std::make_unique<i64[]>(batch_size)) {}

    SeedGenerator(const SeedGenerator &) = delete;
    SeedGenerator &operator=(const SeedGenerator &) = delete;

    i64 *nextBatch(size_t &actual_batch_size) {
        actual_batch_size = 0;

        while (actual_batch_size < batch_size) {
            if (current == end) break;

            i64 remaining_in_range = range_end - current_seed;
            i64 space_in_batch = batch_size - actual_batch_size;
            const i64 seeds_to_add = std::min(remaining_in_range, space_in_batch);

            for (i64 i = 0; i < seeds_to_add; ++i) {
                batch_array[actual_batch_size++] = current_seed + i;
            }

            current_seed += seeds_to_add;
            if (current_seed >= range_end) {
                ++current;
                if (current != end) {
                    current_seed = current->first;
                    range_end = current_seed + current->second;
                }
            }
        }

        return actual_batch_size > 0 ? batch_array.get() : nullptr;
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
    void addInterval(i64 start, const i64 length, const i64 destination_start) {
        intervals_.emplace_back(start, start + length, destination_start - start);
    }

    void buildTree() {
        std::ranges::sort(intervals_, [](const Interval &a, const Interval &b) {
            return a.start < b.start;
        });
    }

    [[nodiscard]] i64 mapValue(const i64 value) const {
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

std::unordered_map<std::string, IntervalTree> parseIntervalTrees(const std::vector<std::string> &input) {
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
                interval_trees[current_map].addInterval(source_start, length, desination_start);
            }
        }
    }

    for (auto &tree: interval_trees | std::views::values) {
        tree.buildTree();
    }

    return interval_trees;
}

i64 processSeed(const std::unordered_map<std::string, IntervalTree> &interval_trees, const MapNames &map_names, i64 seed) {
    for (const auto &map_name: map_names) {
        seed = interval_trees.at(map_name).mapValue(seed);
    }
    return seed;
}

std::atomic<size_t> total_seeds_processed;

i64 processBatch(const SeedRange &seed_range, const std::unordered_map<std::string, IntervalTree> &interval_trees, const MapNames &map_names) {
    SeedGenerator seed_generator(seed_range, 5000);
    size_t actual_batch_size;
    i64 lowest_location = LLONG_MAX;

    while (true) {
        const i64 *seeds = seed_generator.nextBatch(actual_batch_size);
        if (actual_batch_size == 0) break;

        for (size_t i = 0; i < actual_batch_size; ++i) {
            const i64 seed = seeds[i];
            if (const i64 location = processSeed(interval_trees, map_names, seed); location < lowest_location) {
                lowest_location = location;
            }
            ++total_seeds_processed;
        }
    }
    return lowest_location;
}

template<>
int DayPuzzle<5>::solvePartOne(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto seeds = parseSeeds(puzzle_input.front());
    const auto interval_trees = parseIntervalTrees(puzzle_input);
    const MapNames map_names = {"seed-to-soil map", "soil-to-fertilizer map", "fertilizer-to-water map",
                                "water-to-light map", "light-to-temperature map", "temperature-to-humidity map",
                                "humidity-to-location map"};


    i64 lowest_location = LLONG_MAX;
    for (const auto &seed: seeds) {
        if (const i64 location = processSeed(interval_trees, map_names, seed); location < lowest_location) {
            lowest_location = location;
        }
    }

    return lowest_location;
}

template<>
int DayPuzzle<5>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto seed_range = parseSeedRange(puzzle_input.front());
    const unsigned int thread_count = std::thread::hardware_concurrency();
    const auto split_range = splitSeedRange(seed_range, thread_count);
    const auto interval_trees = parseIntervalTrees(puzzle_input);
    const MapNames map_names = {"seed-to-soil map", "soil-to-fertilizer map", "fertilizer-to-water map",
                                "water-to-light map", "light-to-temperature map", "temperature-to-humidity map",
                                "humidity-to-location map"};

    std::vector<std::future<i64>> futures;
    for (unsigned int i = 0; i < thread_count; ++i) {
        futures.push_back(std::async(std::launch::async, processBatch, split_range[i], interval_trees, map_names));
    }

    i64 lowest_location = LLONG_MAX;
    for (auto &f: futures) {
        if (const auto &location = f.get(); location < lowest_location) {
            lowest_location = location;
        }
    }

    std::cout << "Total seeds processed: " << total_seeds_processed << std::endl;
    return lowest_location;
}

template<>
const char *DayPuzzle<5>::getTitle() {
    return "If You Give A Seed A Fertilizer";
}