#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef __DEBUG
#define __DEBUG__ 0
#endif

bool areDigitsOnEitherSideEqual(const char* str, int size, int comparisons) {
    for (int i = 0; i < comparisons; i++) {
        if (*(str + i) != *(str + size - 1 - i)) {
            return false;
        }
    }

    return true;
}

bool isPalindrome(long n) {
    const size_t length = sizeof(n);
    char numberString[length];

    sprintf(numberString, "%li", n);

    const size_t numberStringLength = strlen(numberString);
    int comparisons = (int)numberStringLength / 2;

#if __DEBUG__ == 1
    printf("Comparison(s): %i\n", comparisons);
#endif

    if (areDigitsOnEitherSideEqual(numberString, numberStringLength,
                                   comparisons)) {
        return true;
    }

    return false;
}

void printTestIsPalindrome(long n, bool expectedResult) {
    bool actualResult = isPalindrome(n);
    const char* _isPalindrome = actualResult ? "true" : "false";
    printf("%s%li%s%-30s\n", "isPalindrome(", n, "): ", _isPalindrome);
    assert(expectedResult == actualResult);
}

int main(void) {
    printTestIsPalindrome(0, true);
    printTestIsPalindrome(1, true);
    printTestIsPalindrome(2, true);
    printTestIsPalindrome(9, true);
    printTestIsPalindrome(10, false);
    printTestIsPalindrome(11, true);
    printTestIsPalindrome(12, false);
    printTestIsPalindrome(99, true);
    printTestIsPalindrome(100, false);
    printTestIsPalindrome(101, true);
    printTestIsPalindrome(102, false);
    printTestIsPalindrome(121, true);
    printTestIsPalindrome(999, true);
    printTestIsPalindrome(1001, true);
    printTestIsPalindrome(1221, true);
    printTestIsPalindrome(1321, false);
    printTestIsPalindrome(9009, true);
    printTestIsPalindrome(9999, true);
    printTestIsPalindrome(10101, true);
    printTestIsPalindrome(12221, true);
    printTestIsPalindrome(12321, true);
    printTestIsPalindrome(12331, false);
    printTestIsPalindrome(12345654321, true);
    printTestIsPalindrome(12345678901, false);
    printTestIsPalindrome(123456654321, true);
    printTestIsPalindrome(__LONG_MAX__, false);

    return 0;
}