QT       += core gui openglwidgets
QMAKE_CXXFLAGS += -Wno-deprecated

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(deps/QtGifImage/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += PROJECT_DIR=\\\"$$PWD\\\"

INCLUDEPATH += deps/QtGifImage/src controller model

SOURCES += \
    view/main.cc \
    view/mainwindow.cc \
    view/style_loader.cc \
    view/opengl_widget.cc \
    model/obj.cc \
    model/utils.cc \

HEADERS += \
    view/mainwindow.h \
    view/style_loader.h \
    view/opengl_widget.h \
    controller/controller.h \
    model/obj.h \
    model/utils.h \
    model/model.h \
    deps/QtGifImage/src/gifimage/qgifimage.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc
DISTFILES += \
    objects/cube.obj

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
