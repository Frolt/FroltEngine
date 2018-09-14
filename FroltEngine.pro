#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T19:54:40
#
#-------------------------------------------------

# Settings
# --------------------------------------------------------------
QT += core gui widgets
TARGET = FroltEngine
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++17
QMAKE_CXXFLAGS += /std:c++17
# --------------------------------------------------------------

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    viewport.cpp \
    entity.cpp \
    inputcomponent.cpp \
    playerinputcomponent.cpp \
    a_math.cpp \
    material.cpp \
    mesh.cpp \
    model.cpp \
    shader.cpp \
    stb_image.cpp \
    texture.cpp \
    vec2.cpp \
    vec3.cpp \
    vec4.cpp \
    vertex.cpp \
    engine.cpp

HEADERS += \
    mainwindow.h \
    viewport.h \
    entity.h \
    inputcomponent.h \
    playerinputcomponent.h \
    a_math.h \
    gl_constants.h \
    material.h \
    math_constants.h \
    matrix.h \
    mesh.h \
    model.h \
    shader.h \
    stb_image.h \
    texture.h \
    vec2.h \
    vec3.h \
    vec4.h \
    vertex.h \
    engine.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
# --------------------------------------------------------------
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
# --------------------------------------------------------------

# External libraries
# --------------------------------------------------------------
unix|win32: LIBS += -L$$PWD/Libraries/libs/ -lassimp-vc140-mt

INCLUDEPATH += $$PWD/Libraries/Include
DEPENDPATH += $$PWD/Libraries/Include

unix|win32: LIBS += -L$$PWD/Libraries/libs/ -lglm_static

INCLUDEPATH += $$PWD/Libraries/Include
DEPENDPATH += $$PWD/Libraries/Include
# --------------------------------------------------------------
