set(CMAKE_SYSTEM_NAME "Linux")
set(CMAKE_SYSTEM_PROCESSOR "x86_64")

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

find_package(glfw3 REQUIRED)

add_library(imgui_linux STATIC "${IMGUI_SRC}")
target_include_directories(imgui_linux PRIVATE "${IMGUI_INCLUDE_DIRS}")
target_compile_options(imgui_linux PRIVATE "${IMGUI_COMPILE_FLAGS}")

add_library(ManaUnix SHARED "${LIBRARY_SRC}")
set_target_properties(ManaUnix PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}-unix"
        PREFIX ""
        SUFFIX ".so"
)

target_link_libraries(ManaUnix PRIVATE imgui_linux glfw "-lGL")

target_include_directories(ManaUnix PRIVATE "${IMGUI_SRC_DIR}" "${SRC_DIR}")