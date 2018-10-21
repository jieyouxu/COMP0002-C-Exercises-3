#include <stdint.h>

#include "../../bdd-for-c.h"

#include "../digitalize.h"

void resetArrayElementsToZero(int32_t* array, size_t size) {
    for (int i = 0; i < size; i++) {
        *(array + i) = 0;
    }
}

spec("Digtialize") {
    describe("int32_t compute_num_of_digits(int32_t n)") {
        it("should return 1 for 1-digit numbers") {
            check(compute_num_of_digits(0) == 1);
            check(compute_num_of_digits(1) == 1);
            check(compute_num_of_digits(9) == 1);
        }

        it("should return 2 for 2-digit numbers") {
            check(compute_num_of_digits(10) == 2);
            check(compute_num_of_digits(99) == 2);
        }

        it("should return 3 for 3-digit numbers") {
            check(compute_num_of_digits(100) == 3);
            check(compute_num_of_digits(999) == 3);
        }

        it("should return n for n-digit numbers") {
            check(compute_num_of_digits(1234) == 4);
            check(compute_num_of_digits(12345) == 5);
            check(compute_num_of_digits(123456) == 6);
            check(compute_num_of_digits(1234567) == 7);
            check(compute_num_of_digits(12345678) == 8);
            check(compute_num_of_digits(123456789) == 9);
            check(compute_num_of_digits(1234567890) == 10);
        }
    }

    enum s { size = 10 };
    int32_t actual[size] = {};

    describe("handles invalid input") {
        before_each() {
            resetArrayElementsToZero(actual, size);
        }

        after() {
            resetArrayElementsToZero(actual, size);
        }

        it("should return [-1] when n < 0") {
            digitalize(-1, actual, size);
            check(actual[0] == -1);
        }

        it("should do nothing upon receiving a null pointer") {
            digitalize(0, ((void*) 0), 1);
        }

        it("should handle size <= 0") {
            it("should return [-1] when size < 0") {
                digitalize(0, actual, -1);
                check(actual[0] == -1);
            }

            it("should return [-1] when size = 0") {
                digitalize(0, actual, 0);
                check(actual[0] == -1);
            }
        }
    }

    describe("handles natural numbers") {
        before_each() {
            resetArrayElementsToZero(actual, size);
        }

        after() {
            resetArrayElementsToZero(actual, size);
        }

        it("should handle n = 0") {
            actual[0] = -1;
            digitalize(0, actual, size);
            check(actual[0] == 0);
        }

        it("should handle 1-digit numbers") {
            digitalize(1, actual, size);
            check(actual[0] == 1);

            digitalize(9, actual, size);
            check(actual[0] == 9);
        }

        it("should handle 2-digit numbers") {
            digitalize(10, actual, size);
            check(actual[1] == 1);
            check(actual[0] == 0);

            digitalize(99, actual, size);
            check(actual[1] == 9);
            check(actual[0] == 9);
        }

        it("should handle 3-digit numbers") {
            digitalize(100, actual, size);
            check(actual[2] == 1)
            check(actual[1] == 0);
            check(actual[0] == 0);

            digitalize(999, actual, size);
            check(actual[2] == 9)
            check(actual[1] == 9);
            check(actual[0] == 9);
        }

        it("should handle n-digit numbers") {
            digitalize(1234, actual, size);
            check(actual[3] == 1)
            check(actual[2] == 2)
            check(actual[1] == 3);
            check(actual[0] == 4);

            digitalize(12345, actual, size);
            check(actual[4] == 1)
            check(actual[3] == 2)
            check(actual[2] == 3)
            check(actual[1] == 4);
            check(actual[0] == 5);

            digitalize(123456, actual, size);
            check(actual[5] == 1)
            check(actual[4] == 2)
            check(actual[3] == 3)
            check(actual[2] == 4)
            check(actual[1] == 5);
            check(actual[0] == 6);
        }
    }
}