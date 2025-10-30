#pragma once

namespace rl
{
#include <raylib.h>
}

#include "types.hpp"

namespace Window
{
	extern rl::Vector2 mouse;
	extern void DoInit();

	extern void debug();
	extern void DoRender();
	extern void DoCameraRender();

	namespace UI
	{
		namespace SpawnerDrop
		{
			extern void WipeDrop();
			extern void SpawnFunction();
			extern void MakeModule();
			extern void List();
			extern void Delete();
		}
	}

	namespace callbacks
	{
		extern void RenderAllLayers();
		extern void DoInput();
		extern void DoButtonCallBacks();
		extern void DoInputCallbacksOnScreen();
		extern void DoInputCallbacksCamera();
	}
}