//
// Created by mew on 2/4/26.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map> // what?

#ifndef MEOWYGAMEENGINE_TYPES_H
#define MEOWYGAMEENGINE_TYPES_H

#endif //MEOWYGAMEENGINE_TYPES_H

namespace HLang
{
    struct MObject
    {
        // fuck you if you are reading this code because if youre trying to add your own types you will break everything into pieces and i wasted many hours on this thing and you just say that you want to replace them with better types? no fuck you.
        std::string id;
        sf::RectangleShape shape;
    };
    //extern std::unordered_map<std::string, MObject> objects;

}

struct assembly
{
    int bit 2;
    std::string country;
    std::unordered_map<std::string, std::string> usa;
};