#ifndef STRONG_NUMBER_H
#define STRONG_NUMBER_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

bool is_strong_number(int32_t n);

int32_t find_strong_numbers_between(int32_t lower_bound, int32_t upper_bound, 
    int32_t* out_strong_numbers, size_t out_strong_numbers_size);

#endif