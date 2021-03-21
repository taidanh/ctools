#ifndef __BV_H__
#define __BV_H__

#include <stdint.h>

#define BV_TYPE uint8_t

typedef struct BitVector BitVector;

BitVector *bv_create(uint32_t length);

void bv_delete(BitVector **bv);

uint32_t bv_length(BitVector *bv);

void bv_set_bit(BitVector *bv, uint32_t i);

void bv_clr_bit(BitVector *bv, uint32_t i);

BV_TYPE bv_get_bit(BitVector *bv, uint32_t i);

void bv_print(BitVector *bv);

#endif
