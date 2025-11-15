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

	bool dragging = false;

	namespace config
	{
		int framerate = 24;
		bool vsync = true;

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
			
			if (!DG2D::INI::getvalue("vsync", buffer))
			{
				vsync = (bool)1;
				DG2D::INI::setvalue("vsync", "1");
			}
			else {
				vsync = (bool)std::atoi(buffer.c_str());
			}
		}

		void updateini()
		{
			std::string buffer;

			DG2D::INI::filename = "config.ini";

			buffer = std::to_string(framerate);
			DG2D::INI::setvalue("framerate", buffer.c_str());

			rl::SetTargetFPS(framerate);

			buffer = std::to_string((int)vsync);
			DG2D::INI::setvalue("vsync", buffer.c_str());

			if (vsync)
			{
				rl::SetWindowState(rl::FLAG_VSYNC_HINT);
			}
			else {
				rl::ClearWindowState(rl::FLAG_VSYNC_HINT);
			}

			return;
		}
	}
}