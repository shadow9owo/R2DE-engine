#pragma once

namespace rl
{
#include <raylib.h>
}

#include <string>

#include "types.hpp"

class Label
{
public:
    int fontsize = 8;
    std::string text = "nul";
    rl::Font font = rl::GetFontDefault();
    Types::PIVOT pivot = Types::PIVOT::Middle;
    rl::Rectangle MinMax = { INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX };
    rl::Vector2 position = { 0,0 };
    void (*callback)(void*) = nullptr;
    rl::Color Def = rl::BLACK;// was {0,0,0,0}, invisible by default
    rl::Color Onhover = rl::DARKGRAY;
    Types::UniqueIds uniqueid = Types::UniqueIds::NONE;

    void Render();
};