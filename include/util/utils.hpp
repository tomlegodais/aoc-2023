#pragma once

#include <chrono>
#include <utility>

namespace utils {
    template<typename Func>
    std::pair<decltype(std::declval<Func>()()), long long> measureExecutionTime(Func func) {
        const auto start = std::chrono::high_resolution_clock::now();
        auto result = func();
        const auto stop = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        return std::make_pair(result, duration.count());
    }

    inline std::vector<std::string> splitOnNewline(const std::string &str) {
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
}// namespace utils