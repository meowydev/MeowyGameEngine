//
// Created by mew on 1/26/26.
//

#ifndef MEOWYGAMEENGINE_HLANGRUNTIME_H
#define MEOWYGAMEENGINE_HLANGRUNTIME_H

#endif //MEOWYGAMEENGINE_HLANGRUNTIME_H

#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <spdlog/spdlog.h>

namespace HLang
{
    inline void exec(const std::string& cmd)
    {
        std::istringstream stream(cmd);
        std::string line;

        while (std::getline(stream, line))
        {
            if (line.empty())
                continue;

            // test cmd
            if (line.starts_with("print"))
            {
                auto firstQuote = line.find('"');
                auto lastQuote = line.rfind('"');

                if (firstQuote != std::string::npos && lastQuote != std::string::npos && firstQuote < lastQuote) //honestly idk what does that even mean i will ask chatgpt later
                {
                    std::string cmdrl = line.substr(firstQuote + 1, lastQuote - firstQuote - 1); // same for this

                    spdlog::info("cmdrl: " + cmdrl);

                }

                else
                {
                    spdlog::info("cmdrl: i heta you");
                }

            }
        }
    }
}