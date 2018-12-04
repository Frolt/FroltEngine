#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T19:54:40
#
#-------------------------------------------------

# Settings
# --------------------------------------------------------------
CONFIG += console
QT += core gui widgets
TARGET = FroltEngine
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
#CONFIG += c++17
QMAKE_CXXFLAGS += /std:c++17

# Includes
# --------------------------------------------------------------
INCLUDEPATH += $$PWD/Libraries
INCLUDEPATH += $$PWD/Math
INCLUDEPATH += $$PWD/Factories

# Source files
# --------------------------------------------------------------
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
    octahedron.cpp \
    mesh.cpp \
    texture.cpp \
    mathterraingenerator.cpp \
    lazterraingenerator.cpp \
    Factories/materialfactory.cpp \
    modelloader.cpp \
    Factories/meshfactory.cpp \
    Factories/entityfactory.cpp \
    ECS/system.cpp \
    ECS/Systems/movementsystem.cpp \
    ECS/Managers/entitymanager.cpp \
    ECS/component.cpp \
    ECS/entity.cpp \
    ECS/Managers/basecomponentmanager.cpp \
    ECS/Handles/entityhandle.cpp \
    ECS/component_mask.cpp \
    ECS/Systems/rendersystem.cpp \
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
    ECS/Systems/playersystem.cpp \
    ECS/Systems/freecamerasystem.cpp \
    ECS/Components/input_component.cpp \
    ECS/Components/camera_component.cpp \
    ECS/Components/free_camera_component.cpp \
    ECS/Components/terrain_component.cpp \
    ECS/Systems/modelrendersystem.cpp \
    ECS/Components/model_component.cpp \
    ECS/Systems/physicssystem.cpp \
    ECS/Components/physics_component.cpp \
    ECS/Components/bspline_component.cpp \
    ECS/Systems/aisystem.cpp \
    ECS/Components/collision_component.cpp \
    ECS/Systems/collisionsystem.cpp \
    ECS/Systems/combatsystem.cpp \
    EventSystem/basememberfunctionhandler.cpp \
    EventSystem/collisionevent.cpp \
    EventSystem/event.cpp \
    EventSystem/eventhandler.cpp \
    ECS/Components/player_component.cpp \
    ECS/Components/ai_component.cpp \
    ECS/Systems/thirdpersoncamerasystem.cpp \
    ECS/Components/third_person_camera_component.cpp \
    ECS/Components/skybox_component.cpp \
    ECS/Systems/skyboxsystem.cpp \
    cubemap.cpp \
    ECS/component.cpp \
    EventSystem/spherecollisionevent.cpp

# Header files
# --------------------------------------------------------------
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
    inputstate.h \
    ECS/entity.h \
    ECS/Managers/componentmanager.h \
    ECS/Handles/entityhandle.h \
    world.h \
    ECS/Handles/componenthandle.h \
    ECS/system.h \
    ECS/Systems/movementsystem.h \
    ECS/Managers/entitymanager.h \
    ECS/Managers/basecomponentmanager.h \
    ECS/Components/movement_component.h \
    ECS/Components/transform_component.h \
    ECS/Components/mesh_component.h \
    ECS/Components/material_component.h \
    ECS/component_mask.h \
    ECS/Systems/rendersystem.h \
    octahedron.h \
    mesh.h \
    texture.h \
    ECS/Components/light_component.h \
    ECS/Components/pointlight_component.h \
    ECS/Components/spotlight_component.h \
    ECS/Components/directionallight_component.h \
    ECS/Systems/directionallightsystem.h \
    ECS/Systems/pointlightsystem.h \
    ECS/Systems/spotlightsystem.h \
    Factories/entityfactory.h \
    Factories/meshfactory.h \
    ECS/Systems/playersystem.h \
    ECS/Systems/freecamerasystem.h \
    ECS/Components/free_camera_component.h \
    ECS/Components/camera_component.h \
    ECS/Components/input_component.h \
    mathterraingenerator.h \
    ECS/Components/terrain_component.h \
    lazterraingenerator.h \
    Factories/materialfactory.h \
    modelloader.h \
    ECS/Systems/modelrendersystem.h \
    ECS/Components/model_component.h \
    ECS/Systems/physicssystem.h \
    ECS/Components/physics_component.h \
    ECS/Components/bspline_component.h \
    ECS/Systems/aisystem.h \
    ECS/Components/collision_component.h \
    ECS/Systems/collisionsystem.h \
    EventSystem/event.h \
    EventSystem/collisionevent.h \
    ECS/Systems/combatsystem.h \
    EventSystem/basememberfunctionhandler.h \
    EventSystem/collisionevent.h \
    EventSystem/event.h \
    EventSystem/memberfunctionhandler.h \
    EventSystem/eventhandler.h \
    Math/color.h \
    ECS/Components/player_component.h \
    ECS/Components/ai_component.h \
    ECS/Systems/thirdpersoncamerasystem.h \
    ECS/Components/third_person_camera_component.h \
    ECS/Components/skybox_component.h \
    ECS/Systems/skyboxsystem.h \
    cubemap.h \
    path.h \
    ECS/component.h \
    EventSystem/spherecollisionevent.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
# --------------------------------------------------------------
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# External libraries
# --------------------------------------------------------------
unix|win32: LIBS += -L$$PWD/Libraries/libs/ -lassimp-vc140-mt

INCLUDEPATH += $$PWD/Libraries/Include
DEPENDPATH += $$PWD/Libraries/Include

unix|win32: LIBS += -L$$PWD/Libraries/libs/ -lglm_static

INCLUDEPATH += $$PWD/Libraries/Include
DEPENDPATH += $$PWD/Libraries/Include

# Shader files
# --------------------------------------------------------------
DISTFILES += \
    Shaders/VertexShader.vert \
    Shaders/PhongShader.frag \
    Shaders/Skybox.frag \
    Shaders/Skybox.vert

# App icon
RC_FILE = myapp.rc
