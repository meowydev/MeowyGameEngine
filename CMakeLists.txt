cmake_minimum_required(VERSION 3.15)

set(LLVM_ROOT "/opt/homebrew/opt/llvm")
if(NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "${LLVM_ROOT}/bin/clang" CACHE FILEPATH "" FORCE)
endif()
if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "${LLVM_ROOT}/bin/clang++" CACHE FILEPATH "" FORCE)
endif()

project(MeowyGameEngine)

execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE MACOS_SDK
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_OSX_SYSROOT ${MACOS_SDK})

if(NOT CMAKE_CXX_COMPILER MATCHES "/opt/homebrew/opt/llvm/bin/clang\\+\\+")
    message(FATAL_ERROR "Homebrew LLVM is required. Use /opt/homebrew/opt/llvm/bin/clang++.")
endif()

# ---- C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- SFML (brew, shared)
set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML" CACHE PATH "" FORCE)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

# ---- spdlog (brew)
find_package(spdlog REQUIRED)

# ---- imgui-sfml config
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui CACHE PATH "" FORCE)

# ---- imgui-sfml
add_subdirectory(external/imgui-sfml)

# ---- executable
add_executable(MeowyGameEngine main.cpp)

# ---- link libs
target_link_libraries(MeowyGameEngine
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        spdlog::spdlog
        ImGui-SFML
)

# Workaround for libc++ 21 + SFML 2.6 String/Uint32 usage.
set(SFML_CHAR_TRAITS_HEADER "${CMAKE_SOURCE_DIR}/engine/sfml_char_traits.hpp")
target_compile_options(ImGui-SFML PRIVATE -include ${SFML_CHAR_TRAITS_HEADER})
target_compile_options(MeowyGameEngine PRIVATE -include ${SFML_CHAR_TRAITS_HEADER})

add_custom_command(
        TARGET MeowyGameEngine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)
