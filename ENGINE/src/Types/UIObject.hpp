#pragma once

#include "Window.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "InputLabel.hpp"
#include "Toggle.hpp"

enum UIObjectType
{
    None,
    _Button,
    _Window,
    _Label,
    _InputLabel,
    _Toggle
};

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

