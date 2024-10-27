#include "scorer.h"
#include <algorithm>
#include <vector>

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {

    ScoreTable score_table;
    std::map<std::pair<StudentName, TaskName>, bool> merge_requests;
    std::map<std::pair<StudentName, TaskName>, bool> clang_check;
    Events sorted_events(events.begin(), events.end());

    std::sort(sorted_events.begin(), sorted_events.end(),
              [](const Event& first_event, const Event& second_event) { return first_event.time < second_event.time; });

    for (const auto& event : sorted_events) {

        if (event.time > score_time) {
            break;
        }

        if (event.event_type == EventType::CheckSuccess) {
            clang_check[{event.student_name, event.task_name}] = true;
        } else if (event.event_type == EventType::CheckFailed) {
            clang_check[{event.student_name, event.task_name}] = false;
        } else if (event.event_type == EventType::MergeRequestOpen) {
            merge_requests[{event.student_name, event.task_name}] = true;
        } else if (event.event_type == EventType::MergeRequestClosed) {
            merge_requests[{event.student_name, event.task_name}] = false;
        }
    }

    for (const auto& event : sorted_events) {
        if (event.time > score_time) {
            break;
        }

        if (clang_check[{event.student_name, event.task_name}] &&
            !merge_requests[{event.student_name, event.task_name}]) {
            score_table[event.student_name].insert(event.task_name);
        }
    }

    return score_table;
}
