#include "shell.h"

#include "gaps.h"
#include "tools.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t k = 0; k < GAPS; k += 1) {
        for (uint32_t i = gaps[k]; i < n; i += 1) {
            uint32_t j = i;
            uint32_t temp = A[i];
            while ((j >= gaps[k]) && comp_incr(temp, A[j - gaps[k]])) {
                // if a swap is found it checks backwards
                // by gap amount for more swaps
                my_swap(&A[j], &A[j - gaps[k]]);
                move_add(3);
                j -= gaps[k];
            }
            A[j] = temp;
        }
    }
    return;
}
