
// Copyright (c) 2023. tiredy
//
// This file is part of mana-utility
//
// mana-utility is free software: you can redistribute it and/or modify
// it under the terms of the gnu affero general public license as
// published by the free software foundation, either version 3 of the
// license, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but without any warranty; without even the implied warranty of
// merchantability or fitness for a particular purpose. See the
// gnu affero general public license for more details.
//
// You should have received a copy of the gnu affero general public license
// along with this program. If not, see <https: //www. Gnu. Org/licenses/>

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