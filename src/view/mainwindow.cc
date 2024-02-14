#include "mainwindow.h"

#include <QFileDialog>
#include <iostream>

#include "../controller/controller.h"
#include "ui_mainwindow.h"

using s21::OpenglWidget;

s21::MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      settings_file_(QApplication::applicationDirPath() + "/3DViewer.ini"),
      settings_(
          std::make_unique<QSettings>(settings_file_, QSettings::IniFormat)),
      gif_timer_(std::make_unique<QTimer>(nullptr)) {
  ui_->setupUi(this);
  ui_->tool_box->setCurrentIndex(0);
  ui_->text_filename->setWordWrap(true);
  ui_->label_gif_timer->setVisible(false);
  connect(gif_timer_.get(), &QTimer::timeout, this,
          &s21::MainWindow::CreateScreen);
  setWindowTitle("3DViewer by taniakia vivienne mortalan");
  setWindowIcon(QIcon("://view/images/icon-3d.png"));
  int wi = QApplication::primaryScreen()->size().width();

  if (wi < 1200) {
    resize(800, 600);
  } else if (wi < 1600) {
    resize(1000, 620);
  } else {
    resize(1200, 820);
  }
}

s21::MainWindow::~MainWindow() { delete ui_; }

void s21::MainWindow::ConnectController(std::unique_ptr<Controller> c) {
  ctrl_ = std::move(c);
}

OpenglWidget* s21::MainWindow::GetScene() { return ui_->openGLWidget; }

void s21::MainWindow::on_button_file_clicked() {
  ResetViewParams();
  QString file =
      QFileDialog::getOpenFileName(this, "Выберите файл", ".", tr(" (*.obj)"));

  if (file.isEmpty()) return;

  ctrl_->LoadNew(file.toStdString());
  int height = ui_->text_filename->geometry().height();
  QString filename_release = QFileInfo(file).fileName();
  int length = filename_release.length();
  if (length > 35) {
    for (int i = 0, n = 0; i < length/35; i++) {
        n += 35;
        filename_release.insert(n, " ");
    }
  }
  ui_->text_filename->setText("Название файла:  " + filename_release);
  if (height > ui_->text_filename->sizeHint().height()) {
      height = ui_->text_filename->sizeHint().height();
      ui_->text_filename->setMaximumHeight(height);
  }
  else if (height < ui_->text_filename->sizeHint().height()) {
      height = ui_->text_filename->sizeHint().height();
      ui_->text_filename->setMaximumHeight(height);
  }
  ui_->label_count_vertex->setText(QString::asprintf(
      "Количество вершин: %ld", ctrl_->vertices().size() / 3));
  ui_->label_count_edges->setText(
      QString::asprintf("Количество рёбер: %ld", ctrl_->facets_count()));
  ui_->openGLWidget->HandleUpdate(ctrl_->vertices(), ctrl_->indices());
  is_obj_loaded_2_ = true;
}

void s21::MainWindow::ResetViewParams() {
  moving_x_ = moving_y_ = moving_z_ = rotating_x_ = rotating_y_ = rotating_z_ =
      0;
  ui_->spinbox_move_x->setValue(0);
  ui_->spinbox_move_y->setValue(0);
  ui_->spinbox_move_z->setValue(0);
  ui_->spinbox_rotate_x->setValue(0);
  ui_->spinbox_rotate_y->setValue(0);
  ui_->spinbox_rotate_z->setValue(0);
  ui_->spinbox_scale->setValue(100);
}

void s21::MainWindow::on_spinbox_move_x_valueChanged(double arg1) {
  if (is_obj_loaded_2_) {
    ctrl_->MoveModel(float(arg1) - moving_x_, Axis::X);
    moving_x_ = float(arg1);
    ctrl_->NotifyObservers();
  }
}

void s21::MainWindow::on_spinbox_move_y_valueChanged(double arg1) {
  if (is_obj_loaded_2_) {
    ctrl_->MoveModel(float(arg1) - moving_y_, Axis::Y);
    moving_y_ = float(arg1);
    ctrl_->NotifyObservers();
  }
}

void s21::MainWindow::on_spinbox_move_z_valueChanged(double arg1) {
  if (is_obj_loaded_2_) {
    ctrl_->MoveModel(float(arg1) - moving_z_, Axis::Z);
    moving_z_ = float(arg1);
    ctrl_->NotifyObservers();
  }
}

