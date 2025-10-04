#include <string>
#include <iostream>
#include "Log.hpp"

namespace Utils
{
	void Log(std::string str)
	{
		std::cout << str << std::endl;
		return;
	}
}