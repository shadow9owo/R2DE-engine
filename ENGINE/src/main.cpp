#ifdef _WIN32
#include <Windows.h>
#endif

namespace rl
{
    #include "raylib.h"
}

#include "Utils/Log.hpp"
#include "window.hpp"
#include "main.hpp"

#include "utils.hpp"

rl::RenderTexture2D text;
rl::Camera2D camera;

int main()
{
    rl::SetConfigFlags(rl::FLAG_VSYNC_HINT | rl::FLAG_WINDOW_HIGHDPI | rl::FLAG_WINDOW_RESIZABLE);

    rl::InitWindow((int)BaseTexture.x, (int)BaseTexture.y, "GAME");

    if (rl::GetMonitorWidth(rl::GetCurrentMonitor()) < BaseTexture.x || rl::GetMonitorHeight(rl::GetCurrentMonitor()) < BaseTexture.y)
    {
        Utils::LogFatal("Initialization error", "screen sizes below 720p are not supported");
        return -1; //crash the ui is not made for such small resolutions
    }

    rl::SetWindowMinSize((int)BaseTexture.x, (int)BaseTexture.y);

	text = rl::LoadRenderTexture((int)BaseTexture.x, (int)BaseTexture.y);

    rl::SetTextureFilter(text.texture, rl::TEXTURE_FILTER_POINT);

    rl::SetExitKey(rl::KEY_RIGHT_CONTROL);

    rl::SetTargetFPS(24);

	Window::DoInit();

	camera = { 0 };
	camera.target = { 0,0 };
	camera.offset = { 0,0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

    while (!rl::WindowShouldClose() && !::shouldclose)
    {
        if (rl::IsWindowResized())
        {
            rl::Vector2 size = { (float)rl::GetScreenWidth(), (float)rl::GetScreenHeight() };
            rl::UnloadRenderTexture(text); // i hate this
            text = rl::LoadRenderTexture((int)size.x, (int)size.y);
            Window::DoRender();
        }

        rl::BeginDrawing();

        rl::ClearBackground(rl::WHITE);

        rl::BeginTextureMode(text);
        rl::ClearBackground(rl::RAYWHITE);

        Window::DoRender();

        rl::EndTextureMode();

        rl::DrawTexturePro(
            text.texture,
            rl::Rectangle{ 0,0,(float)text.texture.width,-(float)text.texture.height },
            rl::Rectangle{ 0,0,(float)rl::GetScreenWidth(), (float)rl::GetScreenHeight() },
            rl::Vector2{ 0,0 },
            0.0f,
            rl::WHITE
        );

        rl::BeginMode2D(camera);
        Window::DoCameraRender();
        rl::EndMode2D();

        rl::EndDrawing();
    }

    rl::UnloadRenderTexture(text);
    rl::CloseWindow();
	return 0;
}
