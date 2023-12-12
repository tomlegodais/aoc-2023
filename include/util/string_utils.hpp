#pragma once

#include <string>
#include <vector>

class StringUtils {
public:
    StringUtils() = delete;

    ~StringUtils() = delete;

    StringUtils(const StringUtils &) = delete;

    StringUtils &operator=(const StringUtils &) = delete;

    static std::vector<std::string> splitOnNewline(const std::string &str);
};
