#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "model.h"
#include "utils.h"

s21::Obj::Obj(std::string_view filename) {
  std::ifstream fp(filename.data());
  std::string buf;

  if (!fp.is_open()) {
    std::stringstream ss;
    ss << "Couldn't open the file `" << filename << "`";
    throw std::runtime_error(ss.str());
  }

  while (std::getline(fp, buf)) {
    if (StartsWith(buf, "v ")) {
      // skipping the prefix "v "
      ParseVertex_({buf.data() + 2, buf.size() - 2});
    } else if (StartsWith(buf, "f ")) {
      // skipping the prefix "f "
      ParseIndex_({buf.data() + 2, buf.size() - 2});
    }
  }

  fp.close();
}

auto s21::Obj::ParseVertex_(std::string_view line) -> void {
  std::stringstream ss(line.data());
  float x, y, z;

  ss >> x >> y >> z;
  vertices_.push_back(x);
  vertices_.push_back(y);
  vertices_.push_back(z);
}

auto s21::Obj::ParseIndex_(std::string_view line) -> void {
  indices_type tmp;
  std::size_t indices_count = 0;

  for (const auto& tok : SplitAll(line, ' ')) {
    if (tok.empty()) continue;

    std::stringstream ss(tok.data());
    int idx;

    ss >> idx;
    if (idx < 0)
      tmp.push_back(static_cast<unsigned int>(idx + (vertices_.size() / 3)));
    else
      tmp.push_back(static_cast<unsigned int>(idx - 1));
    if (tmp.size() > 1) tmp.push_back(tmp.back());

    ++indices_count;
  }

  indices_.insert(indices_.end(), tmp.cbegin(), tmp.cend());
  indices_.push_back(tmp.at(0));
  facets_count_ += indices_count;
}

void s21::Obj::RotateModel(int rot, Axis axis) {
  float rad = rot * PI / 180;
  float s = sin(rad), c = cos(rad), x1 = 0, y1 = 0, z1 = 0;

  for (size_t i = 0; i < vertices_.size(); i += 3) {
    x1 = vertices_[i];
    y1 = vertices_[i + 1];
    z1 = vertices_[i + 2];

    switch (axis) {
      case Axis::X:
        vertices_[i + 1] = y1 * c - s * z1;
        vertices_[i + 2] = y1 * s + c * z1;
        break;
      case Axis::Y:
        vertices_[i] = x1 * c + s * z1;
        vertices_[i + 2] = -x1 * s + c * z1;
        break;
      case Axis::Z:
        vertices_[i] = x1 * c - s * y1;
        vertices_[i + 1] = x1 * s + c * y1;
        break;
    }
  }
}

void s21::Obj::MoveModel(float val, Axis axis) {
  for (size_t i = 0; i < vertices_.size(); i += 3)
    vertices_[i + static_cast<size_t>(axis)] += val;
}

void s21::Obj::ScaleModel(float val) {
  for (size_t i = 0; i < vertices_.size(); ++i) vertices_[i] *= val;
}
