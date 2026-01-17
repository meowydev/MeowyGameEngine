#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <spdlog/spdlog.h>
using namespace ImGui;

int main()
{

    bool Test_CheckBox = false;
    int counter = 0;
    float load = 0.0f;
    static bool start = true;

    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        "Meowy Engine V1"
    );

    //Init ImGUI
    SFML::Init(window);

    static ImGuiIO& io = ImGui::GetIO();
    GetIO().IniFilename = nullptr;

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
xd
        }
        ImGui::SFML::Update(window, deltaClock.restart());


        // Default window
        if (start == true)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_FirstUseEver);
            start = false;
        }

        Begin("Welcome to Meowy Engine :3");
        Text("Loading please wait...");

        ProgressBar(load, ImVec2(0.f,0.0f));
        SetItemTooltip("Loading bar");

        End();

        load += deltaClock.getElapsedTime().asSeconds();

        window.clear(sf::Color::White);

        SFML::Render(window);

        window.display();
    }
    SFML::Shutdown();

}
