#ifndef FREECAMERASYSTEM_H
#define FREECAMERASYSTEM_H

#include "ECS/system.h"


/**
   @brief The FreeCameraSystem class makes a FPS type camera that can be used to navigate the viewport.

   It is controlled by W,A,S,D,CTRL,SPACE and the mouse movement controls the camera rotation if the right mouse button is pressed
   The Camera uses its own coordinate system to figure out how to move correctly. F8 to possess/eject the pawn/player
   Scrolling will increase/decrease camera move speed. Scrolling while holding shift will zoom in or out.
   + and - keys can also use to zoom in or out.
 */
class FreeCameraSystem : public System
{
public:
    FreeCameraSystem();
    void beginPlay() override;
    void update(float deltaTime) override;

private:
    /// Sets
    void processKeyboard(const InputComponent &input, MovementComponent &movement, FreeCameraComponent &freeCamera, EntityHandle entity) const;
    void processMouse(const InputComponent &input, const FreeCameraComponent &freeCamera, TransformComponent &transform) const;
    void processScroll(FreeCameraComponent &freeCamera, const InputComponent &input) const;
    void updateUniforms(const FreeCameraComponent &camera, EntityHandle entity) const;
};

#endif // FREECAMERASYSTEM_H
