#include "Util.h"

#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <string>

namespace {
    std::mt19937& rng() {
        static std::mt19937 engine(static_cast<unsigned>(std::time(nullptr)));
        return engine;
    }
}

namespace util {

    void seedRng() {
        rng().seed(static_cast<unsigned>(std::time(nullptr)));
    }

    int randomInt(int minInclusive, int maxInclusive) {
        if (maxInclusive < minInclusive) {
            return minInclusive;
        }
        std::uniform_int_distribution<int> dist(minInclusive, maxInclusive);
        return dist(rng());
    }

    bool rollChance(int percent) {
        return randomInt(1, 100) <= percent;
    }

    int clampInt(int value, int lo, int hi) {
        if (value < lo) return lo;
        if (value > hi) return hi;
        return value;
    }

    // Prompts the user until they enter an integer in [lo, hi].
    int promptIntInRange(const std::string& prompt, int lo, int hi) {
        while (true) {
            std::cout << prompt;
            std::string line;
            if (!std::getline(std::cin, line)) {
                std::cin.clear();
                continue;
            }

            try {
                size_t pos = 0;
                int value = std::stoi(line, &pos);
                if (pos == 0 || value < lo || value > hi) {
                    throw std::out_of_range("range");
                }
                return value;
            } catch (...) {
                std::cout << "  >> Invalid input. Please enter a number between "
                          << lo << " and " << hi << ".\n";
            }
        }
    }

    void pauseForEnter() {
        std::cout << "\n  (press Enter to continue) ";
        std::string discard;
        std::getline(std::cin, discard);
    }
}
