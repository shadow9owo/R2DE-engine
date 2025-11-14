#ifdef _WIN32
#include <Windows.h>
#endif
#include "types.hpp"
#include <vector>
#include "data.hpp"
#include <string>
#include <raylib.h>

namespace data
{
	Types::Project project = {};
	std::string filepath = "";
	std::vector<std::string> contentsofproject = {};

	// headers
	Types::Layer rootlayer;
	std::vector<Types::Layer> Layers;

	bool wipedrop = false;
}