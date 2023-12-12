#pragma once

#include <string>
#include <utility>

class Session {
    std::string value_;

    explicit Session(std::string value) : value_(std::move(value)) {}

public:
    ~Session() = default;

    static Session init(const std::string &file_name);

    static Session fromValue(const std::string &value) {
        return Session(value);
    }

    const std::string &getValue() {
        return value_;
    }
};
