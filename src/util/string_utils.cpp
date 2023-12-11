#include "util/string_utils.hpp"
#include <sstream>

std::vector<std::string> StringUtils::splitOnNewline(const std::string& str)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    for (std::string line; std::getline(iss, line);)
    {
        if (line.empty())
        {
            continue;
        }

        result.push_back(line);
    }
    return result;
}
