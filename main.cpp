#include <SFML/Graphics.hpp>        // SFML графика
#include <SFML/Audio.hpp>          // SFML аудио (чтоб CMake не ныл)
#include <imgui.h>                 // Dear ImGui
#include <imgui-SFML.h>            // ImGui + SFML биндинг
#include <vector>                  // std::vector

int main()
{
    // ===== SFML WINDOW =====

    sf::RenderWindow window(
        sf::VideoMode(1280, 720),   // Размер окна
        "Meowy Engine V1",           // Заголовок
        sf::Style::Default           // Стандартный стиль
    );

    window.setFramerateLimit(60);   // Ограничение FPS

    // ===== IMGUI INIT =====

    ImGui::SFML::Init(window);      // Инициализация ImGui-SFML

    ImGuiIO& io = ImGui::GetIO();   // Доступ к IO

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // ВКЛЮЧАЕМ DOCKING
    io.IniFilename = nullptr;       // ОТКЛЮЧАЕМ imgui.ini

    // ===== STYLE (чтоб не серое говно) =====

    ImGuiStyle& style = ImGui::GetStyle(); // Получаем стиль
    style.WindowRounding = 4.f;      // Скругление окон
    style.FrameRounding  = 4.f;      // Скругление кнопок
    style.GrabRounding   = 4.f;      // Скругление слайдеров

    // ===== CLOCK =====

    sf::Clock deltaClock;            // Часы для deltaTime

    // ===== SCENE (SFML DRAW SPACE) =====

    sf::RenderTexture scene;         // RenderTexture для сцены
    scene.create(1280, 720);          // Начальный размер

    sf::RectangleShape test({50,50}); // Тестовый объект
    test.setFillColor(sf::Color::White);
    test.setPosition(100.f, 100.f);

    std::vector<sf::RectangleShape> objects; // Список объектов

    // ===== MAIN LOOP =====

    while (window.isOpen())
    {
        // ----- EVENTS -----

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event); // Передаём события ImGui

            if (event.type == sf::Event::Closed)      // Закрытие окна
                window.close();

            if (event.type == sf::Event::KeyPressed)  // Клавиши
            {
                if (event.key.code == sf::Keyboard::D)
                    test.move(10.f, 0.f);              // Двигаем объект
            }
        }

        // ----- IMGUI UPDATE -----

        ImGui::SFML::Update(window, deltaClock.restart());

        // ===== GLOBAL DOCKSPACE =====
        // Делает весь viewport док-зоной (Unity-style)

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        // ===== ASSETS WINDOW =====

        ImGui::Begin("Assets");        // Окно Assets

        ImGui::Text("Root/");          // Текст

        if (ImGui::Button("Create object")) // Кнопка
        {
            sf::RectangleShape obj({30,30});
            obj.setFillColor(sf::Color::Yellow);
            obj.setPosition(test.getPosition());
            objects.push_back(obj);    // Добавляем объект
        }

        ImGui::End();                  // Конец Assets

        // ===== SCENE WINDOW =====

        ImGui::Begin("Scene");         // Окно Scene

        ImVec2 avail = ImGui::GetContentRegionAvail(); // Свободное место

        // Меняем размер RenderTexture под окно
        if (avail.x > 0 && avail.y > 0)
        {
            sf::Vector2u newSize(
                static_cast<unsigned>(avail.x),
                static_cast<unsigned>(avail.y)
            );

            if (scene.getSize() != newSize)
                scene.create(newSize.x, newSize.y);
        }

        // Показываем RenderTexture в ImGui
        ImGui::Image(
            scene,                     // RenderTexture
            sf::Vector2f(avail.x, avail.y)
        );

        ImGui::End();                  // Конец Scene

        // ===== SFML RENDER =====

        scene.clear(sf::Color(26,26,26)); // Тёмный фон сцены
        scene.draw(test);                // Рисуем объект

        for (auto& obj : objects)
            scene.draw(obj);             // Рисуем остальные

        scene.display();                 // ОБЯЗАТЕЛЬНО display()

        // ===== FINAL DRAW =====

        window.clear(sf::Color::Black);  // Чистим окно
        ImGui::SFML::Render(window);     // Рендер ImGui
        window.display();                // Показываем кадр
    }

    // ===== SHUTDOWN =====

    ImGui::SFML::Shutdown();             // Корректное завершение
    return 0;
}
