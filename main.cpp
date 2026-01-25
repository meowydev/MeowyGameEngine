#include <SFML/Graphics.hpp>     // SFML
#include <imgui.h>              // ImGui core
#include <imgui_internal.h>
#include <imgui-SFML.h>         // ImGui-SFML
#include <spdlog/spdlog.h>
#include <vector>               // std::vector
#include <algorithm>            // std::min
#include "engine/CodeEditor.h"
#include <string>

std::string editorCode = "test \"hi\"";

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(1280, 720),
        "Meowy Engine"
    );
    ImGui::SFML::Init(window);

    //vars
    static bool runGame = false;
    static std::string runGameName = "Run game";

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // enable docking
    io.IniFilename = nullptr;                          // disable ini

    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding      = ImVec2(0, 0);
    style.WindowBorderSize   = 0.f;
    style.FrameBorderSize    = 0.f;
    style.ChildBorderSize    = 0.f;
    style.DockingSeparatorSize = 1.f;
    style.TabRounding      = 0.f;

    style.Colors[ImGuiCol_FrameBg] = {112.f / 255.f, 112.f / 255.f, 112.f / 255.f, 0.f};

    sf::Clock deltaClock;
    CodeEditor editor;

    sf::RenderTexture scene;

    sf::RectangleShape cube({50.f, 50.f});
    cube.setFillColor(sf::Color::Green);
    cube.setPosition(200.f, 200.f);

    static bool firstFrame = true; // run layout once

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

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

        ImGui::Begin("General");
        ImGui::BeginTabBar("General_MAIN");
        if (ImGui::BeginTabItem("Assets"))
        {
            ImGui::Text("Placeholder...");

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Code Editor"))
        {
            editor.Draw();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("DevMenu"))
        {
            if (ImGui::Button("Crash"))
            {
                IM_ASSERT(false && "Crash button pressed");
            }

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
        ImGui::End();

        ImGui::Begin("Scene");

        if (ImGui::Button(runGameName.c_str()))
        {
            if (runGame == true)
            {
                runGame = false;
                runGameName = "Run game";
            }
            if (runGame == false)
            {
                runGame = true;
                runGameName = "Stop game";
            }
        }

        ImVec2 avail = ImGui::GetContentRegionAvail();

        if (avail.x < 1.f) avail.x = 1.f;
        if (avail.y < 1.f) avail.y = 1.f;

        if (scene.getSize().x != (unsigned)avail.x ||
            scene.getSize().y != (unsigned)avail.y)
        {
            scene.create(
                static_cast<unsigned>(avail.x),
                static_cast<unsigned>(avail.y)
            );
        }

        ImGui::Image(scene, avail);

        ImGui::End();

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
