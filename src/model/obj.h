#ifndef VIEWER_3D_V2_MODEL_OBJ_H_
#define VIEWER_3D_V2_MODEL_OBJ_H_

#define PI 3.1415926

#include <cmath>
#include <string_view>
#include <vector>

namespace s21 {

enum class Axis { X = 0, Y, Z };
class Obj {
 public:
  using vertices_type = std::vector<float>;
  using indices_type = std::vector<unsigned int>;

 public:
  Obj() = default;
  Obj(std::string_view);
  Obj(const Obj&) = default;
  Obj(Obj&&) noexcept = default;
  ~Obj() = default;

 public:
  constexpr auto vertices() const noexcept -> const vertices_type& {
    return vertices_;
  }

  constexpr auto indices() const noexcept -> const indices_type& {
    return indices_;
  }

  constexpr auto facets_count() const noexcept -> std::size_t {
    return facets_count_;
  }

 public:
  // coord code -- rotate around: 0 - X, 1 - Y, 2 - Z
  void RotateModel(int rot, Axis axis);
  void ScaleModel(float val);
  void MoveModel(float val, Axis axis);

 private:
  auto ParseVertex_(std::string_view) -> void;
  auto ParseIndex_(std::string_view) -> void;

 private:
  vertices_type vertices_;
  indices_type indices_;
  std::size_t facets_count_{0};
};
}  // namespace s21

#endif  // VIEWER_3D_V2_MODEL_OBJ_H_
