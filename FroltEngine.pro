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

INCLUDEPATH += $$PWD/Libraries
INCLUDEPATH += $$PWD/Math


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    viewport.cpp \
    shader.cpp \
    vertex.cpp \
    engine.cpp \
    Math/a_math.cpp \
    Math/vec2.cpp \
    Math/vec3.cpp \
    Math/vec4.cpp \
    LAS/lasreader.cpp \
    Libraries/Include/stb_image.cpp \
    world.cpp \
    ECS/system.cpp \
    ECS/Systems/movementsystem.cpp \
    ECS/entitymanager.cpp

HEADERS += \
    mainwindow.h \
    viewport.h \
    shader.h \
    vertex.h \
    engine.h \
    Math/a_math.h \
    Math/math_constants.h \
    Math/matrix.h \
    Math/vec2.h \
    Math/vec3.h \
    Math/vec4.h \
    LAS/headerstock.h \
    LAS/lasreader.h \
    Libraries/Include/stb_image.h \
    enums.h \
    paths.h \
    inputstate.h \
    ECS/entity.h \
    ECS/componentmanager.h \
    ECS/entityhandle.h \
    world.h \
    ECS/componenthandle.h \
    ECS/wrappers.h \
    ECS/system.h \
    ECS/Components/transformcomponent.h \
    ECS/Components/movementcomponent.h \
    ECS/Systems/movementsystem.h \
    ECS/entitymanager.h \
    ECS/component.h \
    ECS/basecomponentmanager.h

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
