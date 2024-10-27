#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {

    int64_t passports = 0;

    std::multiset<int64_t> sorted_provinces(provinces.begin(), provinces.end());

    while (sorted_provinces.size() > 1) {

        auto it = sorted_provinces.begin();

        int64_t first_province = *it;
        sorted_provinces.erase(it);

        it = sorted_provinces.begin();
        int64_t second_province = *it;
        sorted_provinces.erase(it);

        passports += first_province + second_province;

        sorted_provinces.insert(first_province + second_province);
    }

    return passports;
}
