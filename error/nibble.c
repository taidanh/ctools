#include <stdint.h>

uint8_t low_nibble(uint8_t n) {
    return n & 0x0f;
}

uint8_t high_nibble(uint8_t n) {
    return (n & 0xf0) >> 4;
}

uint8_t pack_byte(uint8_t low, uint8_t high) {
    uint8_t upper = low_nibble(high);
    uint8_t lower = low_nibble(low);
    return (upper << 4) + lower;
}
