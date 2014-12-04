QT += core gui opengl

TARGET = cs123-final
TEMPLATE = app

INCLUDEPATH += src
DEPENDPATH += src

unix:!macx: LIBS += -lGLEW

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    shape/Quad.cpp \
    src/DataBinding.cpp \
    src/Settings.cpp \
    src/Shader.cpp \
    shape/Sphere.cpp \
    src/glwidget.cpp \
    camera/CamtransCamera.cpp \
    helper/utils.cpp \
    shape/Shape.cpp \
    scene/Basketball.cpp \
    shape/Cube.cpp \
    shape/Cylinder.cpp

HEADERS += \
    src/mainwindow.h \
    shape/Quad.h \
    src/DataBinding.h \
    src/Settings.h \
    src/Shader.h \
    shape/Sphere.h \
    camera/Camera.h \
    src/glwidget.h \
    camera/CamtransCamera.h \
    helper/utils.h \
    shape/Shape.h \
    scene/Basketball.h \
    helper/Physics.h \
    scene/SceneData.h \
    shape/Cube.h \
    shape/Cylinder.h

FORMS += src/mainwindow.ui

DEFINES += GLEW_STATIC

OTHER_FILES += \
    ADS/ADS.frag \
    ADS/ADS.vert
