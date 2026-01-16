execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE MACOS_SDK
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_OSX_SYSROOT ${MACOS_SDK})

cmake_minimum_required(VERSION 4.1)
project(MeowyGameEngine)

# ---- C++
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- SFML (brew, shared)
set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)
find_package(SFML REQUIRED COMPONENTS Graphics Window System Audio)

# ---- spdlog (brew)
find_package(spdlog REQUIRED)

# ---- imgui-sfml config
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui CACHE PATH "" FORCE)

# ---- ImGui (source-only)
add_library(imgui STATIC
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_tables.cpp
)

target_include_directories(imgui PUBLIC
        external/imgui
)

# ---- imgui-sfml
add_subdirectory(external/imgui-sfml)

# ---- executable
add_executable(MeowyGameEngine main.cpp)

# ---- link libs
target_link_libraries(MeowyGameEngine
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        spdlog::spdlog
        imgui
        ImGui-SFML
)
