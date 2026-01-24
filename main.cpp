#include <iostream>                 // Стандартный ввод/вывод

#include <SFML/Graphics.hpp>        // SFML графика
#include <SFML/Audio.hpp>           // SFML звук (пока не используем)

#include <imgui.h>                  // ImGui core
#include <imgui-SFML.h>             // Связка ImGui + SFML

#include <spdlog/spdlog.h>          // Логгер (пока не используем)

int main()
{
    // ---------- SFML WINDOW ----------

    sf::RenderWindow window(
        sf::VideoMode(1280, 720),   // Размер окна
        "Meowy Engine V1"            // Заголовок
    );

    window.setFramerateLimit(60);   // Ограничение FPS

    // ---------- INIT IMGUI ----------

    ImGui::SFML::Init(window);      // Создаёт ImGui-контекст и бинды

    // ---------- IMGUI CONFIG ----------

    ImGuiIO& io = ImGui::GetIO();   // Глобальное состояние ImGui

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Включаем докинг
    io.IniFilename = nullptr;       // Отключаем imgui.ini

    // ---------- TIME ----------

    sf::Clock deltaClock;           // Для deltaTime ImGui

    // ---------- SCENE RENDER TARGET ----------

    sf::RenderTexture scene;        // Offscreen сцена
    scene.create(1280, 720);         // Начальный размер

    // ---------- TEST OBJECT ----------

    sf::RectangleShape player({50.f, 50.f}); // Тестовый объект
    player.setFillColor(sf::Color::White);
    player.setPosition(100.f, 100.f);

    std::vector<sf::RectangleShape> spawnedObjects; // Спавн-объекты

    // ---------- DOCKING STATE ----------

    static bool dockInitialized = false; // Чтобы layout создавался 1 раз

    // ---------- MAIN LOOP ----------

    while (window.isOpen())
    {
        // ---------- EVENTS ----------

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event); // В ImGui

            if (event.type == sf::Event::Closed)      // Закрытие
                window.close();

            // Движение игрока, если ImGui не забрал клавиатуру
            if (!io.WantCaptureKeyboard &&
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::D)
            {
                player.move(10.f, 0.f);
            }
        }

        // ---------- IMGUI UPDATE ----------

        ImGui::SFML::Update(window, deltaClock.restart());

        // ---------- DOCKSPACE ----------

        ImGuiID dockspaceID = ImGui::GetID("MainDockSpace"); // ID докспейса
        ImGui::DockSpace(dockspaceID, ImVec2(0.f, 0.f));    // Главный док

        // ---------- DOCK LAYOUT (ONCE) ----------

        if (!dockInitialized)
        {
            dockInitialized = true;

            ImGui::DockBuilderRemoveNode(dockspaceID); // Чистим старое
            ImGui::DockBuilderAddNode(                  // Новый node
                dockspaceID,
                ImGuiDockNodeFlags_DockSpace
            );

            ImGui::DockBuilderSetNodeSize(               // Размер = окно
                dockspaceID,
                ImGui::GetMainViewport()->Size
            );

            ImGuiID dockMain = dockspaceID;
            ImGuiID dockLeft;
            ImGuiID dockRight;

            dockLeft = ImGui::DockBuilderSplitNode(      // Левая панель
                dockMain,
                ImGuiDir_Left,
                0.20f,
                nullptr,
                &dockMain
            );

            dockRight = ImGui::DockBuilderSplitNode(     // Правая панель
                dockMain,
                ImGuiDir_Right,
                0.25f,
                nullptr,
                &dockMain
            );

            ImGui::DockBuilderDockWindow("Assets", dockLeft);
            ImGui::DockBuilderDockWindow("Inspector", dockRight);
            ImGui::DockBuilderDockWindow("Scene", dockMain);

            ImGui::DockBuilderFinish(dockspaceID);       // Применяем
        }

        // ---------- ASSETS WINDOW ----------

        ImGui::Begin("Assets");

        ImGui::Text("Root/");

        if (ImGui::Button("Create object"))              // Кнопка
        {
            sf::RectangleShape obj({30.f, 30.f});
            obj.setFillColor(sf::Color::Yellow);
            obj.setPosition(player.getPosition());
            spawnedObjects.push_back(obj);
        }

        ImGui::End();

        // ---------- INSPECTOR ----------

        ImGui::Begin("Inspector");
        ImGui::Text("Inspector placeholder");
        ImGui::End();

        // ---------- SCENE WINDOW ----------

        ImGui::Begin("Scene");

        ImVec2 avail = ImGui::GetContentRegionAvail();   // Свободное место

        if (avail.x > 0 && avail.y > 0)                  // Ресайз сцены
        {
            sf::Vector2u newSize(
                static_cast<unsigned>(avail.x),
                static_cast<unsigned>(avail.y)
            );

            if (scene.getSize() != newSize)
                scene.create(newSize.x, newSize.y);
        }

        scene.clear(sf::Color::Black);                   // Чистим сцену
        scene.draw(player);

        for (auto& obj : spawnedObjects)
            scene.draw(obj);

        scene.display();                                 // ВАЖНО

        ImGui::Image(                                    // Рисуем сцену
            scene.getTexture(),
            avail,
            sf::Vector2f(0.f, 1.f),                      // Flip Y
            sf::Vector2f(1.f, 0.f)
        );

        ImGui::End();

        // ---------- FINAL RENDER ----------

        window.clear(sf::Color::Black);
        ImGui::SFML::Render(window);
        window.display();
    }

    // ---------- SHUTDOWN ----------

    ImGui::SFML::Shutdown();
    return 0;
}
