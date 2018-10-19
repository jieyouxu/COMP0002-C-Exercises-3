#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "../question3.6/prime.h"

void printTwinPrimeNumbersBetween(int32_t lowerBound, int32_t upperBound) {
    assert(lowerBound >= 0 && upperBound >= 0);
    assert(lowerBound < upperBound);
    for (int32_t n = lowerBound; n <= upperBound - 2; n++) {
        if (isPrime(n)) {
            if (isPrime(n + 1)) {
                printf("%i %i\n", n, n + 1);
            }

            if (isPrime(n + 2)) {
                printf("%i %i\n", n, n + 2);
            }
        }
    }
}

int32_t main(void) {
    printTwinPrimeNumbersBetween(0, 1);
    printf("\n");
    printTwinPrimeNumbersBetween(0, 2);
    printf("\n");
    printTwinPrimeNumbersBetween(1, 2);
    printf("\n");
    printTwinPrimeNumbersBetween(2, 3);
    printf("\n");
    printTwinPrimeNumbersBetween(1, 5);
    printf("\n");
    printTwinPrimeNumbersBetween(0, 10);
    printf("\n");
    printTwinPrimeNumbersBetween(0, 15);
    printf("\n");
    printTwinPrimeNumbersBetween(0, 19);
    printf("\n");
    printTwinPrimeNumbersBetween(0, 100);
    printf("\n");
}