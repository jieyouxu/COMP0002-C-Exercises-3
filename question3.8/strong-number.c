#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "strong-number.h"
#include "digitalize.h"
#include "factorial.h"

#define SIZE 80

static int32_t digits[SIZE];

bool is_strong_number(int32_t n) {
    if (n < 0) {
        return false;
    }

    int32_t sumOfFactorials = 0;
    int32_t numOfDigits = compute_num_of_digits(n);
    digitalize(n, digits, numOfDigits);
    for (int32_t i = 0; i < numOfDigits; i++) {
        sumOfFactorials += factorial(digits[i]);
    }

    if (sumOfFactorials == n) {
        return true;
    }

    return false;
}

int32_t find_strong_numbers_between(int32_t lower_bound, 
                                 int32_t upper_bound, 
                                 int32_t* out_strong_numbers,
                                 size_t out_strong_numbers_size) {
    if (!out_strong_numbers) {
        return 0;        
    }

    if (out_strong_numbers_size <= 0) {
        return 0;
    }

    if (lower_bound < 0 || upper_bound < 0) {
        out_strong_numbers[0] = -1;
        return 0;
    }

    if (lower_bound == 0 && upper_bound == 0) {
        out_strong_numbers[0] = -1;
        return 0;
    }

    if (lower_bound > upper_bound) {
        out_strong_numbers[0] = -1;
        return 0;
    }

    int32_t out_strong_numbers_index = 0;
    for (int32_t i = lower_bound; i <= upper_bound 
        && out_strong_numbers_index < out_strong_numbers_size; i++) {
        if (is_strong_number(i)) {
            out_strong_numbers[out_strong_numbers_index] = i;
            out_strong_numbers_index++;
        } else {
            continue;
        }
    }

    return out_strong_numbers_index;
}