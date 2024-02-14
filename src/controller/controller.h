#ifndef VIEWER_3D_V2_CONTROLLER_CONTROLLER_H_
#define VIEWER_3D_V2_CONTROLLER_CONTROLLER_H_

#include <QColorDialog>
#include <memory>
#include <string_view>

#include "model.h"

namespace s21 {

class Observer {
 public:
  virtual ~Observer() = default;
  virtual void HandleUpdate(const std::vector<float>& vertices,
                            const std::vector<unsigned int>& indices) = 0;
};

class Controller {
 public:
  Controller() = default;
  Controller(std::unique_ptr<Obj> obj) : obj_(std::move(obj)) {}
  Controller(const Controller&) = delete;
  Controller(Controller&&) = default;
  ~Controller() = default;

 public:
  auto operator=(const Controller&) -> Controller& = delete;
  auto operator=(Controller&&) -> Controller& = default;

  // for observer pattern
  void AddObserver(std::unique_ptr<Observer> observer) {
    observers_.emplace_back(std::move(observer));
  }

  void NotifyObservers() {
    for (const auto& observer : observers_) {
      observer->HandleUpdate(obj_->vertices(), obj_->indices());
    }
  }

 public:
  inline auto vertices() const noexcept -> const Obj::vertices_type& {
    return obj_->vertices();
  }

  inline auto indices() const noexcept -> const Obj::indices_type& {
    return obj_->indices();
  }

  inline auto facets_count() const noexcept -> std::size_t {
    return obj_->facets_count();
  }

  inline auto LoadNew(std::string_view filepath) -> void {
    auto new_obj = std::make_unique<Obj>(filepath);
    obj_ = std::move(new_obj);
  }

  inline auto RotateModel(float val, Axis axis) -> void {
    obj_->RotateModel(val, axis);
  }

  inline auto ScaleModel(float val) -> void { obj_->ScaleModel(val); }

  inline auto MoveModel(float val, Axis axis) -> void {
    obj_->MoveModel(val, axis);
  }

 private:
  std::unique_ptr<s21::Obj> obj_;
  std::vector<std::unique_ptr<Observer>> observers_;
};

}  // namespace s21

#endif  // VIEWER_3D_V2_CONTROLLER_CONTROLLER_H_
