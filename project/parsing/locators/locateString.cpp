#include "../Parser.hpp"

bool locateString(const std::vector<std::string>& vectorStr, std::string the_line) {
    std::vector<std::string>::const_iterator it;
    it = std::find(vectorStr.begin(), vectorStr.end(), the_line);

    if (it != vectorStr.end())
        return true;
    else
        return false;
}