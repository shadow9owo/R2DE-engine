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
}