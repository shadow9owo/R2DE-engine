#pragma once

#include "types.hpp"

class Window
{
public:
    bool disabled = false;
    std::string title = "undefined";
    rl::Rectangle rect = {};
    std::vector<Types::UIObject> elements;
    Types::UniqueIds uniqueid = Types::UniqueIds::NONE;
    rl::Color bgcolor = { 255,255,255,255 };
    void (*callback)(Types::Layer*) = nullptr;
    Types::LayerInts currentlayer;

    void Disable();

    void Enable();

    void WipeAwait();

    void RenderSubUIElementHelper(Types::UIObject _Object);
};

