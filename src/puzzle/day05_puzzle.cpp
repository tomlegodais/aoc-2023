#include "puzzle/day_puzzle.hpp"
#include "util/utils.hpp"

#include <atomic>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>

using i64 = long long;
using MapNames = std::string[7];

struct MapSection {
    i64 source_start;
    i64 destination_start;
    i64 length;

    MapSection(const i64 source_start, const i64 destination_start, const i64 length)
        : source_start(source_start), destination_start(destination_start), length(length) {}
};

using SectionMap = std::vector<MapSection>;
using SectionsMapping = std::unordered_map<std::string, SectionMap>;
using SeedRange = std::vector<std::pair<i64, i64>>;

void displayProgressBar(const size_t current, const size_t total) {
    constexpr int bar_width = 70;
    const float progress = static_cast<float>(current) / total;

    std::cout << "[";
    const int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "] " << progress * 100.0 << "% (" << current << "/" << total <<  ")\r";
    std::cout.flush();
}

struct ProgressTracker {
    std::atomic<size_t> total_processed;
    size_t total_seeds;
    std::mutex display_mutex;

    explicit ProgressTracker(size_t total_seeds) : total_seeds(total_seeds) {}

    void updateProgress(const int processed) {
        total_processed += processed;
        std::lock_guard lock(display_mutex);
        displayProgressBar(total_processed, total_seeds);
    }
};

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

SectionsMapping parseAllSections(const std::vector<std::string> &input) {
    SectionsMapping sections_mapping;
    SectionMap *current_map = nullptr;

    for (const auto &line: input) {
        if (line.back() == ':') {
            const std::string &current_section = line;
            current_map = &sections_mapping[current_section];
        } else if (current_map) {
            std::istringstream iss(line);
            i64 destination_start, source_start;
            if (i64 length; iss >> destination_start >> source_start >> length) {
                current_map->emplace_back(source_start, destination_start, length - 1);
            }
        }
    }

    return sections_mapping;
}

i64 findValue(const SectionMap &map, const i64 id) {
    for (const auto &section: map) {
        if (id >= section.source_start && id <= section.source_start + section.length) {
            return section.destination_start + id - section.source_start;
        }
    }

    return id;
}

std::unordered_map<i64, i64> cache;
std::mutex cache_mutex;

i64 processSeed(const SectionsMapping &sections_mapping, const MapNames &map_names, i64 seed) {
    {
        std::lock_guard lock(cache_mutex);
        if (const auto it = cache.find(seed); it != cache.end()) {
            return it->second;
        }
    }

    for (const auto &map_name: map_names) {
        if (const auto it = sections_mapping.find(map_name); it != sections_mapping.end()) {
            seed = findValue(it->second, seed);
        }
    }

    {
        std::lock_guard lock(cache_mutex);
        cache[seed] = seed;
    }
    return seed;
}

i64 processSeedRange(const SectionsMapping &sections_mapping, const MapNames &map_names, const i64 seed_start, const i64 length, ProgressTracker &progress_tracker) {
    i64 min_location = -1;
    for (i64 i = 0; i < length; ++i) {
        const i64 seed = seed_start + i;
        if (const i64 location = processSeed(sections_mapping, map_names, seed); min_location == -1 || location < min_location) {
            min_location = location;
        }
        progress_tracker.updateProgress(1);
    }
    return min_location;
}

template<>
int DayPuzzle<5>::solvePartOne(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto seeds = parseSeeds(puzzle_input.front());
    const auto sections_mapping = parseAllSections(puzzle_input);
    const MapNames map_names = {"seed-to-soil map:", "soil-to-fertilizer map:", "fertilizer-to-water map:",
                                "water-to-light map:", "light-to-temperature map:", "temperature-to-humidity map:",
                                "humidity-to-location map:"};

    i64 min_location = -1;
    for (const auto &seed: seeds) {
        if (const i64 location = processSeed(sections_mapping, map_names, seed); min_location == -1 || location < min_location) {
            min_location = location;
        }
    }

    return static_cast<int>(min_location);
}

template<>
int DayPuzzle<5>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto seed_range = parseSeedRange(puzzle_input.front());
    const auto sections_mapping = parseAllSections(puzzle_input);
    const MapNames map_names = {"seed-to-soil map:", "soil-to-fertilizer map:", "fertilizer-to-water map:",
                                "water-to-light map:", "light-to-temperature map:", "temperature-to-humidity map:",
                                "humidity-to-location map:"};

    const size_t total_seeds = std::accumulate(seed_range.begin(), seed_range.end(), 0, [](i64 sum, const auto &range) {
        return sum + range.second;
    });

    ProgressTracker tracker(total_seeds);
    std::vector<std::future<i64>> futures;

    for (const auto &[seed_start, length]: seed_range) {
        futures.emplace_back(std::async(std::launch::async, [&sections_mapping, &map_names, seed_start, length, &tracker] {
            return processSeedRange(sections_mapping, map_names, seed_start, length, tracker);
        }));
    }

    i64 min_location = -1;
    for (auto &f: futures) {
        if (const i64 location = f.get(); min_location == -1 || location < min_location) {
            min_location = location;
        }
    }

    return static_cast<int>(min_location);
}

template<>
const char *DayPuzzle<5>::getTitle() {
    return "If You Give A Seed A Fertilizer";
}