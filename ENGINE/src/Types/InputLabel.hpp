#pragma once

namespace rl
{
#include <raylib.h>
}
#include "types.hpp"
#include <string>

#include "Label.hpp"

class InputLabel
{
public:
    rl::Rectangle rect;
    Label Label = {};
    rl::Color bgcolor = { 192,192,192,255 };
    std::string value = {};
    std::string regex = ".*";
    int scrolloffset = 0;
    bool focused = false;
    void (*callback)() = nullptr; //on char pressed
    Types::UniqueIds uniqueid = Types::UniqueIds::NONE;
};
