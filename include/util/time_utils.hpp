#pragma once

#include <chrono>
#include <utility>

class TimeUtils {
public:
    TimeUtils() = delete;

    ~TimeUtils() = delete;

    TimeUtils(const TimeUtils &) = delete;

    TimeUtils &operator=(const TimeUtils &) = delete;

    template<typename Func>
    static std::pair<decltype(std::declval<Func>()()), long long> measureExecutionTime(Func func) {
        const auto start = std::chrono::high_resolution_clock::now();
        auto result = func();
        const auto stop = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        return std::make_pair(result, duration.count());
    }
};
