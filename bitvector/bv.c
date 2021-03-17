#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

#define BV_BITS (sizeof(BV_TYPE) * 8)

typedef struct BitVector {
    uint32_t length;
    BV_TYPE *vector;
} BitVector;

BitVector *bv_create(uint32_t length) {
    // creates an empty vector size of length
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    v->length = length;
    v->vector = calloc(length / BV_BITS, sizeof(BV_TYPE));
    if (v->vector == NULL) {
        free(v);
        return NULL;
    }
    return v;
}

void bv_delete(BitVector **bv) {
    // frees the insides then moves out
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    // ORs specified bit with 1
    bv->vector[i / BV_BITS] |= 1 << (i % BV_BITS);
    return;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    // ANDs everything with 1 except specified bit
    bv->vector[i / BV_BITS] &= ~(1 << (i % BV_BITS));
    return;
}

BV_TYPE bv_get_bit(BitVector *bv, uint32_t i) {
    // ANDs the specified bit with 1 and returns that
    return (bv->vector[i / BV_BITS] >> i % BV_BITS) & 1;
}

void bv_print(BitVector *bv) {
    // loops through bit by bit and prints from git_bit
    for (uint32_t i = 0; i < bv->length; i += 1) {
        printf("%d", bv_get_bit(bv, i));
        if (i % 4 == 3) {
            putc(' ', stdout);
        }
    }
    putc('\n', stdout);
}
