#include "Window.hpp"
#include "utils.hpp"
#include <string>
#include "types.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "InputLabel.hpp"
#include "Toggle.hpp"

#include "UIObject.hpp"

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

    void WipeAwait()
    {
        currentlayer = Types::LayerInts::AWAITING_WIPE;
        return;
    }

    void RenderSubUIElementHelper(UIObject _Object)
    {
        if (_Object.type == UIObjectType::_Button)
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