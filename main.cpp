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
    GetIO().IniFilename = nullptr;

    sf::Clock deltaClock;

    // SFML Draw space
    sf::RenderTexture Scene;

    sf::Texture texture("assets/icons/folder.png");

    sf::RectangleShape Test({10, 10});
    Test.setFillColor(sf::Color::White);

    std::vector<sf::RectangleShape> RectangleShapes;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;

                if (key == sf::Keyboard::Key::D)
                {
                    Test.setPosition(Test.getPosition() + sf::Vector2f(10, 0));
                }

            }

        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // Assets window

        Begin("Assets");
        Text("Root/");

        if (Button("Create object"))
        {
            sf::RectangleShape Shape({30,30});
            Shape.setFillColor(sf::Color::Yellow);
            Shape.setPosition(Test.getPosition());
            RectangleShapes.push_back(Shape);
        }

        Image(texture, sf::Vector2f(128,128));

        End();

        Begin("Scene");
        ImVec2 avail = ImGui::GetContentRegionAvail();
        sf::Vector2u newSize(
            static_cast<unsigned>(avail.x),
            static_cast<unsigned>(avail.y)
        );

        if (newSize.x > 0 && newSize.y > 0 &&
            Scene.getSize() != newSize)
        {
            Scene.resize(newSize);
        }
        Image(Scene, avail);
        End();

        window.clear(sf::Color::Black);
        Scene.clear(sf::Color::Black);

        Scene.draw(Test);

        for (const auto& obj : RectangleShapes)
        {
            Scene.draw(obj);
        }

        SFML::Render(window);

        window.display();
    }
    SFML::Shutdown();

}
