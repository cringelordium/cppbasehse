#include "is_leap.h"

bool IsLeap(int year) {

    int const third_divider = 400;

    int const second_divider = 100;

    int const first_divider = 4;

    if ((year % first_divider == 0 && !(year % second_divider == 0)) || (year % third_divider == 0)) {

        return true;
    }

    return false;
}
