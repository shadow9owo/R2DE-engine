#pragma once

#include "../json.hpp"
#include <fstream>
#include "../../types.hpp"
#include "../../data.hpp"
#include <memory>

namespace projecthandling
{
	namespace json
	{
		extern bool exporttofile(const Types::Project& project,std::string path);
		extern Types::Project importprojectfromfile(std::string path);
	}

	namespace f_export
	{
		extern bool f_export();
	}
	namespace f_import
	{
		extern bool f_import();
	}
}