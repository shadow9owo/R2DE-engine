#pragma once

#include "types.hpp"
#include <vector>
#include <string>

namespace data
{
	extern Types::Project project;
	extern std::string filepath;
	extern std::vector<std::string> contentsofproject;

	extern Types::Window rootwindow;
	extern std::vector<Types::Window> windows;
}