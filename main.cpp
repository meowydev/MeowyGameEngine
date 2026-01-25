#include <SFML/Graphics.hpp>     // SFML
#include <imgui.h>              // ImGui core
#include <imgui_internal.h>
#include <imgui-SFML.h>         // ImGui-SFML
#include <vector>               // std::vector
#include <algorithm>            // std::min
#include "engine/windows.h"

sf::RenderTexture scene;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(1280, 720),
        "Meowy Engine"
    );

    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // enable docking
    io.IniFilename = nullptr;                          // disable ini

    // ---------------- STYLE ----------------

    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding      = ImVec2(0, 0);
    style.WindowBorderSize   = 0.f;
    style.FrameBorderSize    = 0.f;
    style.ChildBorderSize    = 0.f;
    style.DockingSeparatorSize = 1.f;
    style.TabRounding      = 0.f;

    style.Colors[ImGuiCol_FrameBg] = {112.f / 255.f, 112.f / 255.f, 112.f / 255.f, 0.f};
    
    // ---------------- CLOCK ----------------

    sf::Clock deltaClock;

    sf::RectangleShape cube({50.f, 50.f});
    cube.setFillColor(sf::Color::Green);
    cube.setPosition(200.f, 200.f);

    // ---------------- DOCK STATE ----------------

    static bool firstFrame = true; // run layout once

    // ---------------- LOOP ----------------

    while (window.isOpen())
    {
        // ---------- EVENTS ----------

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ---------- UPDATE ----------

        ImGui::SFML::Update(window, deltaClock.restart());

        // ---------- DOCK ROOT ----------

        ImGuiViewport* vp = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(vp->WorkPos);
        ImGui::SetNextWindowSize(vp->WorkSize);
        ImGui::SetNextWindowViewport(vp->ID);

        ImGuiWindowFlags rootFlags =
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground;

        ImGui::Begin("DockRoot", nullptr, rootFlags);

        ImGuiID dockspaceID = ImGui::GetID("MainDockspace");
        ImGui::DockSpace(dockspaceID);

        ImGui::End();

        // ---------- DEFAULT LAYOUT (ONCE) ----------

        static ImGuiID dockScene  = 0;
        static ImGuiID dockAssets = 0;

        if (firstFrame)
        {
            ImGui::DockBuilderRemoveNode(dockspaceID);
            ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspaceID, vp->WorkSize);

            // split vertically: top = Scene, bottom = Assets
            dockScene = dockspaceID;
            dockAssets = ImGui::DockBuilderSplitNode(
                dockScene,
                ImGuiDir_Down,
                0.5f,
                nullptr,
                &dockScene
            );

            ImGui::DockBuilderDockWindow("Scene", dockScene);
            ImGui::DockBuilderDockWindow("General", dockAssets);

            ImGui::DockBuilderFinish(dockspaceID);

            firstFrame = false;
        }

        meowyengine::defaultwindows();

        // ---------- RENDER SCENE ----------

        scene.clear(sf::Color(30, 30, 30));
        scene.draw(cube);
        scene.display();

        window.clear(sf::Color::Black);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
