#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef __DEBUG__
#define __DEBUG__ 1
#endif

#define LOWER_BOUND 0
#define UPPER_BOUND 999

#define STR_BUFFER_SIZE 80

#define NUMSTR_CONJ_AND     "AND"
#define NUMSTR_HUNDRED      "HUNDRED"

#define NUMSTR_ZERO         "ZERO"
#define NUMSTR_ONE          "ONE"
#define NUMSTR_TWO          "TWO"
#define NUMSTR_THREE        "THREE"
#define NUMSTR_FOUR         "FOUR"
#define NUMSTR_FIVE         "FIVE"
#define NUMSTR_SIX          "SIX"
#define NUMSTR_SEVEN        "SEVEN"
#define NUMSTR_EIGHT        "EIGHT"
#define NUMSTR_NINE         "NINE"
#define NUMSTR_TEN          "TEN"
#define NUMSTR_ELEVEN       "ELEVEN"
#define NUMSTR_TWELVE       "TWELVE"
#define NUMSTR_THIRTEEN     "THIRTEEN"
#define NUMSTR_FOURTEEN     "FOURTEEN"
#define NUMSTR_FIFTEEN      "FIFTEEN"
#define NUMSTR_SIXTEEN      "SIXTEEN"
#define NUMSTR_SEVENTEEN    "SEVENTEEN"
#define NUMSTR_EIGHTEEN     "EIGHTEEN"
#define NUMSTR_NINETEEN     "NINETEEN"
#define NUMSTR_TWENTY       "TWENTY"
#define NUMSTR_THIRTY       "THIRTY"
#define NUMSTR_FOURTY       "FOURTY"
#define NUMSTR_FIFTY        "FIFTY"
#define NUMSTR_SIXTY        "SIXTY"
#define NUMSTR_SEVENTY      "SEVENTY"
#define NUMSTR_EIGHTY       "EIGHTY"
#define NUMSTR_NINETY       "NINETY"

#define NULL_STR            "\0"

typedef struct ThreeDigitInteger {
    int32_t hundredthDigit;
    int32_t tenthDigit;
    int32_t unitsDigit;
} ThreeDigitInteger_t;

static char str[STR_BUFFER_SIZE];

int32_t askForTargetNumber(void);
void clearInputBuffer(void);

const char* verbalize(int32_t n);
ThreeDigitInteger_t digitize(int32_t n);
const char* convertDigitToString(int32_t n);
const char* convertTenToNineteenToString(int32_t n);
const char* convertTwentyToNinetyNineToString(int32_t n);
const char* convertTensWithinOneHundredToString(int32_t n);
const char* convertTwoDigitNumbersAboveTwentyNotTensToString(int32_t n);

bool isNumberBetween(int32_t n, int32_t lowerBound, int32_t upperBound);
bool isMultipleOfTen(int32_t n);

#if __DEBUG__ == 1
void testNumberCorrespondsToString(int32_t n, const char* s);
#endif

int32_t main(void) {
    int32_t targetNumber = askForTargetNumber();
    const char* targetNumberToString = verbalize(targetNumber);
    printf("%i => %s\n", targetNumber, targetNumberToString);

#if __DEBUG__ == 1
    testNumberCorrespondsToString(0, "ZERO");
    testNumberCorrespondsToString(1, "ONE");
    testNumberCorrespondsToString(2, "TWO");
    testNumberCorrespondsToString(3, "THREE");
    testNumberCorrespondsToString(4, "FOUR");
    testNumberCorrespondsToString(5, "FIVE");
    testNumberCorrespondsToString(6, "SIX");
    testNumberCorrespondsToString(7, "SEVEN");
    testNumberCorrespondsToString(8, "EIGHT");
    testNumberCorrespondsToString(9, "NINE");
    testNumberCorrespondsToString(10, "TEN");
    testNumberCorrespondsToString(11, "ELEVEN");
    testNumberCorrespondsToString(12, "TWELVE");
    testNumberCorrespondsToString(13, "THIRTEEN");
    testNumberCorrespondsToString(14, "FOURTEEN");
    testNumberCorrespondsToString(15, "FIFTEEN");
    testNumberCorrespondsToString(16, "SIXTEEN");
    testNumberCorrespondsToString(17, "SEVENTEEN");
    testNumberCorrespondsToString(18, "EIGHTEEN");
    testNumberCorrespondsToString(19, "NINETEEN");
    testNumberCorrespondsToString(20, "TWENTY");
    testNumberCorrespondsToString(21, "TWENTY ONE");
    testNumberCorrespondsToString(30, "THIRTY");
    testNumberCorrespondsToString(99, "NINETY NINE");
    testNumberCorrespondsToString(100, "ONE HUNDRED");
    testNumberCorrespondsToString(101, "ONE HUNDRED AND ONE");
    testNumberCorrespondsToString(110, "ONE HUNDRED AND TEN");
    testNumberCorrespondsToString(111, "ONE HUNDRED AND ELEVEN");
    testNumberCorrespondsToString(120, "ONE HUNDRED AND TWENTY");
    testNumberCorrespondsToString(121, "ONE HUNDRED AND TWENTY ONE");
    testNumberCorrespondsToString(200, "TWO HUNDRED");
    testNumberCorrespondsToString(201, "TWO HUNDRED AND ONE");
    testNumberCorrespondsToString(210, "TWO HUNDRED AND TEN");
    testNumberCorrespondsToString(211, "TWO HUNDRED AND ELEVEN");
    testNumberCorrespondsToString(220, "TWO HUNDRED AND TWENTY");
    testNumberCorrespondsToString(221, "TWO HUNDRED AND TWENTY ONE");
    testNumberCorrespondsToString(999, "NINE HUNDRED AND NINETY NINE");
#endif

    return 0;
}

