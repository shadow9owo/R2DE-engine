#include <iostream>
#include <sys/stat.h>

#include "types.hpp"
#include <raylib.h>

#include "main.hpp"

int offset = 16; //idk depends ig

bool HasProjects()
{
	struct stat sb = {};

	if (stat("projects", &sb) != 0)
	{
		return false;
	}

	return true;
}

Rectangle GetButtonSize(Button& button)
{
	Vector2 sizeinfo = MeasureTextEx(button.font, button.text.c_str(), button.fontsize, 0.2f);
	Rectangle rect = { button.position.x, button.position.y, sizeinfo.x * 2, sizeinfo.y * 2 };

	float scaleX = (float)GetScreenWidth() / (float)text.texture.width;
	float scaleY = (float)GetScreenHeight() / (float)text.texture.height;

	sizeinfo = {};

	return rect;
}




Vector2 GetMousePosPro()
{
	Vector2 output = { (int)(GetMouseX() / ((float)GetScreenWidth() / text.texture.width)),
	(int)(GetMouseY() / ((float)GetScreenHeight() / text.texture.height)) };

	return output;
}
