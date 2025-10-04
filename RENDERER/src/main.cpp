#include "raylib.h"
#include <iostream>

#include "types.hpp"
#include "data.hpp"

#include "PARSER/parser.hpp"
#include "Utils/Log.hpp"

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	if (!parser::IsValid())
	{
		Utils::Log("corrupted");
		return 1; //corrupted
	}

	InitWindow(1280, 800, "game");

	RenderTexture2D text = LoadRenderTexture(1280,720);

	SetTextureFilter(text.texture, TEXTURE_FILTER_POINT);

	while (!WindowShouldClose())
	{
		BeginTextureMode(text);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("RENDERER GAME RENDERER", 200,200,20,WHITE);

		EndDrawing();

		EndTextureMode();
	}

	CloseWindow();
	return 0;
}
