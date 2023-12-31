cmake_minimum_required(VERSION 3.9...3.20)

project("mana-util" LANGUAGES "CXX" VERSION "1.0")

set(IMGUI_SRC_DIR "${CMAKE_SOURCE_DIR}/external/imgui")
set(GLFW_SRC_DIR "${CMAKE_SOURCE_DIR}/external/glfw")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(TITLE_TEXT "${PROJECT_NAME} ${PROJECT_VERSION}")
add_compile_definitions(TITLE_TEXT="${TITLE_TEXT}")

set(IMGUI_SRC
        "${IMGUI_SRC_DIR}/imconfig.h"
        "${IMGUI_SRC_DIR}/imgui.cpp"
        "${IMGUI_SRC_DIR}/imgui.h"
        "${IMGUI_SRC_DIR}/imgui_demo.cpp"
        "${IMGUI_SRC_DIR}/imgui_draw.cpp"
        "${IMGUI_SRC_DIR}/imgui_internal.h"
        "${IMGUI_SRC_DIR}/imgui_tables.cpp"
        "${IMGUI_SRC_DIR}/imgui_widgets.cpp"
        "${IMGUI_SRC_DIR}/imgui_impl_glfw.cpp"
        "${IMGUI_SRC_DIR}/imgui_impl_glfw.h"
        "${IMGUI_SRC_DIR}/imgui_impl_opengl3.cpp"
        "${IMGUI_SRC_DIR}/imgui_impl_opengl3.h"
        "${IMGUI_SRC_DIR}/imgui_impl_opengl3_loader.h"
        # imgui STB
        "${IMGUI_SRC_DIR}/imstb_rectpack.h"
        "${IMGUI_SRC_DIR}/imstb_textedit.h"
        "${IMGUI_SRC_DIR}/imstb_truetype.h"
        # perhaps consider adding imgui stdlib for std::string support.
)
set(IMGUI_INCLUDE_DIRS "${GLFW_SRC_DIR}")
set(IMGUI_COMPILE_FLAGS "-fPIC")

set(LIBRARY_SRC
        "${SRC_DIR}/libmain.cpp"
        "${SRC_DIR}/gui/ManaGui.h"
        "${SRC_DIR}/gui/ManaGui.cpp"
        "${SRC_DIR}/gui/ManaColor.h"
        "${SRC_DIR}/gui/ManaColor.cpp"
        "${SRC_DIR}/gui/IconsMaterialDesign.h"
)

add_subdirectory("${CMAKE_SOURCE_DIR}/windows")
add_subdirectory("${CMAKE_SOURCE_DIR}/linux")

add_subdirectory("${CMAKE_SOURCE_DIR}/test_exe")