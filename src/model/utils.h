#ifndef VIEWER_3D_V2_MODEL_UTILS_H_
#define VIEWER_3D_V2_MODEL_UTILS_H_

#include <sstream>
#include <string_view>
#include <utility>
#include <vector>

namespace s21 {
using Split = std::vector<std::string_view>;

auto StartsWith(std::string_view src, std::string_view prefix) -> bool;

auto SplitAll(std::string_view src, char sep) -> Split;
}  // namespace s21

#endif  // VIEWER_3D_V2_MODEL_UTILS_H_
