#include <string>

#include "../data.hpp"
#include "../types.hpp"

#include <raylib.h>
#include <limits>

#include <fstream>
#include <iostream>
#include <vector>

namespace parser
{
	namespace emulator
	{
		std::vector<std::pair<Value, Value>> hardcodedpairs = {
			{"PI", 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f},
			{"NUL", _I64_MAX}
		};

		std::vector<std::pair<Value, Value>> dynamicpairs = {
			{"DELTA", GetFrameTime()},
			{"FPSLIMIT", 60}
		};

		std::vector<std::pair<Value, Value>> variables;

		std::vector<Value> pointerarr;
	}

	bool IsValid(std::string str)
	{
		std::ifstream file(str);

		if (!file) {
			return false;
		}

		binaryname = str; // file name
		return true;
	}

	void Load()
	{
		emulator::pointerarr = {}; //wipe it so if somehow magically somehow i call this again (which shouldnt happen) then nothing happens

		// THIS WHOLE THING IS INIT DO NOT REMOVE IT ITS IMPORTANT RETARD!
		for(std::pair<Value, Value>& a : emulator::hardcodedpairs)
		{
			emulator::pointerarr.push_back((void*)&a.first); //gives address again heap garbage for emulatr
		}

		for (std::pair<Value, Value>& a : emulator::dynamicpairs)
		{
			emulator::pointerarr.push_back((void*)&a.first);
		}

		for (std::pair<Value, Value>& a : emulator::variables)
		{
			emulator::pointerarr.push_back((void*)&a.first);
		}
		return;
	}
}