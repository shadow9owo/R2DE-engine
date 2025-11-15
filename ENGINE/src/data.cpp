#ifdef _WIN32
#include <Windows.h>
#endif
#include "types.hpp"
#include <vector>
#include "data.hpp"
#include <string>
#include <raylib.h>

#include "ini/ini.hpp"

namespace data
{
	Types::Project project = {};
	std::string filepath = "";
	std::vector<std::string> contentsofproject = {};

	// headers
	Types::Layer rootlayer;
	std::vector<Types::Layer> Layers;

	bool wipedrop = false;

	namespace config
	{
		int framerate = 24;

		void parseini()
		{
			std::string buffer;

			DG2D::INI::filename = "config.ini";
			if (!DG2D::INI::getvalue("framerate",buffer))
			{
				framerate = 24;
				DG2D::INI::setvalue("framerate", "24");
			}
			else {
				framerate = std::atoi(buffer.c_str());
			}
		}
	}
}