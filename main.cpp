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

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Meowy Engine V1"
    );

    //Init ImGUI
    SFML::Init(window);

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

        }
        ImGui::SFML::Update(window, deltaClock.restart());

        // Default window

        Begin("Welcome to Meowy Engine :3");
        Text("Welcome :333");
        if (Button("Counter +"))
        {
            counter++;
        }

        Text("Counter: %d", counter);

        End();

        window.clear(sf::Color::White);

        SFML::Render(window);

        window.display();
    }

}