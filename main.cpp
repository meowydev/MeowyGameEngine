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
    static bool start = true;

    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        "Meowy Engine V1"
    );

    //Init ImGUI
    SFML::Init(window);

    ImGuiStyle& style = ImGui::GetStyle();

    ImGuiIO& io = ImGui::GetIO();
    //GetIO().IniFilename = nullptr;

    sf::Clock deltaClock;

    // SFML Draw space
    sf::RenderTexture Scene;

    sf::Texture texture("assets/icons/folder.png");

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        // Default window

        Begin("Assets");
        Text("Root/");

        Image(texture, sf::Vector2f(128,128));

        End();

        window.clear(sf::Color::Black);

        SFML::Render(window);

        window.display();
    }
    SFML::Shutdown();

}
