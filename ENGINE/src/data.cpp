#ifdef _WIN32
#include <Windows.h>
#endif
#include "types.hpp"
#include <vector>
#include "data.hpp"
#include <string>

namespace data
{
	std::vector<Button> activebuttons;
	Project project;
	std::string filepath = "";
	std::vector<std::string> contentsofproject;
}