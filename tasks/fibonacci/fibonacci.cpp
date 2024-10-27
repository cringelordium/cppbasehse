#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {

    if (n == 0 || n == 1) {

        return n;
    }

    int64_t current = 1;

    int64_t previous = 0;

    for (int64_t i = 2; i <= n; ++i) {

        current = current + previous;

        previous = current - previous;
    }

    return current;
}
