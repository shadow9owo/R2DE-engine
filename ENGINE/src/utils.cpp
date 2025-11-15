#ifdef _WIN32
#include <Windows.h>
#endif

namespace rl
{
	#include <raylib.h>
}

#include <iostream>
#include <sys/stat.h>

#include "types.hpp"

#include "main.hpp"
#include "utils.hpp"

const rl::Vector2 BaseTexture = { 1280,720 };

int offset = 16; //idk depends ig
bool debug = true;

bool shouldclose = false;


float clamp(float value, float min, float max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

bool HasProjects()
{
	struct stat sb = {};

	if (stat("projects", &sb) != 0)
	{
		return false;
	}

	return true;
}

rl::Rectangle GetButtonSize(Types::Button& button)
{
	rl::Vector2 sizeinfo = rl::MeasureTextEx(button.font, button.text.c_str(), (int)button.fontsize, 0.2f);
	rl::Rectangle rect = { button.position.x, button.position.y, sizeinfo.x * 2, sizeinfo.y * 2 };

	float scaleX = (float)rl::GetScreenWidth() / (float)text.texture.width;
	float scaleY = (float)rl::GetScreenHeight() / (float)text.texture.height;

	sizeinfo = {};

	return rect;
}

rl::Rectangle GetToggleSize(Types::Button& button)
{
	rl::Vector2 sizeinfo = rl::MeasureTextEx(button.font, button.text.c_str(), (int)button.fontsize, 0.2f);
	rl::Rectangle rect = { button.position.x, button.position.y, sizeinfo.x * 2, sizeinfo.y * 2 };

	float scaleX = (float)rl::GetScreenWidth() / (float)text.texture.width;
	float scaleY = (float)rl::GetScreenHeight() / (float)text.texture.height;

	sizeinfo = {};

	return rect;
}

rl::Vector2 Qmessure(Types::Button& button)
{
	rl::Rectangle rect = GetButtonSize(button);
	return { rect.width, rect.height };
}

rl::Vector2 GetMousePosPro()
{
	rl::Vector2 output = { (int)(rl::GetMouseX() / ((float)rl::GetScreenWidth() / text.texture.width)),
	(int)(rl::GetMouseY() / ((float)rl::GetScreenHeight() / text.texture.height)) };

	return output;
}


