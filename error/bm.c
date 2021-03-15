#include "bm.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    uint8_t **mat;
} BitMatrix;

uint32_t bytes(uint32_t bits) {
    // rounds bits to bytes
    if (bits % 8 == 0 && bits != 0) {
        return bits / 8;
    } else {
        return bits / 8 + 1;
    }
}

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    m->mat = (uint8_t **) calloc(rows, sizeof(uint8_t *));
    for (uint32_t r = 0; r < rows; r += 1) {
        // allocates byte num of cols not bits
        m->mat[r] = (uint8_t *) calloc(bytes(cols), sizeof(uint8_t));
    }
    if (m == NULL || m->mat == NULL) {
        return NULL;
    }
    return m;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_delete(BitMatrix **m) {
    uint32_t rows = (*m)->rows;
    for (uint32_t r = 0; r < rows; r += 1) {
        // free internal
        free((*m)->mat[r]);
    }
    free((*m)->mat);
    free(*m);
    *m = NULL;
    return;
}

void bm_set_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    // shifts 0x1 over to the place that needs to be set
    // and ors it with that bit in the bitmat
    m->mat[row][col / 8] |= ((uint8_t) 0x1 << col % 8);
    return;
}

void bm_clr_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    // shifts 0x1 over to the place that needs to be cleared,
    // nots the whole thing then ands it with the bitmat
    m->mat[row][col / 8] &= ~((uint8_t) 0x1 << col % 8);
    return;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    // corresponding bit & 1 gives needed bit
    return (m->mat[row][col / 8] >> col % 8) & 0x1;
}

void bm_print(BitMatrix *m) {
    // prints rows and bits of each col
    for (uint32_t r = 0; r < m->rows; r += 1) {
        for (uint32_t c = 0; c < m->cols; c += 1) {
            fprintf(stderr, "%d", bm_get_bit(m, r, c));
            if (c == m->cols - 1) {
                putc('\n', stderr);
            }
        }
    }
}
