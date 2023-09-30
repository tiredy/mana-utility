#include "ManaColor.h"

ManaColor::ManaColor(float r, float g, float b, float a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

float* ManaColor::get4F()
{
    return color;
}

ImVec4 ManaColor::toImVec4()
{
    return ImVec4(color[0], color[1], color[2], color[3]);
}

ManaColor ManaColor::multiply(float m)
{
    return ManaColor(color[0] * m, color[1] * m, color[2] * m, color[3]);
}

ManaColor ManaColor::alpha(float a)
{
    return ManaColor(color[0], color[1], color[2], color[3] * a);
}

ManaColor ManaColor::saturation(float s) {
    // Interpolate each component towards the grayscale value
    float gray = color[0] * 0.299f + color[1] * 0.587f + color[2] * 0.114f;
    float r = gray + (color[0] - gray) * s;
    float g = gray + (color[1] - gray) * s;
    float b = gray + (color[2] - gray) * s;

    // Return a new ManaColor with the modified saturation
    return ManaColor(r, g, b, color[3]);
}
