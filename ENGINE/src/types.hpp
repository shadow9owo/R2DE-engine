#pragma once

namespace rl
{
    #include <raylib.h>
}
#include <string>

#include <cstdint> // for int64_t

#include <vector>

struct Button
{
	bool hovering = false;
	void* exec = nullptr;
	std::string text = "nul";
	bool disabled = false;
    rl::Vector2 position = { 0,0 }; //its like if this value got added up every time a new definition is made
    int fontsize = 24;
    rl::Font font = rl::GetFontDefault();
};

enum class ValueType {
    INT, INT64, FLOAT, CHAR, PTR, STRING, NONE
};

union ValueData {
    int i;
    int64_t i64;
    float f;
    char c;
    void* ptr;
    const char* str;

    ValueData() { ptr = nullptr; }
};

struct Value {
    ValueType type;
    ValueData data;

    Value() : type(ValueType::NONE) {}

    Value(int v) { type = ValueType::INT; data.i = v; }
    Value(int64_t v) { type = ValueType::INT64; data.i64 = v; }
    Value(float v) { type = ValueType::FLOAT; data.f = v; }
    Value(char v) { type = ValueType::CHAR; data.c = v; }
    Value(void* v) { type = ValueType::PTR; data.ptr = v; }
    Value(const char* v) { type = ValueType::STRING; data.str = v; }
};


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

struct Node
{
    opcodes type = nop;
    Value Arg1, Arg2, Arg3;
    Value Output;
};

struct Module
{
    std::string name;
    Value Arg1, Arg2, Arg3;
    Value Output;
    void* eval;
};

union FunctionUnion {
    Node node;
    Module module;

    FunctionUnion() {}
    ~FunctionUnion() {}
};

struct Object
{
    FunctionUnion function;
    rl::Vector2 position; //editor specific discard on compilation or set to nullptr
};

struct Project
{
    std::vector<Object> objects;
};