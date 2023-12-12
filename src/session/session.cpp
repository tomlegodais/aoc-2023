#include "session/session.hpp"
#include <fstream>
#include <stdexcept>

Session Session::init(const std::string &file_name) {
    std::string session_value;
    if (std::ifstream file(file_name.c_str()); file.is_open()) {
        getline(file, session_value);
        file.close();
    } else {
        throw std::runtime_error("Unable to open session file in path: \"" + file_name + "\"\n" +
                                 "Please create a file named \"" + file_name + "\" and put your session value in it.");
    }

    if (session_value.empty()) {
        throw std::runtime_error(
                "Session value is empty, please put your session value in the file \"" + file_name + "\"");
    }

    return Session(session_value);
}
