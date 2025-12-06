#pragma once

namespace rl
{
#include <raylib.h>
}
#include <string>
#include <cstdint> // for int64_t
#include <vector>
#include <memory>

#include "main.hpp"

namespace Types
{
    enum class LayerInts
    {
        AWAITING_WIPE = -9999,
        LAYER_APPLICATION_QUICK_ACTIONS = -1,
        LAYER_POPUP_MENU = 1,
        LAYER_WINDOW_DEFAULT = 2,
        LAYER_WINDOW_OVERLAY = 3, //important for messageboxes and such
        LAYER_DEBUG = 9999
    };

    enum class UniqueIds
    {
        NONE = -1,
        MOUSE_POS_ID = 1,
        FPS_ID = 2,
        SPAWN_WINDOW_ID = 3,
        LIST_WINDOW_ID = 4,
        SETTINGS_WINDOW_ID = 5,
        VSYNC_TOGGLE = 6,
        FRAMERATE_INPUT = 7
    };
    
    class Texture
    {
    public:
        rl::Texture2D texture;
        rl::Rectangle rect;
    };

    enum class PIVOT {
        TopLeft, TopMiddle, TopRight,
        MiddleLeft, Middle, MiddleRight,
        BottomLeft, BottomMiddle, BottomRight
    };

    enum class ValueType {
        INT, INT64, DOUBLE, FLOAT, CHAR, UNSIGNED_CHAR, PTR, STRING, NONE
    };

    union ValueData {
        int i;
        int64_t i64;
        double d;
        float f;
        unsigned char uc;
        char c;
        void* ptr;
        const char* str;

        ValueData() { ptr = nullptr; }
    };

    class Value {
        public:
            ValueType type;
            ValueData data;

            Value() : type(ValueType::NONE) {}

            Value(int v) { type = ValueType::INT; data.i = v; }
            Value(int64_t v) { type = ValueType::INT64; data.i64 = v; }
            Value(double v) { type = ValueType::DOUBLE; data.d = v; }
            Value(float v) { type = ValueType::FLOAT; data.f = v; }
            Value(char v) { type = ValueType::CHAR; data.c = v; }
            Value(void* v) { type = ValueType::PTR; data.ptr = v; }
            Value(unsigned char v) { type = ValueType::UNSIGNED_CHAR; data.uc = v; }
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
        r_div,
        r_mul,
        r_dec,
        r_inc,
        r_add,
        r_sub
    };

    class Node
    {
        public:
            opcodes type = r_nop;
            Value Arg1, Arg2, Arg3;
            Value Output;
    };

    class Layer
    {
        public:
            std::vector<UIObject> objects;
            LayerInts priority = LayerInts::LAYER_WINDOW_DEFAULT;

            inline void WipeAwait()
            {
                priority = LayerInts::AWAITING_WIPE;
                return;
            }

            inline void WipeNow() //unsafe
            {
                objects.clear();
                return;
            }
    };

    class Module
    {
        public:
            std::string name;
            Value Arg1, Arg2, Arg3;
            Value Output;
            void* eval = nullptr;
    };

    class FunctionUnion
    {
        public:
            Node node;
            Module module;
    };

    class Object
    {
        public:
            FunctionUnion function;
            rl::Vector2 position;

            Object() = default;
            Object(Object&&) = default;
            Object& operator=(Object&&) = default;

            Object(const Object&) = delete;
            Object& operator=(const Object&) = delete;
    };

    class Project
    {
        public:
            std::vector<std::unique_ptr<Object>> objects;
    };
}
