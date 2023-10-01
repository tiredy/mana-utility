
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

#include "ManaGui.h"

void ManaGui::init()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return;

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    window = glfwCreateWindow(state.windowWidth, state.windowHeight, title, nullptr, nullptr);
    if (window == nullptr)
        return;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Vsync

    // glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    setupStyle();
    setupFonts();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void ManaGui::end()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ManaGui::setupStyle()
{
    ImGuiStyle *style = &ImGui::GetStyle();

    style->WindowMinSize = ImVec2(200, 80);
    style->WindowPadding = ImVec2(4, 4);
    style->FramePadding = ImVec2(4, 4);
    
    style->Alpha                = 1.00f;

    style->ItemSpacing = ImVec2(4, 4);
    style->ItemInnerSpacing = ImVec2(4, 4);
    style->IndentSpacing = 6.0f;
    style->ColumnsMinSpacing = 50.0f;

    style->GrabMinSize = 14.0f;
    style->ScrollbarSize = 12.0f;

    style->WindowRounding = 0.0f;
    style->GrabRounding = 1.0f;
    style->ScrollbarRounding = 16.0f;
    style->TabRounding = 2.0f;
    style->FrameRounding = 2.0f;

    style->TabBorderSize = 0.0f;
    style->FrameBorderSize = 0.0f;
    style->PopupBorderSize = 0.0f;
    style->WindowBorderSize = 0.0f;
    style->SeparatorTextBorderSize = 0.0f;
    style->ChildBorderSize = 0.0f;
    
            // Non-Customizable
    style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.05f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    
            // Primary
    style->Colors[ImGuiCol_WindowBg] = state.colorMain.toImVec4();
    style->Colors[ImGuiCol_PopupBg] = state.colorMain.toImVec4();

            // Accent
    style->Colors[ImGuiCol_Button] = state.colorAccent.alpha(0.4f).toImVec4();
    style->Colors[ImGuiCol_Header] = state.colorAccent.alpha(0.4f).toImVec4();
    style->Colors[ImGuiCol_SliderGrab] = state.colorAccent.alpha(0.4f).toImVec4();
    style->Colors[ImGuiCol_ScrollbarGrab] = state.colorAccent.alpha(0.4f).toImVec4();
    style->Colors[ImGuiCol_Tab] = state.colorAccent.multiply(0.9f).alpha(0.8f).toImVec4();
    style->Colors[ImGuiCol_TabUnfocused] = state.colorAccent.multiply(0.7f).alpha(0.95f).toImVec4();
    style->Colors[ImGuiCol_TitleBg] = state.colorAccent.multiply(0.5f).toImVec4();
    style->Colors[ImGuiCol_ResizeGrip] = state.colorAccent.alpha(0.2f).toImVec4();
            // Hovered
    style->Colors[ImGuiCol_ButtonHovered] = state.colorAccent.alpha(0.8f).toImVec4();
    style->Colors[ImGuiCol_HeaderHovered] = state.colorAccent.alpha(0.8f).toImVec4();
    style->Colors[ImGuiCol_TabHovered] = state.colorAccent.alpha(0.8f).toImVec4();
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = state.colorAccent.alpha(0.8f).toImVec4();
    style->Colors[ImGuiCol_SeparatorHovered] = state.colorAccent.multiply(0.8f).alpha(0.78f).toImVec4();
    style->Colors[ImGuiCol_ResizeGripHovered] = state.colorAccent.alpha(0.67f).toImVec4();
            // Active
    style->Colors[ImGuiCol_ButtonActive] = state.colorAccent.saturation(1.1f).toImVec4();
    style->Colors[ImGuiCol_HeaderActive] = state.colorAccent.saturation(1.1f).toImVec4();
    style->Colors[ImGuiCol_SliderGrabActive] = state.colorAccent.saturation(1.1f).toImVec4();
    style->Colors[ImGuiCol_ScrollbarGrabActive] = state.colorAccent.saturation(1.1f).toImVec4();
    style->Colors[ImGuiCol_TabActive] = state.colorAccent.multiply(0.9f).toImVec4();
    style->Colors[ImGuiCol_TabUnfocusedActive] = state.colorAccent.multiply(0.8f).toImVec4();
    style->Colors[ImGuiCol_TitleBgActive] = state.colorAccent.multiply(0.9f).toImVec4();
    style->Colors[ImGuiCol_SeparatorActive] = state.colorAccent.multiply(0.8f).toImVec4();
    style->Colors[ImGuiCol_ResizeGripActive] = state.colorAccent.toImVec4();
            // Frame
    style->Colors[ImGuiCol_FrameBg] = state.colorAccent.multiply(0.9f).alpha(0.55f).toImVec4();
    style->Colors[ImGuiCol_FrameBgActive] = state.colorAccent.alpha(0.4f).toImVec4();
    style->Colors[ImGuiCol_FrameBgHovered] = state.colorAccent.alpha(0.67f).toImVec4();
            // Other
    style->Colors[ImGuiCol_CheckMark] = state.colorAccent.toImVec4();
    style->Colors[ImGuiCol_TextSelectedBg] = state.colorAccent.alpha(0.35f).toImVec4();
    style->Colors[ImGuiCol_NavHighlight] = state.colorAccent.toImVec4();
}

