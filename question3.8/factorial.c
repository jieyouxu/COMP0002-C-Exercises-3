#include <stdint.h>

#include "factorial.h"

int32_t factorial(int32_t n) {
    if (n < 0) {
        return -1;
    }

    if (n == 0) {
        return 1;
    }

    int32_t product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
    }

    return product;
}