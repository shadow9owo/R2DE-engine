#pragma once

namespace rl
{
#include <raylib.h>
}

#include <string>
#include <cstdint> // for int64_t
#include <vector>
#include <memory>

namespace Types
{
    namespace LayerInts
    {
        constexpr int LAYER_APPLICATION_QUICK_ACTIONS = -1;
        constexpr int LAYER_POPUP_MENU = 1;
        constexpr int LAYER_DEBUG = 9999;
    }

    namespace UniqueIds
    {
        constexpr int MOUSE_POS_ID = 1;
        constexpr int FPS_ID = 2;
    }

    enum class PIVOT {
        TopLeft, TopMiddle, TopRight,
        MiddleLeft, Middle, MiddleRight,
        BottomLeft, BottomMiddle, BottomRight
    };

    struct Button
    {
        bool hovering = false;
        void (*exec)() = nullptr;
        std::string text = "nul";
        bool disabled = false;
        rl::Vector2 position = { 0,0 };
        int fontsize = 24;
        rl::Font font = rl::GetFontDefault();
        rl::Rectangle MinMax = { INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX };
        PIVOT pivot = PIVOT::Middle;
        rl::Color Def = rl::WHITE;
        rl::Color Onhover = rl::DARKGRAY;
        int uniqueid = -1;
    };

    struct Label
    {
        int fontsize = 8;
        std::string text = "nul";
        rl::Font font = rl::GetFontDefault();
        PIVOT pivot = PIVOT::Middle;
        rl::Rectangle MinMax = { INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX };
        rl::Vector2 position = { 0,0 };
        void (*callback)(int, void*) = nullptr;
        rl::Color Def = rl::BLACK;      // was {0,0,0,0}, invisible by default
        rl::Color Onhover = rl::DARKGRAY;
        int uniqueid = -1;
    };

    enum UIObjectType
    {
        None,
        _Button,
        _Window,
        _Label
    };

    struct Window;

    struct UIObject
    {
        UIObjectType type = None;
        Button btn{};
        Label lbl{};
        Window* win = nullptr;

        UIObject() = default;
        ~UIObject() = default;

        UIObject(const Button& b) : type(_Button), btn(b), lbl(), win(nullptr) {}
        UIObject(Button&& b) noexcept : type(_Button), btn(std::move(b)), lbl(), win(nullptr) {}

        UIObject(const Label& b) : type(_Label), btn(), lbl(b), win(nullptr) {}
        UIObject(Label&& b) noexcept : type(_Label), btn(), lbl(std::move(b)), win(nullptr) {}

        UIObject(Window* b) : type(_Window), btn(), lbl(), win(b) {}
        UIObject(Window& b) : type(_Window), btn(), lbl(), win(&b) {}

        UIObject(const UIObject&) = default;
        UIObject& operator=(const UIObject&) = default;
        UIObject(UIObject&&) noexcept = default;
        UIObject& operator=(UIObject&&) noexcept = default;
    };

    struct Window
    {
        bool disabled = false;
        std::string title = "undefined";
        rl::Rectangle rect = {};
        std::vector<UIObject> elements;
        int uniqueid = -1;
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

    struct Value {
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

    struct Node
    {
        opcodes type = r_nop;
        Value Arg1, Arg2, Arg3;
        Value Output;
    };

    struct Layer
    {
        std::vector<UIObject> objects;
        int priority = 0;
    };

    struct Module
    {
        std::string name;
        Value Arg1, Arg2, Arg3;
        Value Output;
        void* eval = nullptr;
    };

    struct FunctionUnion
    {
        Node node;
        Module module;

        FunctionUnion() = default;
        ~FunctionUnion() = default;

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
        rl::Vector2 position;

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
}