void s21::MainWindow::on_spinbox_rotate_x_valueChanged(double arg1) {
  if (is_obj_loaded_2_) {
    ctrl_->RotateModel(float(arg1) - rotating_x_, Axis::X);
    rotating_x_ = float(arg1);
    ctrl_->NotifyObservers();
  }
}

void s21::MainWindow::on_spinbox_rotate_y_valueChanged(double arg1) {
  if (is_obj_loaded_2_) {
    ctrl_->RotateModel(float(arg1) - rotating_y_, Axis::Y);
    rotating_y_ = float(arg1);
    ctrl_->NotifyObservers();
  }
}

void s21::MainWindow::on_spinbox_rotate_z_valueChanged(double arg1) {
  if (is_obj_loaded_2_) {
    ctrl_->RotateModel(float(arg1) - rotating_z_, Axis::Z);
    rotating_z_ = float(arg1);
    ctrl_->NotifyObservers();
  }
}

void s21::MainWindow::on_spinbox_scale_valueChanged(double arg1) {
  if (is_obj_loaded_2_) {
    float mult = arg1 / (float)zooming_;
    ctrl_->ScaleModel(mult);
    zooming_ = arg1;
    ctrl_->NotifyObservers();
  }
}

void s21::MainWindow::on_button_color_background_clicked() {
  QColor color =  QColorDialog::getColor(Qt::gray);
  if (color.isValid()) {
    ui_->openGLWidget->SetParameter("back_color_", color);
  } else return;
}

void s21::MainWindow::on_button_color_edges_clicked() {
  QColor color =  QColorDialog::getColor(Qt::gray);
  if (color.isValid()) {
    ui_->openGLWidget->SetParameter("line_color_", color);
  } else return;
}

void s21::MainWindow::on_button_color_vertex_clicked() {
  QColor color =  QColorDialog::getColor(Qt::gray);
  if (color.isValid()) {
    ui_->openGLWidget->SetParameter("point_color_", color);
  } else return;
}

void s21::MainWindow::on_combobox_projection_type_activated(int index) {
  ui_->openGLWidget->SetParameter("proj_type_", index);
}

void s21::MainWindow::on_combobox_edges_type_activated(int index) {
  ui_->openGLWidget->SetParameter("line_type_", index);
}

void s21::MainWindow::on_combobox_vertices_type_activated(int index) {
  ui_->openGLWidget->SetParameter("point_type_", index);
}

void s21::MainWindow::on_spinbox_edges_thickness_valueChanged(double arg1) {
  ui_->openGLWidget->SetParameter("line_thickness_", arg1);
}

void s21::MainWindow::on_spinbox_vertices_thickness_valueChanged(double arg1) {
  ui_->openGLWidget->SetParameter("point_thickness_", arg1);
}

void s21::MainWindow::on_button_settings_load_clicked() { LoadSettings(); }

void s21::MainWindow::on_button_settings_save_clicked() { SaveSettings(); }

void s21::MainWindow::SaveSettings() {
  settings_->setValue("proj_type_",
                      ui_->openGLWidget->GetParameter("proj_type_").toInt());
  settings_->setValue("line_type",
                      ui_->openGLWidget->GetParameter("line_type").toInt());
  settings_->setValue("line_thickness_",
                      ui_->openGLWidget->GetParameter("line_thickness_").toInt());
  settings_->setValue("point_type_",
                      ui_->openGLWidget->GetParameter("point_type_").toInt());
  settings_->setValue(
      "point_thickness_",
      ui_->openGLWidget->GetParameter("point_thickness_").toInt());
  settings_->setValue(
      "back_color_",
      ui_->openGLWidget->GetParameter("back_color_").value<QColor>());
  settings_->setValue(
      "lineColor",
      ui_->openGLWidget->GetParameter("lineColor").value<QColor>());
  settings_->setValue(
      "point_color_",
      ui_->openGLWidget->GetParameter("point_color_").value<QColor>());
}

void s21::MainWindow::LoadSettings() {
  ui_->openGLWidget->SetParameter("proj_type_",
                                  settings_->value("proj_type_").toInt());
  ui_->openGLWidget->SetParameter("lineType",
                                  settings_->value("lineType").toInt());
  ui_->openGLWidget->SetParameter("line_thickness_",
                                  settings_->value("line_thickness_").toInt());
  ui_->openGLWidget->SetParameter("point_type_",
                                  settings_->value("point_type_").toInt());
  ui_->openGLWidget->SetParameter("point_thickness_",
                                  settings_->value("point_thickness_").toInt());
  ui_->openGLWidget->SetParameter(
      "back_color_", settings_->value("back_color_").value<QColor>());
  ui_->openGLWidget->SetParameter(
      "lineColor", settings_->value("lineColor").value<QColor>());
  ui_->openGLWidget->SetParameter(
      "point_color_", settings_->value("point_color_").value<QColor>());

  ui_->combobox_edges_type->setCurrentIndex(settings_->value("lineType").toInt());
  ui_->combobox_projection_type->setCurrentIndex(
      settings_->value("proj_type_").toInt());
  ui_->combobox_vertices_type->setCurrentIndex(
      settings_->value("point_type_").toInt());
  ui_->spinbox_vertices_thickness->setValue(
      settings_->value("point_thickness_").toInt());
  ui_->spinbox_edges_thickness->setValue(
      settings_->value("line_thickness_").toInt());
}