void ManaGui::setupFonts()
{
    ImGuiIO &io = ImGui::GetIO();

    static const ImWchar iconsRanges[] = {ICON_MIN_MD, ICON_MAX_16_MD, 0};
    ImFontConfig fontConfig;
    fontConfig.MergeMode = true;
    fontConfig.PixelSnapH = true;
    fontConfig.GlyphOffset = { 0.0f, 4.0f };

    io.Fonts->AddFontFromFileTTF(INCLUDE_FOLDER FONT_ROBOTO_FILE_NAME, FONT_SIZE);
    io.Fonts->AddFontFromFileTTF(INCLUDE_FOLDER FONT_ICON_FILE_NAME_MD, FONT_SIZE, &fontConfig, iconsRanges);
    io.Fonts->Build();

    bigFont = io.Fonts->AddFontFromFileTTF(INCLUDE_FOLDER FONT_ROBOTO_FILE_NAME, BIG_FONT_SIZE);
    io.Fonts->AddFontFromFileTTF(INCLUDE_FOLDER FONT_ICON_FILE_NAME_MD, BIG_FONT_SIZE, &fontConfig, iconsRanges);
    io.Fonts->Build();

    titleFont = io.Fonts->AddFontFromFileTTF(INCLUDE_FOLDER FONT_RUBIK_FILE_NAME, TITLE_FONT_SIZE);
    io.Fonts->AddFontFromFileTTF(INCLUDE_FOLDER FONT_ICON_FILE_NAME_MD, TITLE_FONT_SIZE, &fontConfig, iconsRanges);
    io.Fonts->Build();
}

void ManaGui::dragHandler()
{
    bool mouseDown = glfwGetMouseButton(window, 0) == GLFW_PRESS;
    if(!mouseDown) {
        if(state.dragging) {
            state.dragging = false;
        }
        return;
    }
    if(!state.dragging) {
        double mouseX, mouseY;
        int windowW, windowH;
        glfwGetWindowSize(window, &windowW, &windowH);
        glfwGetCursorPos(window, &mouseX, &mouseY);

        ImVec2 padding = ImGui::GetStyle().WindowPadding;
        ImVec2 titleBarPos = ImVec2(padding.x, padding.y);
        ImVec2 titleBarSize = ImVec2(windowW - 2 * padding.x, TITLEBAR_HEIGHT);

        if(mouseX >= titleBarPos.x && mouseY >= titleBarPos.y &&
            mouseX <= titleBarPos.x + titleBarSize.x &&
            mouseY <= titleBarPos.y + titleBarSize.y)
        {
            state.prevMouseX = mouseX;
            state.prevMouseY = mouseY;
            state.dragging = true;
        }
    } else {
        double mouseX, mouseY;
        int windowX, windowY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glfwGetWindowPos(window, &windowX, &windowY);
        glfwSetWindowPos(window, windowX + (mouseX - state.prevMouseX), windowY + (mouseY - state.prevMouseY));
    }
}

