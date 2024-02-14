#include <gtest/gtest.h>

#include <iostream>

#include "fixtures.h"
#include "model.h"

static auto AssertDoubleEq(double lhs, double rhs, double epsilon = 0.000001f) {
  ASSERT_TRUE(std::abs(lhs - rhs) <= epsilon);
}

TEST(Obj, Constructor) {
  auto obj = std::make_unique<s21::Obj>("objects/cube.obj");

  auto obj_vertices = obj->vertices();
  auto obj_indices = obj->indices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], VERTICES[i]);

  ASSERT_EQ(obj_indices.size(), 72);
  for (size_t i = 0; i < obj_indices.size(); ++i)
    ASSERT_EQ(obj_indices[i], INDICES[i]);

  ASSERT_EQ(obj->facets_count(), 36);
}

TEST(Obj, MoveConstructor) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  auto obj_vertices = obj->vertices();
  auto obj_indices = obj->indices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], VERTICES[i]);

  ASSERT_EQ(obj_indices.size(), 72);
  for (size_t i = 0; i < obj_indices.size(); ++i)
    ASSERT_EQ(obj_indices[i], INDICES[i]);

  ASSERT_EQ(obj->facets_count(), 36);
}

TEST(Obj, ScaleModel) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  obj->ScaleModel(2);

  auto obj_vertices = obj->vertices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], DOUBLE_SCALE_VERTICES[i]);
}

TEST(Obj, MoveModelX) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  obj->MoveModel(2, s21::Axis::X);

  auto obj_vertices = obj->vertices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], X_MOVED_VERTICES[i]);
}

TEST(Obj, MoveModelY) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  obj->MoveModel(2, s21::Axis::Y);

  auto obj_vertices = obj->vertices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], Y_MOVED_VERTICES[i]);
}

TEST(Obj, MoveModelZ) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  obj->MoveModel(2, s21::Axis::Z);

  auto obj_vertices = obj->vertices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], Z_MOVED_VERTICES[i]);
}

TEST(Obj, RotateModelX) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  obj->RotateModel(2, s21::Axis::X);

  auto obj_vertices = obj->vertices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], X_ROTATED_VERTICES[i]);
}

TEST(Obj, RotateModelY) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  obj->RotateModel(2, s21::Axis::Y);

  auto obj_vertices = obj->vertices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], Y_ROTATED_VERTICES[i]);
}

TEST(Obj, RotateModelZ) {
  std::unique_ptr<s21::Obj> obj =
      std::make_unique<s21::Obj>("objects/cube.obj");

  obj->RotateModel(2, s21::Axis::Z);

  auto obj_vertices = obj->vertices();

  ASSERT_EQ(obj_vertices.size(), 24);
  for (size_t i = 0; i < obj_vertices.size(); ++i)
    AssertDoubleEq(obj_vertices[i], Z_ROTATED_VERTICES[i]);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
