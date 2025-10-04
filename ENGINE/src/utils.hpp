#pragma once

#include <raylib.h>
#include "types.hpp"

extern int offset;
extern bool debug;

extern bool shouldclose;

extern bool HasProjects();
extern Rectangle GetButtonSize(Button& button);
extern Vector2 Qmessure(Button& button); //quick messure

extern Vector2 GetMousePosPro();