bool ManaGui::run() {
    if (glfwWindowShouldClose(window))
        return false;

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiViewport * viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport -> Pos);
    ImGui::SetNextWindowSize(viewport -> WorkSize);

    ImGuiStyle* style = &ImGui::GetStyle();

    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("main", NULL, flags);

    {
        ImVec2 freeSpace = ImGui::GetContentRegionAvail();
        ImGui::BeginChild("title-bar", ImVec2(freeSpace.x, TITLEBAR_HEIGHT));

        ImGui::PushFont(titleFont);

        ImGui::SetCursorPosY((ImGui::GetContentRegionMax().y - ImGui::GetFontSize()) * 0.5f);
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Text(title);

        ImVec2 buttonSize = preCalcItemSize(*style, 1);
        float cursorCenterY = (ImGui::GetContentRegionMax().y - ImGui::GetFontSize() - style->FramePadding.y * 2) * 0.5f;
        ImGui::SameLine(ImGui::GetContentRegionMax().x - buttonSize.x * 2);
        ImGui::SetCursorPosY(cursorCenterY);
        if (ImGui::Button(ICON_MD_MINIMIZE)) {
            glfwIconifyWindow(window);
        }

        ImGui::SameLine();
        ImGui::SetCursorPosY(cursorCenterY);

        if (ImGui::Button(ICON_MD_CLOSE)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        ImGui::PopFont();
        ImGui::EndChild();
    }
    if (state.openSettings) {
        ImVec2 freeSpace = ImGui::GetContentRegionAvail();
        ImGui::BeginChild("settings", ImVec2(freeSpace.x, 0));

        ImGui::Spacing();
        ImGui::TextWrapped("The width and height of the menu window. Max size is 3840x2400 (4k 16:10)");
        if(ImGui::InputInt("Width", &state.windowWidth, 1, 5))
        {
            state.windowWidth = std::fmin(std::fmax(state.windowWidth, style->WindowMinSize.x), 3840);
            glfwSetWindowSize(window, state.windowWidth, state.windowHeight);
        }
        if(ImGui::InputInt("Height", &state.windowHeight, 1, 5))
        {
            state.windowHeight = std::fmin(std::fmax(state.windowHeight, style->WindowMinSize.y), 2400);
            glfwSetWindowSize(window, state.windowWidth, state.windowHeight);
        }
        ImGui::Spacing();
        ImGui::Checkbox("Show style editor", &state.openStyleEditor);

        ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
        if(ImGui::ColorEdit4("Main color", state.colorMain.get4F(), flags)) {
            style->Colors[ImGuiCol_WindowBg] = state.colorMain.toImVec4();
            style->Colors[ImGuiCol_PopupBg] = state.colorMain.toImVec4();
            style->Colors[ImGuiCol_ScrollbarBg] = state.colorMain.toImVec4();
        }
        if(ImGui::ColorEdit4("Accent color", state.colorAccent.get4F(), flags)) {
            // Normal
            style->Colors[ImGuiCol_Button] = state.colorAccent.alpha(0.4f).toImVec4();
            style->Colors[ImGuiCol_Header] = state.colorAccent.alpha(0.4f).toImVec4();
            style->Colors[ImGuiCol_SliderGrab] = state.colorAccent.alpha(0.4f).toImVec4();
            style->Colors[ImGuiCol_ScrollbarGrab] = state.colorAccent.alpha(0.4f).toImVec4();
            style->Colors[ImGuiCol_Tab] = state.colorAccent.multiply(0.9f).alpha(0.8f).toImVec4();
            style->Colors[ImGuiCol_TabUnfocused] = state.colorAccent.multiply(0.7f).alpha(0.95f).toImVec4();
            style->Colors[ImGuiCol_TitleBg] = state.colorAccent.multiply(0.5f).toImVec4();
            style->Colors[ImGuiCol_ResizeGrip] = state.colorAccent.alpha(0.2f).toImVec4();
            // Hovered
            style->Colors[ImGuiCol_ButtonHovered] = state.colorAccent.alpha(0.8f).toImVec4();
            style->Colors[ImGuiCol_HeaderHovered] = state.colorAccent.alpha(0.8f).toImVec4();
            style->Colors[ImGuiCol_TabHovered] = state.colorAccent.alpha(0.8f).toImVec4();
            style->Colors[ImGuiCol_ScrollbarGrabHovered] = state.colorAccent.alpha(0.8f).toImVec4();
            style->Colors[ImGuiCol_SeparatorHovered] = state.colorAccent.multiply(0.8f).alpha(0.78f).toImVec4();
            style->Colors[ImGuiCol_ResizeGripHovered] = state.colorAccent.alpha(0.67f).toImVec4();
            // Active
            style->Colors[ImGuiCol_ButtonActive] = state.colorAccent.saturation(1.1f).toImVec4();
            style->Colors[ImGuiCol_HeaderActive] = state.colorAccent.saturation(1.1f).toImVec4();
            style->Colors[ImGuiCol_SliderGrabActive] = state.colorAccent.saturation(1.1f).toImVec4();
            style->Colors[ImGuiCol_ScrollbarGrabActive] = state.colorAccent.saturation(1.1f).toImVec4();
            style->Colors[ImGuiCol_TabActive] = state.colorAccent.multiply(0.9f).toImVec4();
            style->Colors[ImGuiCol_TabUnfocusedActive] = state.colorAccent.multiply(0.8f).toImVec4();
            style->Colors[ImGuiCol_TitleBgActive] = state.colorAccent.multiply(0.9f).toImVec4();
            style->Colors[ImGuiCol_SeparatorActive] = state.colorAccent.multiply(0.8f).toImVec4();
            style->Colors[ImGuiCol_ResizeGripActive] = state.colorAccent.toImVec4();
            // Frame
            style->Colors[ImGuiCol_FrameBg] = state.colorAccent.multiply(0.9f).alpha(0.55f).toImVec4();
            style->Colors[ImGuiCol_FrameBgActive] = state.colorAccent.alpha(0.4f).toImVec4();
            style->Colors[ImGuiCol_FrameBgHovered] = state.colorAccent.alpha(0.67f).toImVec4();
            // Other
            style->Colors[ImGuiCol_CheckMark] = state.colorAccent.toImVec4();
            style->Colors[ImGuiCol_TextSelectedBg] = state.colorAccent.alpha(0.35f).toImVec4();
            style->Colors[ImGuiCol_NavHighlight] = state.colorAccent.toImVec4();
        }

        ImGui::PushFont(bigFont);
        ImGui::Dummy(ImVec2(0, ImGui::GetContentRegionAvail().y - preCalcItemSize(*style, 1).y));
        if(ImGui::Button(ICON_MD_SETTINGS))
        {
            state.openSettings = !state.openSettings;
        }
        ImGui::PopFont();

        ImGui::EndChild();
    } else {
        {
            ImGui::BeginGroup();

            ImGui::PushFont(bigFont);
            float buttonSize = preCalcItemSize(*style, 1).y;
            float listDisplayRatio = 0.3f;
            ImGui::PopFont();

            {
                ImVec2 freeSpace = ImGui::GetContentRegionAvail();
                ImGui::BeginChild("module-list", ImVec2(freeSpace.x * listDisplayRatio, freeSpace.y - buttonSize));
                for (int i = 0; i < 32; i++) {
                    ImGui::Button(ICON_MD_CHECK " Button", ImVec2(-FLT_MIN, 0.0f));
                }
                ImGui::EndChild();
            }

            {
                ImVec2 freeSpace = ImGui::GetContentRegionAvail();
                ImGui::BeginChild("menu-buttons", ImVec2(freeSpace.x * listDisplayRatio, freeSpace.y));
                ImGui::PushFont(bigFont);

                if(ImGui::Button(ICON_MD_SETTINGS)) {
                    state.openSettings = !state.openSettings;
                }
                ImGui::SameLine();
                ImGui::Button(ICON_MD_DISCORD);
                ImGui::PopFont();
                ImGui::EndChild();
            }

            ImGui::EndGroup();
        }
        ImGui::SameLine();
        {
            ImVec2 freeSpace = ImGui::GetContentRegionAvail();
            ImGui::BeginGroup();
            ImGui::BeginChild("module-display", ImVec2(freeSpace.x, freeSpace.y));
            for (int i = 0; i < 100; i++)
                ImGui::Text("%04d: scrollable region"
                    ICON_MD_CARD_TRAVEL, i);
            ImGui::EndChild();
            ImGui::EndGroup();
        }

    }
    ImGui::End();

    if(state.openStyleEditor) {
        ImGui::ShowStyleEditor();
    }

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, & display_w, & display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(1.0f, 1.0f, 1.0f, 0.3f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);

    return true;
}

ImVec2 ManaGui::preCalcItemSize(const ImGuiStyle& s, int charCount)
{
    ImVec2 size = ImVec2(
        s.FramePadding.x * 2 + ImGui::GetFontSize() * charCount + s.ItemSpacing.x,
        s.FramePadding.y * 2 + ImGui::GetFontSize() * charCount + s.ItemSpacing.y);
    return size;
}

void ManaGui::glfw_error_callback(int error, const char *desc)
{
    std::cout << "GLFW Error: " << error << "\n " << desc << "\n";
}
