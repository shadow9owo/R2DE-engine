#pragma once

namespace rl
{
#include <raylib.h>
}

#include "types.hpp"

namespace Window
{
	namespace callbacks
	{
		extern void DoLabelFieldCallBacks();
		extern void WipeLayer(Types::Layer input);
		extern void UpdateDebugValues(int arg, void* ptr);
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