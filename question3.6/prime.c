#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool isPrime(int32_t n) {
    if (n <= 1) {
        return false;
    }

    for (int32_t i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}