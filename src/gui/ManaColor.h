
#include "imgui.h"

class ManaColor {
public:
    ManaColor(float r, float g, float b, float a = 1.0f);

    float *get4F();

    ImVec4 toImVec4();

    ManaColor multiply(float m);

    ManaColor alpha(float a);

    ManaColor saturation(float s);

private:
    float color[4];
};