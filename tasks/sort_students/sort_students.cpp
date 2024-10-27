#include "sort_students.h"
#include <algorithm>
#include <tuple>

bool DateOrderSort(const Student &first_student, const Student &second_student);

bool NameOrderSort(const Student &first_student, const Student &second_student);

void SortStudents(std::vector<Student>& students, SortKind sortKind) {

	if (sortKind == SortKind::Date) {

		std::sort(students.begin(), students.end(), DateOrderSort);
	} else {

		std::sort(students.begin(), students.end(), NameOrderSort);
	}

};

bool DateOrderSort(const Student &first_student, const Student &second_student) {

	std::tuple<int, int, int> first_student_birth_date =
		std::tie(first_student.birth_date.year, first_student.birth_date.month, first_student.birth_date.day);

	std::tuple<int, int, int> second_student_birth_date =
		std::tie(second_student.birth_date.year, second_student.birth_date.month, second_student.birth_date.day);

    if (first_student_birth_date != second_student_birth_date) {

    	return first_student_birth_date < second_student_birth_date;
   	}

   	return NameOrderSort(first_student, second_student);
};

bool NameOrderSort(const Student &first_student, const Student &second_student) {

	std::tuple<std::string, std::string> first_student_name = std::tie(first_student.last_name, first_student.name);

	std::tuple<std::string, std::string> second_student_name = std::tie(second_student.last_name, second_student.name);

	if (first_student_name != second_student_name) {

		return first_student_name < second_student_name;
	}

	return DateOrderSort(first_student, second_student);
}
