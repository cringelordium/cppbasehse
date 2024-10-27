#include "password.h"
#include <algorithm>
#include <cctype>

bool ValidatePassword(const std::string& password) {

    int const lowerbound = 33;

    int const upperbound = 126;

    int const min_length = 8;

    int const max_length = 14;

    int counter = 0;

    if (std::any_of(password.begin(), password.end(),

                    [](char letter) {
                        return ((static_cast<int>(letter) > upperbound) || (static_cast<int>(letter) < lowerbound));
                    })) {

        return false;
    }

    if (password.length() < min_length || password.length() > max_length) {

        return false;
    }

    if (std::any_of(password.begin(), password.end(),

                    [](char letter) { return std::isupper(letter); })) {

        counter++;
    }

    if (std::any_of(password.begin(), password.end(),

                    [](char letter) { return std::islower(letter); })) {

        counter++;
    }

    if (std::any_of(password.begin(), password.end(),

                    [](char letter) { return std::isdigit(letter); })) {

        counter++;
    }

    if (std::any_of(password.begin(), password.end(),

                    [](char letter) { return !std::isalpha(letter) && !std::isdigit(letter); })) {

        counter++;
    }

    return counter > 2;
}