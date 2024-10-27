#include "unixpath.h"
#include <string>
#include <vector>
#include <algorithm>
#include <string_view>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {

    std::string absolute_path(current_working_dir.begin(), current_working_dir.end());

    std::string str_path(path.begin(), path.end());

    if (str_path.front() == '/') {
        absolute_path = str_path;
    } else {
        absolute_path += "/" + str_path;
    }

    std::vector<std::string> components;
    auto begin = absolute_path.begin();
    auto end = absolute_path.end();

    while (begin != end) {
        auto it = std::find(begin, end, '/');
        std::string component(begin, it);

        if (component == "..") {
            if (!components.empty()) {
                components.pop_back();
            }
        } else if (component != "." && !component.empty()) {
            components.push_back(component);
        }

        if (it != end) {
            begin = it + 1;
        } else {
            begin = end;
        }
    }

    std::string normalized_path;

    for (const std::string& component : components) {
        normalized_path += "/" + component;
    }

    if (normalized_path.empty()) {
        return "/";
    }

    return normalized_path;
}