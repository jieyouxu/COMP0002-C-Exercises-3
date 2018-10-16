#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#ifndef __DEBUG__
#define __DEBUG__ 1
#endif

#define TRANSLATIONS_COUNT 31
#define OUTPUT_STRING_MAX_LENGTH 100

#define HUNDRED_CODE -1
#define HUNDRED_STRING "HUNDRED"
#define AND_CODE -2
#define AND_STRING "AND"
#define NULL_CODE -3
#define NULL_STRING "[!] INVALID_NUMBER [!]"

typedef const char* string_t;

typedef struct Translation {
    int number;
    string_t numberToString;
} Translation_t;

static Translation_t translations[TRANSLATIONS_COUNT] = {
    {.number = 0, .numberToString = "ZERO"},
    {.number = 1, .numberToString = "ONE"},
    {.number = 2, .numberToString = "TWO"},
    {.number = 3, .numberToString = "THREE"},
    {.number = 4, .numberToString = "FOUR"},
    {.number = 5, .numberToString = "FIVE"},
    {.number = 6, .numberToString = "SIX"},
    {.number = 7, .numberToString = "SEVEN"},
    {.number = 8, .numberToString = "EIGHT"},
    {.number = 9, .numberToString = "NINE"},
    {.number = 10, .numberToString = "TEN"},
    {.number = 11, .numberToString = "ELEVEN"},
    {.number = 12, .numberToString = "TWELVE"},
    {.number = 13, .numberToString = "THIRTEEN"},
    {.number = 14, .numberToString = "FOURTEEN"},
    {.number = 15, .numberToString = "FIVETEEN"},
    {.number = 16, .numberToString = "SIXTEEN"},
    {.number = 17, .numberToString = "SEVENTEEN"},
    {.number = 18, .numberToString = "EIGHTEEN"},
    {.number = 19, .numberToString = "NINETEEN"},
    {.number = 20, .numberToString = "TWENTY"},
    {.number = 30, .numberToString = "THIRTY"},
    {.number = 40, .numberToString = "FOURTY"},
    {.number = 50, .numberToString = "FIFTY"},
    {.number = 60, .numberToString = "SIXTY"},
    {.number = 70, .numberToString = "SEVENTY"},
    {.number = 80, .numberToString = "EIGHTY"},
    {.number = 90, .numberToString = "NINETY"},
    {.number = HUNDRED_CODE, .numberToString = "HUNDRED"},
    {.number = AND_CODE, .numberToString = "AND"},
    {.number = NULL_CODE, .numberToString = NULL_STRING}
};

void clearInputBuffer(void);

static int targetInt = 0;

void readTargetInt(void) {
    int _targetInt = 0;
    printf("Enter integer to verbalise:\n");
    scanf("%i", &_targetInt);
    clearInputBuffer();

    assert(_targetInt >= 0 && _targetInt <= 999);
    targetInt = _targetInt;
}

static char buffer[OUTPUT_STRING_MAX_LENGTH];

bool isNumberBetween(int n, int lowerBound, int upperBound);

const char* verbalizeThreeDigitNumber(int hundredthDigit, int tenthDigit, int unitDigit);
const char* verbalizeTwoDigitNumber(int tenthDigit, int unitDigit);
const char* verbalizeUnitDigitNumber(int unitDigit);

const char* convertDigitToString(int digit) {
    assert(digit >= 0 && digit <= 9);
    return translations[digit].numberToString;
}

const char* convertNumberBetween10And20ToString(int n) {
    for (int i = 10; i <= 20; i++) {
        if (translations[i].number == n) {
            return translations[i].numberToString;
        }
    }

    return NULL_STRING;
}

const char* convertTensBetween21And99ToString(int tenthDigit) {
    for (int i = 20; i < TRANSLATIONS_COUNT; i++) {
        if (translations[i].number == tenthDigit*10) {
            return translations[i].numberToString;
        }
    }

    return NULL_STRING;
}

const char* convertTwoDigitNumberBetween21And99ToString(int tenthDigit, int unitDigit) {
    const char* tenthString = convertTensBetween21And99ToString(tenthDigit);
    const char* unitString = convertDigitToString(unitDigit);

    buffer[0] = '\0';
    sprintf(buffer, "%s %s", tenthString, unitString);
    return buffer;
}

bool isNumberMultipleOfTen(int n) {
    return n % 10 == 0;
}

const char* convertHundredsToString(int hundredthDigit) {
    const char* hundredthString = convertDigitToString(hundredthDigit);

    buffer[0] = '\0';
    sprintf(buffer, "%s %s", hundredthString, HUNDRED_STRING);
    return buffer;
}

const char* convertMultiplesOfTenGreaterThan100ToString(int hundredthDigit, int tenthDigit) {
    const char* hundredthString = convertDigitToString(hundredthDigit);
    const char* tenthString;

    if (tenthDigit > 2) {
        tenthString = convertTensBetween21And99ToString(tenthDigit);
    } else if (tenthDigit == 2) {
        tenthString = translations[20].numberToString;
    } else {
        tenthString = translations[10].numberToString;
    }

    buffer[0] = '\0';
    sprintf(buffer, "%s %s %s %s", hundredthString, HUNDRED_STRING, AND_STRING, tenthString);
    return buffer;
}

