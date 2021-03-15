#include "hamming.h"

#include "bm.h"
#include "nibble.h"

#include <stdint.h>
#include <stdio.h>

static int lookup[] = { -1, 4, 5, -1, 6, -1, -1, 3, 7, -1, -1, 2, -1, 1, 0, -1 };

static BitMatrix *generator = NULL;
static BitMatrix *parity = NULL;

ham_rc ham_init(void) {
    generator = bm_create(4, 8);
    if (generator == NULL) {
        return HAM_ERR;
    }
    // setting generator
    bm_set_bit(generator, 0, 0);
    bm_set_bit(generator, 1, 1);
    bm_set_bit(generator, 2, 2);
    bm_set_bit(generator, 3, 3);
    // makes a 4x4 of 1's
    for (int r = 0; r < 4; r += 1) {
        for (int c = 4; c <= 7; c += 1) {
            bm_set_bit(generator, r, c);
        }
    }
    // clr to match pattern
    bm_clr_bit(generator, 0, 4);
    bm_clr_bit(generator, 1, 5);
    bm_clr_bit(generator, 2, 6);
    bm_clr_bit(generator, 3, 7);
    parity = bm_create(8, 4);
    if (parity == NULL) {
        return HAM_ERR;
    }
    // setting H
    // same as G but switched
    for (int r = 0; r < 4; r += 1) {
        for (int c = 0; c < 4; c += 1) {
            bm_set_bit(parity, r, c);
        }
    }
    bm_clr_bit(parity, 0, 0);
    bm_clr_bit(parity, 1, 1);
    bm_clr_bit(parity, 2, 2);
    bm_clr_bit(parity, 3, 3);
    bm_set_bit(parity, 4, 0);
    bm_set_bit(parity, 5, 1);
    bm_set_bit(parity, 6, 2);
    bm_set_bit(parity, 7, 3);
    return HAM_OK;
}

void ham_destroy(void) {
    bm_delete(&generator);
    bm_delete(&parity);
    return;
}

ham_rc ham_encode(uint8_t data, uint8_t *code) {
    if (generator == NULL || parity == NULL || code == NULL) {
        return HAM_ERR;
    }
    uint8_t column_total = 0;
    // start from back col so it shifts properly
    for (uint8_t c = 8; c > 0; c -= 1) {
        column_total <<= 1;
        for (uint8_t r = 0; r < 4; r += 1) {
            // bit in code_vec * bit in G_col XORd together
            // all anded by 1 to make sure only reading LSB
            column_total ^= (1 & (data >> r & bm_get_bit(generator, r, c - 1)));
        }
    }
    // code will be full encoded byte
    *code = column_total;
    return HAM_OK;
}

ham_rc ham_decode(uint8_t code, uint8_t *data) {
    if (generator == NULL || parity == NULL || data == NULL) {
        return HAM_ERR;
    }
    uint8_t e = 0;
    uint8_t column_total = 0;
    // start from back col so it shifts properly
    for (uint8_t c = 4; c > 0; c -= 1) {
        column_total <<= 1;
        for (uint8_t r = 0; r < 8; r += 1) {
            // addition % 2 of corresponding bit in code w H
            column_total ^= (1 & ((code >> r) & bm_get_bit(parity, r, c - 1)));
        }
    }
    e = column_total;
    if (e != 0) {
        if (lookup[e] != -1) {
            // toggle bit that was wrong
            code ^= 1 << lookup[e];
            *data = low_nibble(code);
            return HAM_ERR_OK;
        } else {
            return HAM_ERR;
        }
    } else {
        *data = low_nibble(code);
        return HAM_OK;
    }
}
