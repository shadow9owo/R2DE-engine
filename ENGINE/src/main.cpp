#include "raylib.h"

#include "utils.h"
#include "window.hpp"
#include "main.hpp"

RenderTexture2D text;
Camera2D camera;

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);

	InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "GAME");

	SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));

	text = LoadRenderTexture(1280, 720);

	SetTextureFilter(text.texture, TEXTURE_FILTER_POINT);

	Window::DoInit();

	camera = { 0 };
	camera.target = { 0,0 };
	camera.offset = { 0,0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        BeginTextureMode(text);
        ClearBackground(RAYWHITE);

        Window::DoRender();

        EndTextureMode();

        DrawTexturePro(
            text.texture,
            Rectangle{ 0,0,(float)text.texture.width,-(float)text.texture.height },
            Rectangle{ 0,0,text.texture.width * (float)GetScreenWidth() / (float)text.texture.width, text.texture.height * (float)GetScreenHeight() / (float)text.texture.height },
            Vector2{ 0,0 },
            0.0f,
            WHITE
        );

        BeginMode2D(camera);
        Window::DoCameraRender();
        EndMode2D();

        EndDrawing();
    }


	UnloadRenderTexture(text);
	CloseWindow();
	return 0;
}