const char* convertThreeDigitsToString(int hundredthDigit, int tenthDigit, int unitDigit) {
    const char* hundredthString = convertDigitToString(hundredthDigit);
    const char* tenthString;
    const char* tenthAndUnitString;
    const char* unitString = convertDigitToString(unitDigit);

    buffer[0] = '\0';

    if (tenthDigit > 2 || (tenthDigit == 2 && tenthDigit >= 1)) {
        tenthString = convertTensBetween21And99ToString(tenthDigit);
        sprintf(buffer, "%s %s %s %s %s", hundredthString, HUNDRED_STRING, AND_STRING, tenthString, unitString);
    } else if (tenthDigit == 2 || tenthDigit == 1) {
        tenthAndUnitString = convertNumberBetween10And20ToString(tenthDigit*10 + unitDigit);
        sprintf(buffer, "%s %s %s %s", hundredthString, HUNDRED_STRING, AND_STRING, tenthAndUnitString);
    } else {
        sprintf(buffer, "%s %s %s %s", hundredthString, HUNDRED_STRING, AND_STRING, unitString);
    }

    return buffer;
}

const char* convertHundredsAndUnitsToString(int hundredthDigit, int unitDigit) {
    const char* hundredthString = convertDigitToString(hundredthDigit);
    const char* unitString = convertDigitToString(unitDigit);

    buffer[0] = '\0';
    sprintf(buffer, "%s %s %s %s", hundredthString, HUNDRED_STRING, AND_STRING, unitString);
    return buffer;
}

const char* verbalize(int n) {
    assert(n >= 0 && n <= 999);

    if (isNumberBetween(n, 100, 999)) {
        int hundredthDigit = n / 100;
        int doubleDigitRemainder = n % 100;
        int tenthDigit = doubleDigitRemainder / 10;
        int unitDigit = doubleDigitRemainder % 10;
        
        bool isMultipleOfHundred = tenthDigit == 0 && unitDigit == 0;
        bool isMultipleOfTenButNotHundred = unitDigit == 0;
        bool isHundredAndUnitsNoTenths = tenthDigit == 0;
        if (isMultipleOfHundred) {
            return convertHundredsToString(hundredthDigit);
        } else if (isMultipleOfTenButNotHundred) {
            return convertMultiplesOfTenGreaterThan100ToString(hundredthDigit, tenthDigit);
        } else if (isHundredAndUnitsNoTenths) {
            return convertHundredsAndUnitsToString(hundredthDigit, unitDigit);
        } else {
            return convertThreeDigitsToString(hundredthDigit, tenthDigit, unitDigit);
        }

    } else if (isNumberBetween(n, 21, 99)) {
        int tenthDigit = n / 10;
        int unitDigit = n % 10;
        
        if (isNumberMultipleOfTen(n)) {
            return convertTensBetween21And99ToString(tenthDigit);
        } else {
            return convertTwoDigitNumberBetween21And99ToString(tenthDigit, unitDigit);
        }

    } else if (isNumberBetween(n, 10, 20)) { // if number is between 10 and 20
        return convertNumberBetween10And20ToString(n);
    } else {
        return convertDigitToString(n);
    }
}

void clearInputBuffer(void) {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

bool isNumberBetween(int n, int lowerBound, int higherBound) {
    return n >= lowerBound && n <= higherBound;
}

void testNumberToString(int number) {
    printf("%-20i%-20s\n", number, verbalize(number));
}

int main(void) {
    readTargetInt();
    printf("\n=================================================\n");
    printf("%-20s%-20s\n%-20i%-20s\n", "User Input: ", "Verbalised Output: ", targetInt, verbalize(targetInt));
    printf("=================================================\n");

#if __DEBUG__ == 1
    printf("\n=================================================\n");
    printf("BEGIN TESTS\n");
    printf("=================================================\n");
    testNumberToString(0);
    testNumberToString(1);
    testNumberToString(2);
    testNumberToString(9);
    testNumberToString(10);
    testNumberToString(11);
    testNumberToString(19);
    testNumberToString(20);
    testNumberToString(21);
    testNumberToString(29);
    testNumberToString(30);
    testNumberToString(90);
    testNumberToString(99);
    testNumberToString(100);
    testNumberToString(101);
    testNumberToString(109);
    testNumberToString(110);
    testNumberToString(111);
    testNumberToString(119);
    testNumberToString(120);
    testNumberToString(121);
    testNumberToString(129);
    testNumberToString(130);
    testNumberToString(190);
    testNumberToString(199);
    testNumberToString(200);
    testNumberToString(201);
    testNumberToString(211);
    testNumberToString(299);
    testNumberToString(300);
    testNumberToString(500);
    testNumberToString(900);
    testNumberToString(909);
    testNumberToString(990);
    testNumberToString(999);
#endif

    return 0;
}