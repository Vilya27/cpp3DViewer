#ifndef VIEWER_3D_V2_VIEW_OPENGL_WIDGET_H_
#define VIEWER_3D_V2_VIEW_OPENGL_WIDGET_H_

#include <QColorDialog>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <iostream>

#include "controller.h"

namespace s21 {

class OpenglWidget : public QOpenGLWidget,
                     public QOpenGLFunctions,
                     public Observer {
  Q_OBJECT

 public:
  OpenglWidget(QWidget *parent = nullptr);
  void SetParameter(const std::string &parameter, QVariant value);
  QVariant GetParameter(const std::string &parameter);
  virtual void HandleUpdate(const std::vector<float> &vertices,
                            const std::vector<unsigned int> &indices) override;

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void wheelEvent(QWheelEvent *ev) override;

 private:
  void DrawObjModel();

 private:
  bool is_obj_loaded_ = false, is_ortho_ = false;
  std::vector<float> vertices_in_scene_;
  std::vector<unsigned int> indices_in_scene_;
  QColor back_color_, line_color_, point_color_;
  int line_type_, point_type_, line_thickness_, point_thickness_;
};

}  // namespace s21

#endif  // VIEWER_3D_V2_VIEW_OPENGL_WIDGET_H_
