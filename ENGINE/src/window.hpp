#pragma once

namespace rl
{
#include <raylib.h>
}


namespace Window
{
	namespace callbacks
	{
		extern void DoLabelFieldCallBacks();
		extern void UpdateDebugValues(void* ptr);
		extern void RenderAllLayers();
		extern void DoInput();
		extern void DoButtonCallBacks();
		extern void DoInputCallbacksOnScreen();
		extern void DoInputCallbacksCamera();
	}

	extern rl::Vector2 mouse;
	extern void DoInit();

	extern void debug();
	extern void DoRender();
	extern void DoCameraRender();

	namespace UI
	{
		namespace SpawnerDrop
		{
			extern void WipePreDrop();
			extern void WipeDrop();
			extern void SpawnFunction();
			extern void List();
			extern void Delete();
		}
	}
}