#pragma once

#include "types.hpp"
#include <vector>
#include <string>

namespace data
{
	extern Types::Project project;
	extern std::string filepath;
	extern std::vector<std::string> contentsofproject;

	extern Types::Layer rootlayer;
	extern std::vector<Types::Layer> Layers;

	extern bool wipedrop;

	extern bool dragging;
	
	namespace config
	{
		extern int framerate;
		extern bool vsync;

		extern void parseini();
		extern void updateini();
	}
}