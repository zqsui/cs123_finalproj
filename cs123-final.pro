QT += core gui opengl

TARGET = 3DTransformations_lab
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
    src/glwidget.cpp

HEADERS += \
    src/mainwindow.h \
    src/Quad.h \
    src/DataBinding.h \
    src/Settings.h \
    src/Shader.h \
    src/Sphere.h \
    src/Camera.h \
    src/glwidget.h

FORMS += src/mainwindow.ui

DEFINES += GLEW_STATIC

OTHER_FILES += \
    ADS/ADS.frag \
    ADS/ADS.vert
