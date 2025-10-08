#ifdef _WIN32
#include <Windows.h>
#endif


namespace rl
{
	#include "raylib.h"
}
#include <iostream>

#include "types.hpp"
#include "data.hpp"

#include "PARSER/parser.hpp"
#include "Utils/Log.hpp"

int main ()
{
	rl::SetConfigFlags(rl::FLAG_VSYNC_HINT | rl::FLAG_WINDOW_HIGHDPI);

	if (!parser::IsValid())
	{
		Utils::Log("corrupted");
		return 1; //corrupted
	}

	rl::InitWindow(1280, 800, "game");

	rl::RenderTexture2D text = rl::LoadRenderTexture(1280,720);

	rl::SetTextureFilter(text.texture, rl::TEXTURE_FILTER_POINT);

	while (!rl::WindowShouldClose())
	{
		BeginTextureMode(text);

		rl::BeginDrawing();

		rl::ClearBackground(rl::BLACK);

		rl::DrawText("RENDERER GAME RENDERER", 200,200,20, rl::WHITE);

		rl::EndDrawing();

		rl::EndTextureMode();
	}

	rl::CloseWindow();
	return 0;
}
