#include <stdint.h>
#include <stddef.h>
#include <math.h>

#include "digitalize.h"

int32_t compute_num_of_digits(int32_t n) {
    int32_t num_of_digits = 0;

    if (n == 0) {
        return 1;
    }

    for (int32_t i = 1; i < INT32_MAX; i *= 10) {
        if (n / i != 0) {
            num_of_digits++;
            continue;
        } else {
            break;
        }
    }
    return num_of_digits;
}

void digitalize(int32_t n, int32_t* out_digits, size_t size) {
    if (n < 0) {
        *(out_digits+0) = -1;
        return;
    }

    if (!out_digits) {
        return;
    }

    if (size <= 0) {
        *(out_digits+0) = -1;
        return;
    }

    int32_t n_digits = compute_num_of_digits(n);

    if (n_digits > size) {
        *(out_digits+0) = -1;
        return;
    }

    int32_t multiplier = 1;
    int32_t remainder = n;
    int32_t digit = 0;
    for (int32_t d = n_digits-1; d >= 0; d--) {
        multiplier = (int) pow(10, d);
        digit = remainder / multiplier;
        remainder = n % multiplier;
        *(out_digits+d) = digit;
    }
}