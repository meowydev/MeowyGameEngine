cmake_minimum_required(VERSION 3.15)
project(MeowyGameEngine)

# ---------- COMPILER ----------
set(LLVM_ROOT "/opt/homebrew/opt/llvm@17")
set(CMAKE_C_COMPILER "${LLVM_ROOT}/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "${LLVM_ROOT}/bin/clang++" CACHE FILEPATH "" FORCE)

# ---------- MAC SDK ----------
execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE MACOS_SDK
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_OSX_SYSROOT ${MACOS_SDK})

# ---------- C++ ----------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

# ---------- SFML ----------
set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML" CACHE PATH "" FORCE)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

# ---------- spdlog ----------
find_package(spdlog REQUIRED)

# ---------- ImGui ----------
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui CACHE PATH "" FORCE)
add_subdirectory(external/imgui-sfml)

# ---------- CodeEditor ----------
add_library(codeeditor STATIC
        external/CodeEditor/TextEditor.cpp
)

target_include_directories(codeeditor PUBLIC
        external/CodeEditor
)

target_compile_features(codeeditor PRIVATE cxx_std_20)
target_compile_options(codeeditor PRIVATE -stdlib=libc++)
target_link_options(codeeditor PRIVATE -stdlib=libc++)

# ---------- EXECUTABLE ----------
add_executable(MeowyGameEngine
        main.cpp
        engine/HLang.h
        engine/CodeEditor.h
        engine/HLangRuntime.h
)

target_compile_options(MeowyGameEngine PRIVATE -stdlib=libc++)
target_link_options(MeowyGameEngine PRIVATE -stdlib=libc++)

target_link_libraries(MeowyGameEngine
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        spdlog::spdlog
        ImGui-SFML
        codeeditor
)

# ---------- ASSETS ----------
add_custom_command(
        TARGET MeowyGameEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)
