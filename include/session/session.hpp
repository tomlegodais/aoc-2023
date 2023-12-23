#pragma once

#include <string>

class Session {
    std::string value_;

    explicit Session(std::string value) : value_(std::move(value)) {}

public:
    ~Session() = default;

    static Session init(const std::string &file_name);

    static Session from_value(const std::string &value) {
        return Session(value);
    }

    const std::string &get_value() {
        return value_;
    }
};
