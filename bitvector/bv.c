#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct BitVector {
    uint32_t length;
    uint8_t *vector;
} BitVector;

BitVector *bv_create(uint32_t length) {
    // creates an empty vector size of length
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    v->length = length;
    v->vector = calloc(length / 8, sizeof(uint8_t));
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
    bv->vector[i / 8] |= 1 << (i % 8);
    return;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    // ANDs everything with 1 except specified bit
    bv->vector[i / 8] &= ~(1 << (i % 8));
    return;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    // ANDs the specified bit with 1 and returns that
    return (bv->vector[i / 8] >> i % 8) & 1;
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
