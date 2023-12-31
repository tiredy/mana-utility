
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

#pragma once

#include <cmath>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/gl.h>
#include "GLFW/glfw3.h"

// Fonts
#include "IconsMaterialDesign.h"

#include "ManaColor.h"

#define WIDTH 640
#define HEIGHT 480

#define INCLUDE_FOLDER "./include/"

#define FONT_ROBOTO_FILE_NAME "RobotoMono-Regular.ttf"
#define FONT_RUBIK_FILE_NAME "RubikMonoOne-Regular.ttf"

#define FONT_SIZE 16.0f
#define BIG_FONT_SIZE 24.0f
#define TITLE_FONT_SIZE 16.0f

#define TITLEBAR_HEIGHT 32.0f

#ifndef TITLE_TEXT
#define TITLE_TEXT "Mana - Title Missing"
#endif

class ManaGui
{
public:
    void init();
    void end();

    void setupStyle();
    void setupFonts();

    void dragHandler();

    bool run();

    static void glfw_error_callback(int error, const char* desc);
private:
    ImVec2 preCalcItemSize(const ImGuiStyle& s, int charCount);

    struct WindowState {
        double prevMouseX = 0.0, prevMouseY = 0.0;
        bool dragging = false;

        bool openSettings = false;
        bool openStyleEditor = false;

        ManaColor colorMain = ManaColor(0.15f, 0.16f, 0.21f);
        ManaColor colorAccent = ManaColor(1.0f, 0.47f, 0.77f);

        int windowHeight = HEIGHT, windowWidth = WIDTH;
    };

    ImFont* titleFont;
    ImFont* bigFont;

    const char* title = TITLE_TEXT;

    WindowState state;
    GLFWwindow* window;
};