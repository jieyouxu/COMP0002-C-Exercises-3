#include <stdbool.h>
#include <stdint.h>

#include "../../bdd-for-c.h"

#include "../strong-number.h"

#define ERROR -1
#define SHOULD_BE_UNCHANGED -3

void resetArrayElementsToZero(int32_t* array, size_t size) {
    for (int32_t i = 0; i < size; i++) {
        if (array+i) {
            *(array+i) = 0;
        }
    }
}

spec("StrongNumber") {
    describe("bool is_strong_number(int32_t n)") {
        it("should return false for n < 0") {
            check(is_strong_number(-1) == false);
        }

        it("should return false for n = 0") {
            check(is_strong_number(0) == false);
        }

        it("should return true for n = 1") {
            check(is_strong_number(1) == true);
        }

        it("should return true for n = 2") {
            check(is_strong_number(2) == true);
        }

        it("should return false for n = 144") {
            check(is_strong_number(144) == false);
        }

        it("should return true for n = 145") {
            check(is_strong_number(145) == true);
        }

        it("should return true for n = 40585") {
            check(is_strong_number(40585) == true);
        }
    }

    describe("void find_strong_numbers_between(int32_t lower_bound, "
        "int32_t upper_bound, int32_t* out_strong_numbers)") {

        enum s { size = 80 };
        int32_t strong_numbers[size] = {};

        describe("should handle invalid inputs") {
            before_each() {
                resetArrayElementsToZero(strong_numbers, size);
            }

            after() {
                resetArrayElementsToZero(strong_numbers, size);
            }

            it("should produce [-1] and return 0 when lower_bound or upper_bound are < 0") {
                int32_t count1 =  find_strong_numbers_between(-1, 1, strong_numbers, size);
                check(strong_numbers[0] == ERROR);
                check(count1 == 0);

                int32_t count2 = find_strong_numbers_between(1, -1, strong_numbers, size);
                check(strong_numbers[0] == ERROR);
                check(count2 == 0);

                int32_t count3 = find_strong_numbers_between(-1, 1, strong_numbers, size);
                check(strong_numbers[0] == ERROR);
                check(count3 == 0);
            }

            it("should produce [-1] and return 0 when lower_bound > upper_bound") {
                int32_t count = find_strong_numbers_between(2, 1, strong_numbers, size);
                check(strong_numbers[0] == ERROR);
                check(count == 0);
            }

            it("should do nothing and return 0 when out_strong_numbers is a null pointer") {
                strong_numbers[0] = SHOULD_BE_UNCHANGED;
                int32_t count = find_strong_numbers_between(0, 1, (void *) 0, size);
                check(strong_numbers[0] == SHOULD_BE_UNCHANGED);
                check(count == 0);
            }

            it("should do nothing and return 0 when out_strong_numbers_size = 0") {
                strong_numbers[0] = SHOULD_BE_UNCHANGED;
                int32_t count = find_strong_numbers_between(3, 3, strong_numbers, 0);
                check(strong_numbers[0] == SHOULD_BE_UNCHANGED);
                check(count == 0);
            }
        }

        describe("should handle natural numbers input") {
            it("should return [-1] for 0 <= n <= 0") {
                strong_numbers[0] = -3;
                int32_t count = find_strong_numbers_between(0, 0, strong_numbers, size);
                check(strong_numbers[0] == ERROR);
                check(count == 0);
            }

            it("should return [1] for 0 <= n <= 1") {
                strong_numbers[0] = -3;
                int32_t count = find_strong_numbers_between(0, 1, strong_numbers, size);
                check(strong_numbers[0] == 1);
                check(count == 1);
            }

            it("should return [1] for 1 <= n <= 1") {
                strong_numbers[0] = -3;
                int32_t count = find_strong_numbers_between(1, 1, strong_numbers, size);
                check(strong_numbers[0] == 1);
                check(count == 1);
            }

            it("should return [1, 2] for 0 <= n <= 2") {
                strong_numbers[0] = -3;
                strong_numbers[1] = -3;
                int32_t count = find_strong_numbers_between(0, 2, strong_numbers, size);
                check(strong_numbers[0] == 1);
                check(strong_numbers[1] == 2);
                check(count == 2);
            }

            it("should return [1, 2, 145, 40585] for 0 <= n <= 50000") {
                strong_numbers[0] = -3;
                strong_numbers[1] = -3;
                strong_numbers[2] = -3;
                strong_numbers[3] = -3;
                int32_t count = find_strong_numbers_between(0, 50000, strong_numbers, size);
                check(strong_numbers[0] == 1);
                check(strong_numbers[1] == 2);
                check(strong_numbers[2] == 145);
                check(strong_numbers[3] == 40585);
                check(count == 4);
            }
        }
    }
}