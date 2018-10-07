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
    ECS/Managers/entitymanager.cpp \
    ECS/component.cpp \
    ECS/entity.cpp \
    ECS/Managers/basecomponentmanager.cpp \
    ECS/Handles/entityhandle.cpp \
    ECS/component_mask.cpp \
    meshfarm.cpp \
    ECS/Systems/rendersystem.cpp \
    octahedron.cpp \
    mesh.cpp \
    model.cpp \
    texture.cpp \
    ECS/Components/material_component.cpp \
    ECS/Components/mesh_component.cpp \
    ECS/Components/movement_component.cpp \
    ECS/Components/transform_component.cpp \
    ECS/Components/light_component.cpp \
    ECS/Components/directionallight_component.cpp \
    ECS/Components/pointlight_component.cpp \
    ECS/Components/spotlight_component.cpp \
    ECS/Systems/directionallightsystem.cpp \
    ECS/Systems/pointlightsystem.cpp \
    ECS/Systems/spotlightsystem.cpp \
    paths.cpp \
    objectfarm.cpp \
    colors.cpp

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
    ECS/Managers/componentmanager.h \
    ECS/Handles/entityhandle.h \
    world.h \
    ECS/Handles/componenthandle.h \
    ECS/system.h \
    ECS/Systems/movementsystem.h \
    ECS/Managers/entitymanager.h \
    ECS/component.h \
    ECS/Managers/basecomponentmanager.h \
    ECS/Components/movement_component.h \
    ECS/Components/transform_component.h \
    ECS/Components/mesh_component.h \
    ECS/Components/material_component.h \
    ECS/component_mask.h \
    meshfarm.h \
    ECS/Systems/rendersystem.h \
    octahedron.h \
    mesh.h \
    model.h \
    texture.h \
    ECS/Components/light_component.h \
    ECS/Components/pointlight_component.h \
    ECS/Components/spotlight_component.h \
    ECS/Components/directionallight_component.h \
    ECS/Systems/directionallightsystem.h \
    ECS/Systems/pointlightsystem.h \
    ECS/Systems/spotlightsystem.h \
    objectfarm.h \
    colors.h

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

DISTFILES += \
    Shaders/ColorObject.frag \
    Shaders/LightObject.frag \
    Shaders/LightSource.frag \
    Shaders/TextureObject.frag \
    Shaders/VertexShader.vert
