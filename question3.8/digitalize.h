#ifndef DIGITALIZE_H
#define DIGITALIZE_H

#include <stdint.h>
#include <stddef.h>

void digitalize(int32_t n, int32_t* out_digits, size_t size);

int32_t compute_num_of_digits(int32_t n);

#endif