#include "palindrome.h"
#include <stdint.h>

bool IsPalindrome(const std::string& str) {

    size_t left_idx = 0;

    size_t right_idx = str.length() - 1;

    if (str.length() == 1 || str.length() == 0) {

        return true;
    }

    while (left_idx < right_idx) {

        while (left_idx < right_idx && (str[left_idx] == ' ')) {

            ++left_idx;
        }

        while (left_idx < right_idx && (str[right_idx] == ' ')) {

            --right_idx;
        }

        if (str[left_idx] != str[right_idx]) {

            return false;
        }

        if (left_idx != right_idx) {

            ++left_idx;

            --right_idx;
        }
    }

    return true;
}
