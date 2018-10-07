#ifndef COLORS_H
#define COLORS_H

#include "vec3.h"

// TODO snakk med Ole, namespace isteden?
struct Colors
{
    static const am::Vec3 white;
    static const am::Vec3 silver;
    static const am::Vec3 gray;
    static const am::Vec3 black;
    static const am::Vec3 red;
    static const am::Vec3 maroon;
    static const am::Vec3 yellow;
    static const am::Vec3 olive;
    static const am::Vec3 lime;
    static const am::Vec3 green;
    static const am::Vec3 aqua;
    static const am::Vec3 teal;
    static const am::Vec3 blue;
    static const am::Vec3 navy;
    static const am::Vec3 fuchsia;
    static const am::Vec3 purple;
    static const am::Vec3 orange;
    static const am::Vec3 orangeRed;

private:
    Colors() = default;
};

#endif // COLORS_H
