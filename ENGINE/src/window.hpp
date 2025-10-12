#pragma once

namespace rl
{
#include <raylib.h>
}

namespace Window
{
	extern rl::Vector2 mouse;
	extern void DoInit();

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
		extern void DoButtonCallBacks();
		extern void DoInputCallbacksOnScreen();
		extern void DoInputCallbacksCamera();
	}
	extern void debug();
	extern void DoRender();
	extern void DoCameraRender();
}