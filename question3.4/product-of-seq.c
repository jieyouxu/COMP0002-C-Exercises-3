#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

static int a = 0;
static int b = 0;

void clearInputBuffer(void) {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void askForRange(void) {
    int _a = 0;
    int _b = 0;
    printf("Please enter numbers a and b to produce the product from the range [a, b]:\n");
    scanf("%i %i", &_a, &_b);

    assert(a <= b);
    a = _a;
    b = _b;

    clearInputBuffer();
}

int computeSum(int leftBound, int rightBound) {
    assert(leftBound <= rightBound);

    int sum = 1;
    for (int i = leftBound; i <= rightBound; i++) {
        sum *= i;
    }

    return sum;
}

int main(void) {
    askForRange();
    int sum = computeSum(a, b);
    printf("%i\n", sum);

    return 0;
}