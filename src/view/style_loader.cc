#include "style_loader.h"

void s21::StyleLoader::Attach(void) { watcher_.addPath(filename_); }
void s21::StyleLoader::SetAppStyleSheet() {
  QFile file(filename_);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Cannot open stylesheet file " << filename_;
    return;
  }
  QString stylesheet = QString::fromUtf8(file.readAll());
  qApp->setStyleSheet(stylesheet);
  file.close();
  watcher_.addPath(filename_);
}

QString s21::StyleLoader::DefaultStyleFile() {
  QString pathToStylesFile = QString(PROJECT_DIR) + QString("/style.qss");
  return pathToStylesFile;
}

s21::StyleLoader::StyleLoader(QObject* parent, const QString& filename)
    : QObject(parent), filename_(filename) {
  QObject::connect(&watcher_, SIGNAL(fileChanged(QString)), this,
                   SLOT(SetAppStyleSheet()));
  SetAppStyleSheet();
}
