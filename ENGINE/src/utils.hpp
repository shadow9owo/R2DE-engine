#pragma once

namespace rl
{
#include <raylib.h>
}
#include "types.hpp"

extern int offset;
extern bool debug;

extern bool shouldclose;

extern bool HasProjects();
extern rl::Rectangle GetButtonSize(Button& button);
extern rl::Vector2 Qmessure(Button& button); //quick messure

extern rl::Vector2 GetMousePosPro();