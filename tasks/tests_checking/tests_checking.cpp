#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {

    std::deque<std::string> check_order;

    std::vector<std::string> names_queries;

    for (const StudentAction& action : student_actions) {

        if (action.side == Side::Top) {

            check_order.push_front(action.name);
        } else {

            check_order.push_back(action.name);
        }
    }

    for (const size_t x_i : queries) {

        names_queries.push_back(check_order[x_i - 1]);
    }

    return names_queries;
}
