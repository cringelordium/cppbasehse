#include "reduce_fraction.h"

int64_t GcdFinder(int64_t numerator, int64_t denominator);

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {

    int64_t gcd = GcdFinder(numerator, denominator);

    if (gcd == 0) {

        return numerator + denominator;
    }

    return (numerator / gcd) + (denominator / gcd);
};

int64_t GcdFinder(int64_t numerator, int64_t denominator) {

    while (numerator != 0 && denominator != 0) {

        if (numerator > denominator) {

            numerator %= denominator;
        } else {

            denominator %= numerator;
        }
    }

    return numerator + denominator;
}
