#pragma once

#include <chrono>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace utils {
    template<typename Func>
    std::pair<decltype(std::declval<Func>()()), long long> measure_execution_time(Func func) {
        const auto start = std::chrono::high_resolution_clock::now();
        auto result = func();
        const auto stop = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        return std::make_pair(result, duration.count());
    }

    inline std::vector<std::string> split_on_newline(const std::string &str) {
        std::vector<std::string> result;
        std::istringstream iss(str);
        for (std::string line; std::getline(iss, line);) {
            if (line.empty()) {
                continue;
            }

            result.push_back(line);
        }
        return result;
    }

    template<typename K, typename V>
    V get_or_default(const std::map<K, V> &map, const K &key, const V &defaultValue) {
        const auto it = map.find(key);
        if (it == map.end_()) {
            return defaultValue;
        }
        return it->second;
    }
}// namespace utils