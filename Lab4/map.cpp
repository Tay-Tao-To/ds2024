// map.cpp
#include "map.h"
#include <sstream>

void map(const std::string& input, std::unordered_map<std::string, int>& wordCounts) {
    std::istringstream stream(input);
    std::string word;
    while (stream >> word) {
        ++wordCounts[word];
    }
}