#pragma once

#include <raylib.h>

namespace Window
{
	extern Vector2 mouse;
	extern void DoInit();
	namespace callbacks
	{
		extern void DoButtonCallBacks();
	}
	extern void DoRender();
	extern void DoCameraRender();
}