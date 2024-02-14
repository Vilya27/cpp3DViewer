#ifndef VIEWER_3D_V2_VIEW_MAINWINDOW_H_
#define VIEWER_3D_V2_VIEW_MAINWINDOW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "controller.h"
#include "gifimage/qgifimage.h"
#include "model.h"
#include "opengl_widget.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  void ConnectController(std::unique_ptr<Controller> c);
  OpenglWidget *GetScene();
  void ResetViewParams();
  void SaveSettings();
  void LoadSettings();
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
  std::unique_ptr<Controller> ctrl_;
  bool is_obj_loaded_2_ = false;
  float moving_x_ = 0, moving_y_ = 0, moving_z_ = 0, rotating_x_ = 0,
        rotating_y_ = 0, rotating_z_ = 0;
  int zooming_ = 100, count_clicks_ = 0;
  QString settings_file_;
  std::unique_ptr<QSettings> settings_;
  QVector<QImage> images_;
  std::unique_ptr<QTimer> gif_timer_;
  float time_val_ = 0;

 private:
  void GifSaving();
  void CreateScreen();
  void resizeEvent(QResizeEvent *ev);

 private slots:
  void on_button_file_clicked();
     void on_spinbox_move_x_valueChanged(double arg1);
     void on_spinbox_move_y_valueChanged(double arg1);
     void on_spinbox_move_z_valueChanged(double arg1);
     void on_spinbox_rotate_x_valueChanged(double arg1);
     void on_spinbox_rotate_y_valueChanged(double arg1);
     void on_spinbox_rotate_z_valueChanged(double arg1);
     void on_spinbox_scale_valueChanged(double arg1);
     void on_button_color_background_clicked();
     void on_button_color_edges_clicked();
  void on_button_color_vertex_clicked();
  void on_combobox_projection_type_activated(int index);
  void on_combobox_edges_type_activated(int index);
  void on_combobox_vertices_type_activated(int index);
  void on_spinbox_edges_thickness_valueChanged(double arg1);
  void on_spinbox_vertices_thickness_valueChanged(double arg1);
  void on_button_settings_save_clicked();
  void on_button_settings_load_clicked();
  void on_button_saving_clicked();
  void on_button_screencast_clicked();
};
}  // namespace s21
#endif  // VIEWER_3D_V2_VIEW_MAINWINDOW_H_
