#include "opengl_widget.h"

s21::OpenglWidget::OpenglWidget(QWidget *parent) : QOpenGLWidget{parent} {
  back_color_ = QColor(Qt::black);
  line_color_ = QColor(Qt::white);
  point_color_ = QColor(Qt::blue);
  line_type_ = point_type_ = 0;
  line_thickness_ = point_thickness_ = 1;
  setMouseTracking(true);
}

void s21::OpenglWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(back_color_.redF(), back_color_.greenF(), back_color_.blueF(),
               1);
  glEnable(GL_DEPTH_TEST);
}

void s21::OpenglWidget::paintGL() {
  glClearColor(back_color_.redF(), back_color_.greenF(), back_color_.blueF(),
               1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (is_obj_loaded_) {
    DrawObjModel();
  }
}

void s21::OpenglWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void s21::OpenglWidget::wheelEvent(QWheelEvent *ev) {}

void s21::OpenglWidget::DrawObjModel() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (!is_ortho_) {
    glFrustum(-5, 5, -5, 5, 5, 100);
    glTranslated(0, 0, -10);
  } else {
    glOrtho(-10, 10, -10, 10, 2, 100);
    glTranslatef(0, 0, -5);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glVertexPointer(3, GL_FLOAT, 0, vertices_in_scene_.data());
  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(line_thickness_);
  glColor3f(line_color_.redF(), line_color_.greenF(), line_color_.blueF());
  if (line_type_) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0X0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glDrawElements(GL_LINES, indices_in_scene_.size(), GL_UNSIGNED_INT,
                 indices_in_scene_.data());
  glDisableClientState(GL_VERTEX_ARRAY);

  if (point_type_ != 0) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_POINT_SMOOTH);
    glColor3f(point_color_.redF(), point_color_.greenF(), point_color_.blueF());
    if (point_type_ == 2) glDisable(GL_POINT_SMOOTH);
    glPointSize(point_thickness_);
    glDrawArrays(GL_POINTS, 0, vertices_in_scene_.size() / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_POINT_SMOOTH);
  }
}

void s21::OpenglWidget::SetParameter(const std::string &parameter,
                                     QVariant value) {
  if (parameter == "proj_type_") {
    is_ortho_ = value.toInt();
  } else if (parameter == "line_type_") {
    line_type_ = value.toInt();
  } else if (parameter == "point_type_") {
    point_type_ = value.toInt();
  } else if (parameter == "back_color_") {
    back_color_ = value.value<QColor>();
  } else if (parameter == "line_color_") {
    line_color_ = value.value<QColor>();
  } else if (parameter == "point_color_") {
    point_color_ = value.value<QColor>();
  } else if (parameter == "line_thickness_") {
    line_thickness_ = value.toInt();
  } else if (parameter == "point_thickness_") {
    point_thickness_ = value.toInt();
  }
  update();
}

QVariant s21::OpenglWidget::GetParameter(const std::string &parameter) {
  if (parameter == "proj_type_") {
    return QVariant::fromValue(is_ortho_);
  } else if (parameter == "line_type_") {
    return QVariant::fromValue(line_type_);
  } else if (parameter == "point_type_") {
    return QVariant::fromValue(point_type_);
  } else if (parameter == "back_color_") {
    return QVariant::fromValue(back_color_);
  } else if (parameter == "line_color_") {
    return QVariant::fromValue(line_color_);
  } else if (parameter == "point_color_") {
    return QVariant::fromValue(point_color_);
  } else if (parameter == "line_thickness_") {
    return QVariant::fromValue(line_thickness_);
  } else if (parameter == "point_thickness_") {
    return QVariant::fromValue(point_thickness_);
  } else {
    return QVariant();
  }
}

void s21::OpenglWidget::HandleUpdate(const std::vector<float> &v,
                                     const std::vector<unsigned int> &i) {
  vertices_in_scene_.clear();
  indices_in_scene_.clear();
  vertices_in_scene_ = v;
  indices_in_scene_ = i;
  is_obj_loaded_ = true;
  update();
}
