#include <QApplication>

#include "controller.h"
#include "mainwindow.h"
#include "style_loader.h"

class GlObserver : public s21::Observer {
 public:
  GlObserver(s21::OpenglWidget* scene) {
    if (scene == nullptr)
      throw std::invalid_argument("OpenGlWidget scene is nullptr");

    scene_ = scene;
  }

  virtual void HandleUpdate(const std::vector<float>& vertices,
                            const std::vector<unsigned int>& indices) {
    scene_->HandleUpdate(vertices, indices);
  }

 private:
  s21::OpenglWidget* scene_ = nullptr;
};

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow w;
  auto st = s21::StyleLoader(&w);
  auto ctrl = std::make_unique<s21::Controller>();

  ctrl->AddObserver(std::make_unique<GlObserver>(w.GetScene()));
  w.ConnectController(std::move(ctrl));
  st.Attach();
  w.show();

  return a.exec();
}
