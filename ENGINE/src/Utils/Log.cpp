#include <string>
#include <iostream>
#include "Log.hpp"

#include "wrapper/pfdwrapper.hpp"

namespace Utils
{
	void Log(std::string str)
	{
		std::cout << str << std::endl;
		return;
	}

	void LogFatal(std::string title, std::string message)
	{
		wrapper::LogErr(message.c_str());
		return;
	}
}