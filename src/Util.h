#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace util {
    void seedRng();
    int randomInt(int minInclusive, int maxInclusive);
    bool rollChance(int percent);
    int clampInt(int value, int lo, int hi);
    int promptIntInRange(const std::string& prompt, int lo, int hi);
    void pauseForEnter();
}

#endif
