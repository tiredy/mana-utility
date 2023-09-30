set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_SYSTEM_PROCESSOR "x86_64")

set(CMAKE_C_COMPILER "x86_64-w64-mingw32-gcc")
set(CMAKE_CXX_COMPILER "x86_64-w64-mingw32-g++")

set(CMAKE_FIND_ROOT_PATH "/usr/x86_64-w64-mingw32/sys-root/mingw")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

add_library(imgui_win STATIC "${IMGUI_SRC}")
target_include_directories(imgui_win PRIVATE "${IMGUI_INCLUDE_DIRS}")
target_compile_options(imgui_win PRIVATE "${IMGUI_COMPILE_FLAGS}")

add_library(ManaWin32 SHARED "${LIBRARY_SRC}")
set_target_properties(ManaWin32 PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}-win32"
        PREFIX ""
        SUFFIX ".dll"
)

target_link_directories(ManaWin32 PUBLIC "${GLFW_SRC_DIR}/lib")
target_link_libraries(ManaWin32 PUBLIC glfw3 imgui_win "-lgdi32 -lopengl32 -static")

target_include_directories(ManaWin32 PUBLIC "${SRC_DIR}" "${IMGUI_SRC_DIR}" "${GLFW_SRC_DIR}")