// main.cpp
#include "map.h"
#include "reduce.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfile>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<std::string, int> wordCounts;

    while (std::getline(file, line)) {
        map(line, wordCounts);
    }

    file.close();

    reduce(wordCounts);

    // Output the word counts
    for (const auto &pair : wordCounts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}