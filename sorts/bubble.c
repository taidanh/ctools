#include "bubble.h"

#include "tools.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(uint32_t *A, uint32_t n) {
    bool swapped = true;

    while (swapped) {
        swapped = false;

        for (uint32_t i = 1; i < n; i += 1) {
            comp_add(1);
            if (my_compare(A[i], A[i - 1])) {
                move_add(3);
                my_swap(&A[i], &A[i - 1]);
                swapped = true;
            }
        }
        n -= 1;
    }
}
