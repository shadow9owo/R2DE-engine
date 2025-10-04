#pragma once

#include <string>

namespace Utils
{
	extern void Log(std::string str = "none");
	extern void LogFatal(std::string title = "none", std::string message = "none");
}