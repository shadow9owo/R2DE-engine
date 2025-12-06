#include "Toggle.hpp"

namespace rl
{
#include <raylib.h>
}

#include "Label.hpp"

#include "types.hpp"

class Toggle
{
public:
    rl::Rectangle rect;
    bool toggled = false;
    rl::Texture2D toggletexture = {};
    Label text;
    void (*callback)(Toggle*) = nullptr; //on press
    Types::UniqueIds uniqueid = Types::UniqueIds::NONE;

    void Pressed()
    {
        callback(this);
        return;
    }
};