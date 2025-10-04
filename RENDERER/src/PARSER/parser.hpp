#pragma once

#include <string>
#include <vector>

namespace parser
{
	extern bool IsValid(std::string str = "game.bin");
	extern void Load();

	namespace emulator
	{
		extern std::vector<std::pair<Value, Value>> variables;
		extern std::vector<std::pair<Value, Value>> hardcodedpairs;
		extern std::vector<std::pair<Value, Value>> dynamicpairs;

		extern std::vector<Value> pointerarr; // important for the heap

		enum opcodes
		{
			mov,
			jne,
			je,
			jg,
			jge,
			jz,
			jl,
			jle,
			ret,
			cmp,
			nop
		};
	}
}