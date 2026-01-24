//
// Created by mew on 1/25/26.
//

#pragma once
#include "includesh.h"

#ifndef MEOWYGAMEENGINE_WINDOWS_H
#define MEOWYGAMEENGINE_WINDOWS_H

#endif //MEOWYGAMEENGINE_WINDOWS_H

extern sf::RenderTexture scene;

// ---------- ASSETS WINDOW ----------

namespace meowyengine
{
    inline void defaultwindows()
    {
        ImGui::Begin("General");
        ImGui::BeginTabBar("hello");
        if (ImGui::BeginTabItem("smthing"))
        {
            ImGui::Text("Hello from SMTHING");

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("cube"))
        {
            ImGui::Text("Hello from cube");

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
        ImGui::End();

        // ---------- SCENE WINDOW ----------

        ImGui::Begin("Scene");

        // доступная область внутри окна Scene
        ImVec2 avail = ImGui::GetContentRegionAvail();

        // минимальная защита
        if (avail.x < 1.f) avail.x = 1.f;
        if (avail.y < 1.f) avail.y = 1.f;

        // если размер изменился — пересоздаём RenderTexture
        if (scene.getSize().x != (unsigned)avail.x ||
            scene.getSize().y != (unsigned)avail.y)
        {
            scene.create(
                static_cast<unsigned>(avail.x),
                static_cast<unsigned>(avail.y)
            );
        }

        // рисуем 1:1, БЕЗ scale
        ImGui::Image(scene, avail);

        ImGui::End();
    }
}