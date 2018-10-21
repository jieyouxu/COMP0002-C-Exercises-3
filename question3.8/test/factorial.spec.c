#include <stdbool.h>

#include "../../bdd-for-c.h"

#include "../factorial.h"

spec("int32_t factorial(int32_t n)") {
    describe("handles invalid inputs") {
        it("should return -1") {
            check(factorial(-1) == -1);
        }
    }

    describe("special case: n = 0") {
        it("should return 1") {
            check(factorial(0) == 1);
        }
    }

    describe("handles positive integers") {
        it ("should correctly calculate n!") {
            check(factorial(1) == 1);
            check(factorial(2) == 2);
            check(factorial(3) == 6);
            check(factorial(4) == 24);
            check(factorial(5) == 120);
            check(factorial(6) == 720);
            check(factorial(7) == 5040);
            check(factorial(8) == 40320);
            check(factorial(9) == 362880);
            check(factorial(10) == 3628800);
        }
    }
}