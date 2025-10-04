#include <raylib.h>

#include "types.hpp"
#include "data.hpp"
#include "utils.hpp"

#include "Utils/Log.hpp"

namespace Window
{
	namespace Utils
	{
		void Quit()
		{
			::Utils::Log("Quit triggered");
			return;
		}

		void Save()
		{
			::Utils::Log("Save triggered");
			return;
		}

		void Load()
		{
			::Utils::Log("Load triggered");
			return;
		}
	}

	Vector2 mouse = {0,0};

	void DoInit()
	{
		mouse = GetMousePosPro();
		data::activebuttons = {};

		Button Quit = { false, &Utils::Quit,"Quit",false,{120,120} };
		data::activebuttons.push_back(Quit);

		Button Save = { false, &Utils::Save,"Save",false,{120,240} };
		data::activebuttons.push_back(Save);

		Button Load = { false, &Utils::Load,"Load",false,{120,360} };
		data::activebuttons.push_back(Load);

		return;
	}

	namespace callbacks
	{
		void DoButtonCallBacks()
		{
			for (int i = (int)data::activebuttons.size() - 1; i >= 0; --i)
			{
				if (data::activebuttons[i].disabled)
				{
					data::activebuttons.erase(data::activebuttons.begin() + i);
				}
			}

			for (int i = (int)data::activebuttons.size() - 1; i >= 0; --i)
			{
				if (CheckCollisionRecs(GetButtonSize(data::activebuttons[i]),{mouse.x,mouse.y,4,4}))
				{
					data::activebuttons[i].hovering = true;
				}
				else
				{
					data::activebuttons[i].hovering = false;
				}
			}

			for (int i = (int)data::activebuttons.size() - 1; i >= 0; --i)
			{
				if (data::activebuttons[i].hovering)
				{
					if (IsMouseButtonPressed(0))
					{
						if (data::activebuttons[i].exec)
						{
							((void(*)())data::activebuttons[i].exec)(); //calls pointer
						}
						else
						{
							::Utils::Log("unitialized pointer or memory corruption accured");
						}
					}
				}
			}

			for (int i = (int)data::activebuttons.size() - 1; i >= 0; --i)
			{
				Vector2 text = MeasureTextEx(data::activebuttons[i].font, data::activebuttons[i].text.c_str(), data::activebuttons[i].fontsize, 0.2f);
				Rectangle getsize = GetButtonSize(data::activebuttons[i]);
				if (data::activebuttons[i].hovering)
				{
					DrawRectanglePro({ data::activebuttons[i].position.x,data::activebuttons[i].position.y,getsize.width,getsize.height}, { 0,0 }, 0, BLACK);
					DrawTextPro(data::activebuttons[i].font, data::activebuttons[i].text.c_str(), { (data::activebuttons[i].position.x + getsize.width / 2) - text.x / 2, (data::activebuttons[i].position.y + getsize.height / 2) - text.y / 2 }, {0,0}, 0, data::activebuttons[i].fontsize, 0.2f, WHITE);
				}
				else 
				{
					DrawRectanglePro({ data::activebuttons[i].position.x,data::activebuttons[i].position.y,getsize.width,getsize.height }, { 0,0 }, 0, DARKGRAY);
					DrawTextPro(data::activebuttons[i].font, data::activebuttons[i].text.c_str(), { (data::activebuttons[i].position.x + getsize.width / 2) - text.x /2, (data::activebuttons[i].position.y + getsize.height / 2) - text.y / 2 }, {0,0}, 0, data::activebuttons[i].fontsize, 0.2f, WHITE);
				}
			}
			return;
		}
	}

	void DoRender()
	{
		mouse = GetMousePosPro();

		callbacks::DoButtonCallBacks();

		DrawText(std::to_string(mouse.x).c_str(), 0, 0, 24, BLACK);
		DrawText(std::to_string(mouse.y).c_str(),0,24,24,BLACK);
		return;
	}

	void DoCameraRender()
	{
		return;
	}
}