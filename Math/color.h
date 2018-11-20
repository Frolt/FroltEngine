#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

// TODO snakk med Ole, namespace isteden?
namespace Color
{
    const am::Color white{1.0f, 1.0f, 1.0f};
    const am::Color silver{0.752f, 0.752f, 0.752f};
    const am::Color gray{0.501f, 0.501f, 0.501f};
    const am::Color black{0.0f, 0.0f, 0.0f};
    const am::Color red{1.0f, 0.0f, 0.0f};
    const am::Color maroon{0.501f, 0.0f, 0.0f};
    const am::Color yellow{1.0f, 1.0f, 0.0f};
    const am::Color olive{0.501f, 0.501f, 0.0f};
    const am::Color lime{0.0f, 1.0f, 0.0f};
    const am::Color green{0.0f, 0.501f, 0.0f};
    const am::Color aqua{0.0f, 1.0f, 1.0f};
    const am::Color teal{0.0f, 0.501f, 0.501f};
    const am::Color blue{0.0f, 0.0f, 1.0f};
    const am::Color navy{0.0f, 0.0f, 0.501f};
    const am::Color fuchsia{1.0f, 0.0f, 1.0f};
    const am::Color purple{0.501f, 0.0f, 0.501f};
    const am::Color orange{1.0f, 0.647f, 0.0f};
    const am::Color orangeRed{1.0f, 0.270f, 0.0f};
};

#endif // COLOR_H
