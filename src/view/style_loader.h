#ifndef VIEWER_3D_V2_VIEW_STYLELOADER_H_
#define VIEWER_3D_V2_VIEW_STYLELOADER_H_

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileSystemWatcher>
#include <QKeyEvent>
#include <QKeySequence>
#include <QObject>

namespace s21 {
class StyleLoader : public QObject {
  Q_OBJECT
 public:
  StyleLoader(QObject* parent, const QString& filename = DefaultStyleFile());
  void Attach(void);
  static QString DefaultStyleFile();

 private:
  QString filename_;
  QFileSystemWatcher watcher_;
 private slots:
  void SetAppStyleSheet();
};
}  // namespace s21

#endif  // VIEWER_3D_V2_VIEW_STYLELOADER_H_
