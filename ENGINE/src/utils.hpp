#pragma once

namespace rl
{
#include <raylib.h>
}

namespace Types {
    class Button;
    class Label;
    class Toggle;
    class InputLabel;
    class UIObject;
    class Window;
}

extern int offset;
extern bool debug;

extern const rl::Vector2 BaseTexture; 

extern bool shouldclose;

extern bool HasProjects();
extern rl::Rectangle GetButtonSize(Types::Button& button);
extern rl::Vector2 Qmessure(Types::Button& button); //quick messure

extern float clamp(float value, float min, float max);

extern rl::Vector2 GetMousePosPro();