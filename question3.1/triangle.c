#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define OK 0
#define EXCEPTION_INVALID_RANGE 1
#define EXCEPTION_NOT_A_TRIANGLE 2

void discardInputBuffer(void) {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

double a = 0;
double b = 0;
double c = 0;

bool isInputNotWithinValidRange(double a, double b, double c) {
    return a <= 0 || b <= 0 || c <= 0;
}

bool isNotATriangle(double a, double b, double c) {
    // Make use of triangle inequality theorem.
    bool abc = a + b > c;
    bool acb = a + c > b;
    bool bca = b + c > a;

    return !(abc && acb && bca);
}

int readTriangleLengthsInput(void) {
    double _a = 0;
    double _b = 0;
    double _c = 0;

    printf("Please enter lengths of sides a, b and c of a triange (separated by spaces):\n");
    scanf("%lf %lf %lf", &_a, &_b, &_c);
    discardInputBuffer();

    if (isInputNotWithinValidRange(_a, _b, _c)) {
        printf("[WARNING] Input must be numbers greater than zero.\n");
        return EXCEPTION_INVALID_RANGE;
    }

    if (isNotATriangle(_a, _b, _c)) {
        printf("[WARNING] Input must be for a valid triangle.\n");
        return EXCEPTION_NOT_A_TRIANGLE;
    }

    a = _a;
    b = _b;
    c = _c;

    return OK;
}

double semiperimeter = 0.0;
double perimeter = 0.0;
double area = 0.0;

double calculateSemiperimeter(double a, double b, double c) {
    return 0.5 * (a + b + c);
}

double calculatePerimeter(double a, double b, double c) {
    return a + b + c;
}

double calculateArea(double a, double b, double c) {
    double s = calculateSemiperimeter(a, b, c);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

void printArea(void) {
    printf("%-12s%lf\n", "Area:", area);
}

void printPerimeter(void) {
    printf("%-12s%lf\n", "Perimeter:", perimeter);
}

int main(void) {
    if (readTriangleLengthsInput() != OK) {
        return -1;
    }

    semiperimeter = calculateSemiperimeter(a, b, c);
    perimeter = calculatePerimeter(a, b, c);
    area = calculateArea(a, b, c);

    printArea();
    printPerimeter();

    return 0;
}