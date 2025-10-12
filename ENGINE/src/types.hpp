#pragma once

namespace rl
{
    #include <raylib.h>
}

#include <string>
#include <cstdint> // for int64_t
#include <vector>
#include <memory>

enum class PIVOT {
    TopLeft,TopMiddle,TopRight,
    MiddleLeft,Middle,MiddleRight,
    BottomLeft,BottomMiddle,BottomRight
};

struct Button
{
	bool hovering = false;
	void* exec = nullptr;
	std::string text = "nul";
	bool disabled = false;
    rl::Vector2 position = { 0,0 }; //its like if this value got added up every time a new definition is made
    int fontsize = 24;
    rl::Font font = rl::GetFontDefault();
    rl::Rectangle MinMax = { INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX }; //disables it uncap format:: minx , miny, maxx, maxy
    PIVOT pivot = PIVOT::Middle;
    rl::Color Def = { rl::WHITE };
    rl::Color Onhover = { rl::DARKGRAY };
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
    r_mov,
    r_jne,
    r_je,
    r_jg,
    r_jge,
    r_jz,
    r_jl,
    r_jle,
    r_ret,
    r_cmp,
    r_nop,
    r_div, // cant define it as "div" so every op has r_ before it now so the compiler doesnt bitch
    r_mul,
    r_dec,
    r_inc
};

struct Node
{
    opcodes type = r_nop;
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

struct FunctionUnion
{
    Node node;
    Module module;

    FunctionUnion() {}
    ~FunctionUnion() {}

    FunctionUnion(FunctionUnion&& other) noexcept
    {
        node = std::move(other.node);
        module = std::move(other.module);
    }

    FunctionUnion& operator=(FunctionUnion&& other) noexcept
    {
        if (this != &other)
        {
            node = std::move(other.node);
            module = std::move(other.module);
        }
        return *this;
    }

    FunctionUnion(const FunctionUnion&) = delete;
    FunctionUnion& operator=(const FunctionUnion&) = delete;
};

struct Object
{
    FunctionUnion function;
    rl::Vector2 position; // throw away later useless info

    Object() = default;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;

    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
};

struct Project
{
    std::vector<std::unique_ptr<Object>> objects;
};