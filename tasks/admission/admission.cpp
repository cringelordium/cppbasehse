#include "admission.h"
#include <algorithm>
#include <tuple>

bool ApplicantPointsCompare(const Applicant* first_applicant_ptr, const Applicant* second_applicant_ptr);
bool ApplicantDateCompare(const Student* first_applicant_ptr, const Student* second_applicant_ptr);
bool ApplicantNameCompare(const Student* first_applicant_ptr, const Student* second_applicant_ptr);
std::tuple<std::string, std::string> NameAndLastNameFinder(const Student& applicant);

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {

    AdmissionTable admission_table;

    std::unordered_map<std::string, size_t> university_places;

    for (const auto& university : universities) {  // Unordered map for counting available places in universities (bad?)

        university_places[university.name] = university.max_students;
    }

    std::vector<const Applicant*> applicant_ptrs;

    for (const auto& applicant : applicants) {

        applicant_ptrs.push_back(&applicant);
    }

    std::sort(applicant_ptrs.begin(), applicant_ptrs.end(), ApplicantPointsCompare);

    for (const auto& applicant_ptr : applicant_ptrs) {

        const Applicant& applicant = *applicant_ptr;

        for (const auto& desired_university : applicant.wish_list) {

            if (university_places[desired_university] != 0) {

                const Student* student_ptr = &applicant.student;

                admission_table[desired_university].push_back(student_ptr);

                --university_places[desired_university];

                break;
            }
        }
    }

    for (auto& pair : admission_table) {

        std::sort(pair.second.begin(), pair.second.end(), ApplicantNameCompare);
    }

    return admission_table;
};

bool ApplicantPointsCompare(const Applicant* first_applicant_ptr, const Applicant* second_applicant_ptr) {

    if (first_applicant_ptr->points != second_applicant_ptr->points) {

        return first_applicant_ptr->points > second_applicant_ptr->points;
    }

    return ApplicantDateCompare(&(first_applicant_ptr->student), &(second_applicant_ptr->student));
};

bool ApplicantDateCompare(const Student* first_applicant_ptr, const Student* second_applicant_ptr) {

    std::tuple<int, int, int> first_applicant_birth_date =
        std::tie(first_applicant_ptr->birth_date.year, first_applicant_ptr->birth_date.month,
                 first_applicant_ptr->birth_date.day);

    std::tuple<int, int, int> second_applicant_birth_date =
        std::tie(second_applicant_ptr->birth_date.year, second_applicant_ptr->birth_date.month,
                 second_applicant_ptr->birth_date.day);

    if (first_applicant_birth_date != second_applicant_birth_date) {

        return first_applicant_birth_date < second_applicant_birth_date;
    }

    return ApplicantNameCompare(first_applicant_ptr, second_applicant_ptr);
};

bool ApplicantNameCompare(const Student* first_applicant_ptr, const Student* second_applicant_ptr) {

    std::tuple<std::string, std::string> first_applicant_tuple = NameAndLastNameFinder(*first_applicant_ptr);
    std::tuple<std::string, std::string> second_applicant_tuple = NameAndLastNameFinder(*second_applicant_ptr);

    if (first_applicant_tuple != second_applicant_tuple) {

        return first_applicant_tuple < second_applicant_tuple;
    }

    return ApplicantDateCompare(first_applicant_ptr, second_applicant_ptr);
};

std::tuple<std::string, std::string> NameAndLastNameFinder(const Student& applicant) {

    std::string name;

    std::string last_name;

    bool found_space = false;

    for (char letter : applicant.name) {

        if (found_space) {

            last_name += letter;
        } else {

            name += letter;

            if (std::isspace(letter)) {

                found_space = true;
            }
        }
    }

    return std::make_tuple(last_name, name);
};