int32_t askForTargetNumber(void) {
    int32_t _targetNumber = 0;
    printf("Please enter the number to convert to string [0-999]:\n");
    scanf("%i", &_targetNumber);
    assert(_targetNumber >= LOWER_BOUND && _targetNumber <= UPPER_BOUND);
    clearInputBuffer();
    return _targetNumber;
}

void clearInputBuffer(void) {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * There are several possible cases for converting a three digit number n to its
 * string representation S:
 * - Given conversion to string function str(m) where m is an integer;
 * - Given that the number n = 100 * X + 10 * Y + 1 * Z, where:
 *      - X is the hundredth digit,
 *      - Y is the tenth digit, and
 *      - Z is the units digit.
 * - Possible representation combinations include:
 *        S ::==    <X HUNDRED> AND <str(10*Y)> <str(Z)>    [CASE 1.0]
 *          |       <X HUNDRED> AND <str(10*Y)>             [CASE 1.1]
 *          |       <X HUNDRED> AND <str(Z)>                [CASE 1.2]
 *          |       <X HUNDRED>                             [CASE 1.3]
 *          |       <str(10*Y)> <str(Z)>                    [CSAE 2.0]
 *          |       <str(10*Y)>                             [CASE 2.1]
 *          |       <str(Z)>                                [CASE 3]
 * - Note that there is a special case for 11-19.
 */
const char* verbalize(int32_t targetNumber) {
    assert(targetNumber >= 0 && targetNumber <= 999);

    ThreeDigitInteger_t n = digitize(targetNumber);
    
    if (n.hundredthDigit >= 1 && n.hundredthDigit <= 9) {   // CASE 1.n
        const char* hundredthDigitString = convertDigitToString(n.hundredthDigit);

        if (n.tenthDigit == 0 && n.unitsDigit == 0) { // CASE 1.3
            snprintf(str, STR_BUFFER_SIZE, "%s %s", hundredthDigitString, NUMSTR_HUNDRED);
            return str;

        } else if (n.tenthDigit == 0 && n.unitsDigit != 0) { // CASE 1.2
            const char* unitsDigitString = convertDigitToString(n.unitsDigit);
            snprintf(str, STR_BUFFER_SIZE, "%s %s %s %s", 
                hundredthDigitString, NUMSTR_HUNDRED, NUMSTR_CONJ_AND, unitsDigitString);
            return str;

        } else if (n.tenthDigit != 0 && n.unitsDigit == 0) { // CASE 1.1
            const char* tenthDigitString = convertTensWithinOneHundredToString(n.tenthDigit*10);
            snprintf(str, STR_BUFFER_SIZE, "%s %s %s %s", 
                hundredthDigitString, NUMSTR_HUNDRED, NUMSTR_CONJ_AND, tenthDigitString);
            return str;

        } else if (n.tenthDigit == 1 && n.unitsDigit != 0) { // Special case X11-X19
            const char* numberString = convertTenToNineteenToString(n.tenthDigit*10 + n.unitsDigit);
            snprintf(str, STR_BUFFER_SIZE, "%s %s %s %s",
                hundredthDigitString, NUMSTR_HUNDRED, NUMSTR_CONJ_AND, numberString);
            return str;

        } else { // CASE 1.0
            const char* tenthDigitString = convertTensWithinOneHundredToString(n.tenthDigit*10);
            const char* unitsDigitString = convertDigitToString(n.unitsDigit);
            snprintf(str, STR_BUFFER_SIZE, "%s %s %s %s %s",
                hundredthDigitString, NUMSTR_HUNDRED, NUMSTR_CONJ_AND, tenthDigitString, unitsDigitString);
            return str;
        }
    } else if (n.hundredthDigit == 0 && n.tenthDigit >= 1 && n.tenthDigit <= 9) {   // CASE 2.n
        if (n.tenthDigit == 1 && n.unitsDigit != 0) {   // Handle 11-19 special case
            const char* numberString = convertTenToNineteenToString(n.tenthDigit*10 + n.unitsDigit);
            snprintf(str, STR_BUFFER_SIZE, "%s", numberString);
            return str;

        } else if (n.unitsDigit == 0) { // CASE 2.1
            const char* tenthString = convertTensWithinOneHundredToString(n.tenthDigit*10);
            snprintf(str, STR_BUFFER_SIZE, "%s", tenthString);
            return str;

        } else { // CASE 2.0
            const char* tenthString = convertTensWithinOneHundredToString(n.tenthDigit*10);
            const char* unitsString = convertDigitToString(n.unitsDigit);
            snprintf(str, STR_BUFFER_SIZE, "%s %s", tenthString, unitsString);
            return str;
        }
    } else { // CASE 3
        return convertDigitToString(n.unitsDigit);
    }

    return NULL_STR;
}

ThreeDigitInteger_t digitize(int32_t targetNumber) {
    int32_t hundredthDigit = targetNumber / 100;
    int32_t twoDigitRemainder = targetNumber % 100;
    int32_t tenthDigit = twoDigitRemainder / 10;
    int32_t unitsDigit = twoDigitRemainder % 10;

    ThreeDigitInteger_t n = {
        .hundredthDigit = hundredthDigit,
        .tenthDigit = tenthDigit,
        .unitsDigit = unitsDigit
    };

    return n;
}


const char* convertDigitToString(int32_t n) {
    switch (n) {
        case 0:
            return NUMSTR_ZERO;
        case 1:
            return NUMSTR_ONE;
        case 2:
            return NUMSTR_TWO;
        case 3:
            return NUMSTR_THREE;
        case 4:
            return NUMSTR_FOUR;
        case 5:
            return NUMSTR_FIVE;
        case 6:
            return NUMSTR_SIX;
        case 7: 
            return NUMSTR_SEVEN;
        case 8:
            return NUMSTR_EIGHT;
        case 9:
            return NUMSTR_NINE;
        default:
            return NULL_STR;
    }
}

const char* convertTenToNineteenToString(int32_t n) {
    switch (n) {
        case 10:
            return NUMSTR_TEN;
        case 11:
            return NUMSTR_ELEVEN;
        case 12:
            return NUMSTR_TWELVE;
        case 13:
            return NUMSTR_THIRTEEN;
        case 14:
            return NUMSTR_FOURTEEN;
        case 15:
            return NUMSTR_FIFTEEN;
        case 16:
            return NUMSTR_SIXTEEN;
        case 17:
            return NUMSTR_SEVENTEEN;
        case 18:
            return NUMSTR_EIGHTEEN;
        case 19:
            return NUMSTR_NINETEEN;
        default:
            return NULL_STR;
    }
}

const char* convertTensWithinOneHundredToString(int32_t n) {
    switch (n) {
        case 10:
            return NUMSTR_TEN;
        case 20:
            return NUMSTR_TWENTY;
        case 30:
            return NUMSTR_THIRTY;
        case 40:
            return NUMSTR_FOURTY;
        case 50:
            return NUMSTR_FIFTY;
        case 60:
            return NUMSTR_SIXTY;
        case 70:
            return NUMSTR_SEVENTY;
        case 80:
            return NUMSTR_EIGHTY;
        case 90:
            return NUMSTR_NINETY;
        default:
            return NULL_STR;
    }
}

#if __DEBUG__ == 1
static int testNumber = 0;
void testNumberCorrespondsToString(int32_t n, const char* s) {
    const char* expectedString = s;
    const char* actualString = verbalize(n);
    printf("%s: %i\n", __FILE__, __LINE__);
    printf("Test Number: %i\n", testNumber);
    assert(strcmp(expectedString, actualString) == 0);
    testNumber++;
}
#endif