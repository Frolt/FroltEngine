#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

// Forward declarations
class Viewport;

class InputComponent
{
public:
    InputComponent(Viewport *viewport);
    virtual ~InputComponent();
    virtual void update() = 0;

protected:
    Viewport *mViewport;
};

#endif // INPUTCOMPONENT_H
