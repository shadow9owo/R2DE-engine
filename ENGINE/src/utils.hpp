#pragma once

namespace rl
{
#include <raylib.h>
}
#include "types.hpp"

extern int offset;
extern bool debug;

extern const rl::Vector2 BaseTexture; 

extern bool shouldclose;

extern bool HasProjects();
extern rl::Rectangle GetButtonSize(Types::Button& button);
extern rl::Vector2 Qmessure(Types::Button& button); //quick messure

extern float clamp(float value, float min, float max);

extern rl::Vector2 GetMousePosPro();