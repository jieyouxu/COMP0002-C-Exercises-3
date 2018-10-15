#include <stdbool.h>
#include <stdio.h>

#define EXCEPTION_INVALID_RANGE -1

bool isParametersInValidRange(int base, int exponent) {
    bool isGreaterThanOrEqualToZero = base >= 0 && exponent >= 0;
    bool isNotBothZero = !(base == 0 && exponent == 0);
    return isGreaterThanOrEqualToZero && isNotBothZero;
}

int powLoop(int base, int exponent) {
    if (isParametersInValidRange(base, exponent)) {
        int result = base;

        if (base == 0) {
            return 0;
        }

        if (exponent == 0) {
            return 1;
        }

        for (int i = 1; i < exponent; i++) {
            result *= base;
        }

        return result;
    } else {
        printf("[WARNING] Invalid parameters!\n");
        return EXCEPTION_INVALID_RANGE;
    }
}

int powRecursive(int base, int exponent) {
    if (isParametersInValidRange(base, exponent)) {
        if (base == 0) {
            return 0;
        }

        if (exponent == 0) {
            return 1;
        }
    } else {
        printf("[WARNING] Invalid parameters!\n");
        return EXCEPTION_INVALID_RANGE;
    }

    if (exponent == 1) {
        return base;
    }
    return base * powRecursive(base, exponent - 1);
}

int main(void) {
    printf("%i\n", powLoop(0, 0));
    printf("%i\n", powLoop(0, 1));
    printf("%i\n", powLoop(1, 1));
    printf("%i\n", powLoop(2, 1));
    printf("%i\n", powLoop(2, 2));
    printf("%i\n", powLoop(2, 3));

    printf("%i\n", powRecursive(0, 0));
    printf("%i\n", powRecursive(0, 1));
    printf("%i\n", powRecursive(1, 1));
    printf("%i\n", powRecursive(2, 1));
    printf("%i\n", powRecursive(2, 2));
    printf("%i\n", powRecursive(2, 3));

    return 0;
}