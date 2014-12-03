QT += core gui opengl

TARGET = cs123-final
TEMPLATE = app

INCLUDEPATH += src
DEPENDPATH += src

unix:!macx: LIBS += -lGLEW

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/Quad.cpp \
    src/DataBinding.cpp \
    src/Settings.cpp \
    src/Shader.cpp \
    src/Sphere.cpp \
    src/glwidget.cpp \
    src/CamtransCamera.cpp \
    src/utils.cpp \
    src/Shape.cpp \
    src/Basketball.cpp

HEADERS += \
    src/mainwindow.h \
    src/Quad.h \
    src/DataBinding.h \
    src/Settings.h \
    src/Shader.h \
    src/Sphere.h \
    src/Camera.h \
    src/glwidget.h \
    src/CamtransCamera.h \
    src/utils.h \
    src/Shape.h \
    src/Basketball.h \
    src/Physics.h

FORMS += src/mainwindow.ui

DEFINES += GLEW_STATIC

OTHER_FILES += \
    ADS/ADS.frag \
    ADS/ADS.vert