void s21::MainWindow::on_button_saving_clicked() {
  QFileDialog file_dialog_photo(this);
  QString f_name_photo = file_dialog_photo.getSaveFileName(
      this, "Save as...", QDir::currentPath(), "BMP (*.bmp);; JPEG (*.jpeg)");
  QFile file(f_name_photo);
  file.open(QIODevice::WriteOnly);
  QRect rect(0, 0, ui_->openGLWidget->width(), ui_->openGLWidget->height());
  QPixmap pixmap = ui_->openGLWidget->grab(rect);
  pixmap.copy(rect);
  pixmap.toImage().save(&file, "jpg");
  QString q_command_line = "open " + f_name_photo;
  QByteArray temp = q_command_line.toLocal8Bit();
  char* command_line = temp.data();
  system(command_line);
}

void s21::MainWindow::on_button_screencast_clicked() {
  gif_timer_->start(100);
  count_clicks_++;
  CreateScreen();
}

void s21::MainWindow::GifSaving() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save screenshot"), "",
      tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
  QGifImage gif(QSize(640, 480));

  gif.setDefaultTransparentColor(Qt::black);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator img = images_.begin(); img != images_.end();
       ++img) {
    gif.addFrame(*img);
  }
  if (!fileName.isEmpty())
  {
    gif.save(fileName);
    images_.clear();
    ui_->label_gif_timer->clear();
    time_val_ = 0;
  }
}

void s21::MainWindow::CreateScreen() {
  if ((count_clicks_ % 2) != 0) {
    QSize pic_size(100, 100);
    QPixmap pixmap("://view/images/icon-pause.png");
    pixmap = pixmap.scaled(pic_size, Qt::KeepAspectRatio);
    QIcon button_icon (pixmap);
    ui_->button_screencast->setIcon(button_icon);
    ui_->button_screencast->setIconSize(pixmap.rect().size());
    ui_->button_screencast->setText("");
    ui_->label_gif_timer->setVisible(true);
    images_.push_back(ui_->openGLWidget->grab().toImage().scaled(
        640, 480, Qt::IgnoreAspectRatio));
    time_val_ += 0.1;
    ui_->label_gif_timer->setText("Таймер: " + QString::number(time_val_));
  } else {
    gif_timer_->stop();
    GifSaving();
    ui_->label_gif_timer->setVisible(false);
    ui_->button_screencast->setIcon(QIcon());
    ui_->button_screencast->setText("Screencast");
  }
}

void s21::MainWindow::resizeEvent(QResizeEvent *ev) {
  int small = 0, medium = 0, large = 0;
  int wi = this->frameGeometry().width();
  if (wi <= 1000) { small = 12; medium = 14; large = 21; }
  else if (wi <= 1600) {  small = 18; medium = 20; large = 30; }
  else { small = 20; medium = 24; large = 36; }

  if (ui_->text_filename->maximumHeight() == 16777215) {
    ui_->text_filename->setMaximumHeight(35);
  } else if (ui_->text_filename->maximumHeight() > 35 || ui_->text_filename->sizeHint().height() > 35) {
    wi = ui_->text_filename->sizeHint().height();
    ui_->text_filename->setMaximumHeight(wi);
  }
  this->setStyleSheet(QString("QLabel, QTextEdit, QComboBox::item,"
                              "QGroupBox#groupbox_edges_type {"
                              "font-size: %1px;"
                              "}"
                              "QGroupBox, QDoubleSpinBox, QPushButton,"
                              "QComboBox {"
                              "font-size: %2px;"
                              "}"
                              "QPushButton#button_screencast, QPushButton#button_saving, QLabel#label_gif_timer,"
                              "QToolBox::tab {"
                              "font-size: %3px;"
                              "}")
                          .arg(small)
                          .arg(medium)
                          .arg(large)
                      );
}
