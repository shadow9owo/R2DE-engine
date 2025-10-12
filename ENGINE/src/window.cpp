#ifdef _WIN32
#include <Windows.h>
#endif

namespace rl
{
	#include <raylib.h>
}

#include "Utils/wrapper/pfdwrapper.hpp"

#include "types.hpp"
#include "data.hpp"
#include "utils.hpp"

#include "Utils/Log.hpp"
#include "Utils/export/exportUtils.hpp"
#include "window.hpp"

#include <iostream>

namespace Window
{
	rl::Vector2 mouse = { 0,0 };

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
				projecthandling::f_export::f_export();
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
				projecthandling::f_import::f_import();
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

	void DoInit()
	{
		mouse = GetMousePosPro();
		data::activebuttons = {};

		Button Quit = { false, &Utils::Quit,"Quit",false,{0,670},24,rl::GetFontDefault(),{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Button Save = { false, &Utils::Save,"Save",false,{0,670},24,rl::GetFontDefault(),{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Button Load = { false, &Utils::Load,"Load",false,{0,670},24,rl::GetFontDefault(),{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Button Build = { false, &Utils::Build,"Build",false,{0,670},24,rl::GetFontDefault(),{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},PIVOT::Middle, rl::DARKGRAY , rl::BLACK };
		
		Quit.position.x = offset;
		Save.position.x = Quit.position.x + Qmessure(Quit).x + offset;
		Load.position.x = Save.position.x + Qmessure(Save).x + offset;
		Build.position.x = Load.position.x + Qmessure(Load).x + offset;

		data::activebuttons.push_back(Load);
		data::activebuttons.push_back(Save);
		data::activebuttons.push_back(Quit);
		data::activebuttons.push_back(Build);

		//active ui

		return;
	}

	namespace UI
	{
		namespace SpawnerDrop
		{
			void SpawnFunction()
			{
				::Utils::Log("SpawnFunction()");
				WipeDrop();
				return;
			}

			void MakeModule()
			{
				::Utils::Log("MakeModule()");
				WipeDrop();
				return;
			}

			void List()
			{
				::Utils::Log("List()");
				WipeDrop();
				return;
			}

			void Delete()
			{
				::Utils::Log("Delete()");
				WipeDrop();
				return;
			}

			//utility
			void WipeDrop()
			{
				void* SpawnFunction = (*UI::SpawnerDrop::SpawnFunction);
				void* MakeModule = (*UI::SpawnerDrop::MakeModule);
				void* List = (*UI::SpawnerDrop::List);
				void* Delete = (*UI::SpawnerDrop::Delete);

				for (int i = (int)data::activebuttons.size() - 1; i >= 0; --i)
				{
					if (data::activebuttons[i].exec == SpawnFunction || data::activebuttons[i].exec == MakeModule || data::activebuttons[i].exec == List || data::activebuttons[i].exec == Delete)
					{
						data::activebuttons.erase(data::activebuttons.begin() + i);
					}
				}

				return;
			}
		}
	}

	namespace callbacks
	{
		void DoInput()
		{
			if (rl::IsKeyPressed(rl::KEY_F11))
			{
				rl::ToggleFullscreen();
			}
			return;
		}

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
				if (CheckCollisionRecs(GetButtonSize(data::activebuttons[i]),{mouse.x,mouse.y,1,1}))
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
					if (rl::IsMouseButtonPressed(0))
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
				Button& btn = data::activebuttons[i];

				rl::Rectangle getsize = GetButtonSize(btn);

				getsize.width = clamp(getsize.width, (int)btn.MinMax.x, (int)btn.MinMax.width);
				getsize.height = clamp(getsize.height, (int)btn.MinMax.y, (int)btn.MinMax.height);

				rl::Vector2 text = MeasureTextEx(btn.font, btn.text.c_str(), btn.fontsize, 0.2f);

				rl::Color bgColor = btn.hovering ? btn.Onhover : btn.Def;
				rl::DrawRectanglePro({ btn.position.x, btn.position.y, getsize.width, getsize.height }, { 0,0 }, 0, bgColor);

				rl::Vector2 textPos = btn.position;

				switch (btn.pivot)
				{
					case PIVOT::TopLeft:        
						break;
					case PIVOT::TopMiddle:      
						textPos.x += (getsize.width - text.x) / 2; 
						break;
					case PIVOT::TopRight:       
						textPos.x += getsize.width - text.x; 
						break;
					case PIVOT::MiddleLeft:     
						textPos.y += (getsize.height - text.y) / 2; 
						break;
					case PIVOT::Middle:         
						textPos.x += (getsize.width - text.x) / 2; 
						textPos.y += (getsize.height - text.y) / 2; 
						break;
					case PIVOT::MiddleRight:    
						textPos.x += getsize.width - text.x; 
						textPos.y += (getsize.height - text.y) / 2; 
						break;
					case PIVOT::BottomLeft:     
						textPos.y += getsize.height - text.y;
						break;
					case PIVOT::BottomMiddle:   
						textPos.x += (getsize.width - text.x) / 2; 
						textPos.y += getsize.height - text.y; 
						break;
					case PIVOT::BottomRight:    
						textPos.x += getsize.width - text.x; 
						textPos.y += getsize.height - text.y; 
						break;
				}

				DrawTextPro(btn.font, btn.text.c_str(), textPos, { 0,0 }, 0, btn.fontsize, 0.2f, rl::WHITE);
			}
			return;
		}

		void DoInputCallbacksOnScreen()
		{
			if (rl::IsMouseButtonPressed(0))
			{
				//deactivate
				UI::SpawnerDrop::WipeDrop();
				::Utils::Log("left mouse button pressed");
			}
			else if (rl::IsMouseButtonPressed(1))
			{
				mouse = GetMousePosPro();

				UI::SpawnerDrop::WipeDrop();

				Button SpawnFunction = { false, &UI::SpawnerDrop::SpawnFunction,"SpawnFunction",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
				Button MakeModule = { false, &UI::SpawnerDrop::MakeModule,"MakeModule",false,{mouse.x,mouse.y},12, rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
				Button List = { false, &UI::SpawnerDrop::List,"List",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
				Button Delete = { false, &UI::SpawnerDrop::Delete,"Delete",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
				
				MakeModule.position.y = SpawnFunction.position.y + Qmessure(SpawnFunction).y;
				List.position.y = MakeModule.position.y + Qmessure(MakeModule).y;
				Delete.position.y = List.position.y + Qmessure(List).y;

				data::activebuttons.push_back(SpawnFunction);
				data::activebuttons.push_back(MakeModule);
				data::activebuttons.push_back(List);
				data::activebuttons.push_back(Delete);

				//activate
				::Utils::Log("right mouse button pressed");
			}
			return;
		}

		void DoInputCallbacksCamera()
		{
			return;
		}
	}

	void debug()
	{
		rl::DrawTextPro(rl::GetFontDefault(), std::to_string(mouse.x).c_str(), { 0, 0 },{ 0, 0 },0, 24, 0.2f, rl::BLACK);
		rl::DrawTextPro(rl::GetFontDefault(), std::to_string(mouse.y).c_str(), { 0, 24 },{0,0}, 0,24,0.2f, rl::BLACK);

		return;
	}

	void DoRender()
	{
		mouse = GetMousePosPro();

		callbacks::DoButtonCallBacks();
		callbacks::DoInputCallbacksOnScreen(); //local area
		callbacks::DoInput();

		if (::debug)
		{
			::Window::debug();
		}

		return;
	}

	void DoCameraRender()
	{
		callbacks::DoInputCallbacksCamera(); //global area aka 3d
		return;
	}
}