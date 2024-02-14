#include "utils.h"

#include <fstream>

auto s21::StartsWith(std::string_view src, std::string_view prefix) -> bool {
  return src.compare(0, prefix.size(), prefix) == 0;
}

auto s21::SplitAll(std::string_view src, char sep) -> Split {
  Split tmp;
  size_t pos = src.find(sep);
  size_t init_pos = 0;

  while (pos != std::string::npos) {
    tmp.push_back(src.substr(init_pos, pos - init_pos));
    init_pos = pos + 1;
    pos = src.find(sep, init_pos);
  }

  tmp.push_back(src.substr(init_pos, std::min(pos, src.size()) - init_pos + 1));

  return tmp;
}
