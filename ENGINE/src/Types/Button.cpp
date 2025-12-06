#include "Button.hpp"

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
    Types::PIVOT pivot = Types::PIVOT::Middle;
    rl::Color Def = rl::WHITE;
    rl::Color Onhover = rl::DARKGRAY;
    int uniqueid = -1;

    void Disable()
    {
        disabled = true;
        return;
    }

    void Enable()
    {
        disabled = false;
        return;
    }

    void Exec()
    {
        exec();
        return;
    }
};
