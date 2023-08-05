#ifndef UTIL_BCD_H
#define UTIL_BCD_H

#include <stddef.h>
#include <stdint.h>

namespace Util {
/**
 * @brief Convert a BCD number to binary integer
 */
template<typename T = size_t>
constexpr static inline T BcdToBin(T bcd) {
    size_t digit{};
    T decimalMultiplier = 1;
    T i{0};
    while(bcd > 0) {
        digit = bcd & 0xF;
        i += digit * decimalMultiplier;
        decimalMultiplier *= 10;
        bcd >>= 4;
    }
    return i;
}

/**
 * @brief Convert a binary number to BCD
 */
template<typename T = size_t>
constexpr static inline T BinToBcd(T i) {
    size_t digit{};
    T binaryShift{0};
    T bcd{0};
    while(i > 0) {
        digit = i % 10;
        bcd += (digit << binaryShift);
        binaryShift += 4;
        i /= 10;
    }
    return bcd;
}
}

#endif
