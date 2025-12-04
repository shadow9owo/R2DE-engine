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

    class Button
    {
    public:
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

        inline void Disable()
        {
            disabled = true;
            return;
        }

        inline void Enable()
        {
            disabled = false;
            return;
        }

        inline void Exec()
        {
            exec();
            return;
        }
    };

    class Label
    {
        public:
            int fontsize = 8;
            std::string text = "nul";
            rl::Font font = rl::GetFontDefault();
            PIVOT pivot = PIVOT::Middle;
            rl::Rectangle MinMax = { INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX };
            rl::Vector2 position = { 0,0 };
            void (*callback)(void*) = nullptr;
            rl::Color Def = rl::BLACK;// was {0,0,0,0}, invisible by default
            rl::Color Onhover = rl::DARKGRAY;
            UniqueIds uniqueid = UniqueIds::NONE;

            inline void Render()
            {
                callback(this);
                return;
            }
    };

    class Toggle
    {
        public:
            rl::Rectangle rect;
            bool toggled = false;
            rl::Texture2D toggletexture = {};
            Label text;
            void (*callback)(Toggle*) = nullptr; //on press
            UniqueIds uniqueid = UniqueIds::NONE;

            inline void Pressed()
            {
                callback(this);
                return;
            }
    };

    class InputLabel
    {
        public: 
            rl::Rectangle rect;
            Label Label = {};
            rl::Color bgcolor = { 192,192,192,255 };
            std::string value = {};
		    std::string regex = ".*";
            int scrolloffset = 0;
            bool focused = false;
            void (*callback)() = nullptr; //on char pressed
		    UniqueIds uniqueid = UniqueIds::NONE;
    };

    enum UIObjectType
    {
        None,
        _Button,
        _Window,
        _Label,
        _InputLabel,
        _Toggle
    };

    class Window;

    class UIObject
    {
        public:
            UIObjectType type = None;
            Button btn{};
            Label lbl{};
            Window* win;
            InputLabel ilb{};
            Toggle tog{};

            int windowIndex = 0;

            UIObject() = default;

            UIObject(const Button& b) : type(_Button), btn(b) {}
            UIObject(Button&& b) noexcept : type(_Button), btn(std::move(b)) {}

            UIObject(const Label& b) : type(_Label), lbl(b) {}
            UIObject(Label&& b) noexcept : type(_Label), lbl(std::move(b)) {}

            UIObject(Window* w) : type(_Window), win(w) {}

            UIObject(const InputLabel& b) : type(_InputLabel), ilb(b) {}
            UIObject(InputLabel&& b) noexcept : type(_InputLabel), ilb(std::move(b)) {}

            UIObject(const Toggle& b) : type(_Toggle), tog(b) {}
            UIObject(Toggle&& b) noexcept : type(_Toggle), tog(std::move(b)) {}
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

    class Window
    {
        private:
            float clamp(float value, float min, float max)
            {
                if (value < min) return min;
                if (value > max) return max;
                return value;
            }

            rl::Rectangle GetButtonSize(Types::Button& button)
            {
                rl::Vector2 sizeinfo = rl::MeasureTextEx(button.font, button.text.c_str(), (int)button.fontsize, 0.2f);
                rl::Rectangle rect = { button.position.x, button.position.y, sizeinfo.x * 2, sizeinfo.y * 2 };

                float scaleX = (float)rl::GetScreenWidth() / (float)text.texture.width;
                float scaleY = (float)rl::GetScreenHeight() / (float)text.texture.height;

                sizeinfo = {};

                return rect;
            }
        public:
            bool disabled = false;
            std::string title = "undefined";
            rl::Rectangle rect = {};
            std::vector<UIObject> elements;
            UniqueIds uniqueid = UniqueIds::NONE;
            rl::Color bgcolor = { 255,255,255,255 };
            void (*callback)(Types::Layer*) = nullptr;
            LayerInts currentlayer;

            inline void Disable()
            {
                disabled = true;
                return;
            }

            inline void Enable()
            {
                disabled = false;
                return;
            }

            inline void WipeAwait()
            {
                currentlayer = LayerInts::AWAITING_WIPE;
                return;
            }

            inline void RenderSubUIElementHelper(Types::UIObject _Object)
            {
                if (_Object.type == Types::_Button)
                {
                    Types::Button& btn = _Object.btn;

                    rl::Rectangle getsize = GetButtonSize(btn);

                    getsize.width = clamp(getsize.width, (int)btn.MinMax.x, (int)btn.MinMax.width);
                    getsize.height = clamp(getsize.height, (int)btn.MinMax.y, (int)btn.MinMax.height);

                    rl::Vector2 text = MeasureTextEx(btn.font, btn.text.c_str(), btn.fontsize, 0.2f);

                    rl::Color bgColor = btn.hovering ? btn.Onhover : btn.Def;
                    rl::DrawRectanglePro({ btn.position.x, btn.position.y, getsize.width, getsize.height }, { 0,0 }, 0, bgColor);

                    rl::Vector2 textPos = btn.position;

                    switch (btn.pivot)
                    {
                    case Types::PIVOT::TopLeft:
                        textPos.x -= getsize.width * 0.5f;
                        textPos.y -= getsize.height * 0.5f;
                        break;

                    case Types::PIVOT::TopMiddle:
                        textPos.x -= text.x * 0.5f;
                        textPos.y -= getsize.height * 0.5f;
                        break;

                    case Types::PIVOT::TopRight:
                        textPos.x -= (getsize.width - text.x);
                        textPos.y -= getsize.height * 0.5f;
                        break;

                    case Types::PIVOT::MiddleLeft:
                        textPos.x -= getsize.width * 0.5f;
                        textPos.y -= text.y * 0.5f;
                        break;

                    case Types::PIVOT::Middle:
                        textPos.x -= text.x * 0.5f;
                        textPos.y -= text.y * 0.5f;
                        break;

                    case Types::PIVOT::MiddleRight:
                        textPos.x -= (getsize.width - text.x);
                        textPos.y -= text.y * 0.5f;
                        break;

                    case Types::PIVOT::BottomLeft:
                        textPos.x -= getsize.width * 0.5f;
                        textPos.y -= (getsize.height - text.y);
                        break;

                    case Types::PIVOT::BottomMiddle:
                        textPos.x -= text.x * 0.5f;
                        textPos.y -= (getsize.height - text.y);
                        break;

                    case Types::PIVOT::BottomRight:
                        textPos.x -= (getsize.width - text.x);
                        textPos.y -= (getsize.height - text.y);
                        break;
                    }


                    rl::DrawTextPro(btn.font, btn.text.c_str(), textPos, { 0,0 }, 0, btn.fontsize, 0.2f, rl::WHITE);
                }
                else if (_Object.type == Types::_Label)
                {
                    Types::Label& lbl = _Object.lbl;

                    rl::Vector2 textSize = MeasureTextEx(lbl.font, lbl.text.c_str(), lbl.fontsize, 0.2f);
                    rl::Vector2 pos = lbl.position;

                    switch (lbl.pivot)
                    {
                    case Types::PIVOT::TopLeft:
                        // pos stays as-is
                        break;

                    case Types::PIVOT::TopMiddle:
                        pos.x -= textSize.x * 0.5f;
                        break;

                    case Types::PIVOT::TopRight:
                        pos.x -= textSize.x;
                        break;

                    case Types::PIVOT::MiddleLeft:
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::Middle:
                        pos.x -= textSize.x * 0.5f;
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::MiddleRight:
                        pos.x -= textSize.x;
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::BottomLeft:
                        pos.y -= textSize.y;
                        break;

                    case Types::PIVOT::BottomMiddle:
                        pos.x -= textSize.x * 0.5f;
                        pos.y -= textSize.y;
                        break;

                    case Types::PIVOT::BottomRight:
                        pos.x -= textSize.x;
                        pos.y -= textSize.y;
                        break;
                    }

                    rl::DrawTextPro(lbl.font, lbl.text.c_str(), pos, { 0,0 }, 0, lbl.fontsize, 0.2f, lbl.Def);
                }
                else if (_Object.type == Types::_Toggle)
                {
                    Types::Toggle& tog = _Object.tog;

                    if (tog.toggled)
                    {
                        rl::DrawTexturePro(tog.toggletexture, { 0,0,(float)tog.toggletexture.width,(float)tog.toggletexture.height }, tog.rect, { 0,0 }, 0, { 255,255,255,255 });
                    }
                    else
                    {
                        rl::DrawTexturePro(tog.toggletexture, { 0,0,(float)tog.toggletexture.width,(float)tog.toggletexture.height }, tog.rect, { 0,0 }, 0, { 64,64,64,255 });
                    }

                    Types::Label& lbl = tog.text;

                    rl::Vector2 textSize = MeasureTextEx(lbl.font, lbl.text.c_str(), lbl.fontsize, 0.2f);
                    rl::Vector2 pos = { lbl.position.x + tog.rect.x,lbl.position.y + tog.rect.y };

                    switch (lbl.pivot)
                    {
                    case Types::PIVOT::TopLeft:
                        // pos stays as-is
                        break;

                    case Types::PIVOT::TopMiddle:
                        pos.x -= textSize.x * 0.5f;
                        break;

                    case Types::PIVOT::TopRight:
                        pos.x -= textSize.x;
                        break;

                    case Types::PIVOT::MiddleLeft:
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::Middle:
                        pos.x -= textSize.x * 0.5f;
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::MiddleRight:
                        pos.x -= textSize.x;
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::BottomLeft:
                        pos.y -= textSize.y;
                        break;

                    case Types::PIVOT::BottomMiddle:
                        pos.x -= textSize.x * 0.5f;
                        pos.y -= textSize.y;
                        break;

                    case Types::PIVOT::BottomRight:
                        pos.x -= textSize.x;
                        pos.y -= textSize.y;
                        break;
                    }

                    rl::DrawTextPro(lbl.font, lbl.text.c_str(), pos, { 0,0 }, 0, lbl.fontsize, 0.2f, lbl.Def);
                }
                else if (_Object.type == Types::_InputLabel)
                {
                    auto& ilb = _Object.ilb;

                    rl::DrawRectangleRec(ilb.rect, ilb.bgcolor);

                    Types::Label& lbl = ilb.Label;

                    const char* drawText = nullptr;

                    if (ilb.value.empty())
                    {
                        drawText = "Input a value.";
                        ilb.scrolloffset = 0;
                    }
                    else
                    {
                        if (ilb.scrolloffset > (int)ilb.value.size())
                            ilb.scrolloffset = 0;

                        drawText = ilb.value.c_str() + ilb.scrolloffset;
                    }

                    rl::Vector2 textSize = MeasureTextEx(lbl.font, drawText, lbl.fontsize, 0.2f);
                    rl::Vector2 pos = {
                        ilb.rect.x + lbl.position.x,
                        ilb.rect.y + lbl.position.y
                    };

                    switch (lbl.pivot)
                    {
                    case Types::PIVOT::TopLeft:
                        break;

                    case Types::PIVOT::TopMiddle:
                        pos.x -= textSize.x * 0.5f;
                        break;

                    case Types::PIVOT::TopRight:
                        pos.x -= textSize.x;
                        break;

                    case Types::PIVOT::MiddleLeft:
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::Middle:
                        pos.x -= textSize.x * 0.5f;
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::MiddleRight:
                        pos.x -= textSize.x;
                        pos.y -= textSize.y * 0.5f;
                        break;

                    case Types::PIVOT::BottomLeft:
                        pos.y -= textSize.y;
                        break;

                    case Types::PIVOT::BottomMiddle:
                        pos.x -= textSize.x * 0.5f;
                        pos.y -= textSize.y;
                        break;

                    case Types::PIVOT::BottomRight:
                        pos.x -= textSize.x;
                        pos.y -= textSize.y;
                        break;
                    }

                    rl::DrawTextPro(lbl.font, drawText, pos, { 0,0 }, 0, lbl.fontsize, 0.2f, lbl.Def);
                }
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
