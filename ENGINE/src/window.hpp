#pragma once

namespace rl
{
#include <raylib.h>
}

namespace Window
{
	extern rl::Vector2 mouse;
	extern void DoInit();
	namespace callbacks
	{
		extern void DoButtonCallBacks();
		extern void DoInputCallbacksOnScreen();
		extern void DoInputCallbacksCamera();
	}
	extern void DoRender();
	extern void DoCameraRender();
}