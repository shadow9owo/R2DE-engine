#include <raylib.h>

#include "types.hpp"
#include "data.hpp"
#include "utils.hpp"

#include "Utils/Log.hpp"
#include "window.hpp"

#include "Utils/wrapper/pfdwrapper.hpp"

namespace Window
{
	namespace Utils
	{
		void Quit()
		{
			::Utils::Log("Quit triggered");
			::shouldclose = true;
			return;
		}

		void Save()
		{
			wrapper::SaveProjectFile();

			if (!data::filepath.empty())
			{

			}
			else 
			{
				return; // save cancelled
			}
			::Utils::Log("Save triggered");
			return;
		}

		void Load()
		{
			wrapper::OpenProjectFile();

			if (!data::contentsofproject.empty())
			{
				
			}
			else
			{
				return; // Load cancelled
			}

			::Utils::Log("Load triggered");
			return;
		}

		void Build()
		{
			::Utils::Log("Build triggered");
			return;
		}
	}

	Vector2 mouse = {0,0};

	void DoInit()
	{
		mouse = GetMousePosPro();
		data::activebuttons = {};

		Button Quit = { false, &Utils::Quit,"Quit",false,{0,670} };

		Button Save = { false, &Utils::Save,"Save",false,{0,670} };

		Button Load = { false, &Utils::Load,"Load",false,{0,670} };

		Button Build = { false, &Utils::Build,"Build",false,{0,670} };
		
		Quit.position.x = offset;
		Save.position.x = Quit.position.x + Qmessure(Quit).x + offset;
		Load.position.x = Save.position.x + Qmessure(Save).x + offset;
		Build.position.x = Load.position.x + Qmessure(Load).x + offset;
		
		data::activebuttons.push_back(Load);
		data::activebuttons.push_back(Save);
		data::activebuttons.push_back(Quit);
		data::activebuttons.push_back(Build);

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
							::Utils::LogFatal("Error", "unitialized pointer or memory corruption accured");
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

	void debug()
	{
		DrawText(std::to_string(mouse.x).c_str(), 0, 0, 24, BLACK);
		DrawText(std::to_string(mouse.y).c_str(), 0, 24, 24, BLACK);

		return;
	}

	void DoRender()
	{
		mouse = GetMousePosPro();

		callbacks::DoButtonCallBacks();

		if (::debug) {
			debug();
		}
		return;
	}

	void DoCameraRender()
	{
		return;
	}
}