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

#include <vector>

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

		data::Layers.reserve(128);

		Types::Button Quit = { false, &Utils::Quit,"Quit",false,{0,670},24,rl::GetFontDefault(),{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Types::Button Save = { false, &Utils::Save,"Save",false,{0,670},24,rl::GetFontDefault(),{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Types::Button Load = { false, &Utils::Load,"Load",false,{0,670},24,rl::GetFontDefault(),{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Types::Button Build = { false, &Utils::Build,"Build",false,{0,670},24,rl::GetFontDefault(),{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK};
		
		Quit.position.x = offset;
		Save.position.x = Quit.position.x + Qmessure(Quit).x + offset;
		Load.position.x = Save.position.x + Qmessure(Save).x + offset;
		Build.position.x = Load.position.x + Qmessure(Load).x + offset;

		data::rootlayer.priority = -1;

		data::rootlayer.objects.push_back(Load);
		data::rootlayer.objects.push_back(Save);
		data::rootlayer.objects.push_back(Quit);
		data::rootlayer.objects.push_back(Build);

		data::Layers.push_back(data::rootlayer);

		Types::Layer debug = {};
		debug.priority = 9999;

		Types::Label PosInfo = { 24,std::to_string(mouse.x) + " || " + std::to_string(mouse.y),rl::GetFontDefault(),Types::PIVOT::TopLeft,{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX } ,{ 0,8 } ,callbacks::UpdateDebugValues,{ 0,0,0,255 } ,{ 0,0,0,255} ,1};
		Types::Label FrameRate = { 24,std::to_string(rl::GetFPS()) + " || " + std::to_string(rl::GetFrameTime()),rl::GetFontDefault(),Types::PIVOT::TopLeft,{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX} ,{0,PosInfo.position.y + 24} ,callbacks::UpdateDebugValues,{0,0,0,255} ,{0,0,0,255},2};

		debug.objects.push_back(PosInfo);
		debug.objects.push_back(FrameRate);

		data::Layers.push_back(debug);

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
				void (*SpawnFunction)() = (*UI::SpawnerDrop::SpawnFunction);
				void (*MakeModule)() = (*UI::SpawnerDrop::MakeModule);
				void (*List)() = (*UI::SpawnerDrop::List);
				void (*Delete)() = (*UI::SpawnerDrop::Delete);

				std::vector<Types::Layer> Windows;

				for (Types::Layer i : data::Layers)
				{
					Windows.push_back(i);
				}

				std::sort(Windows.begin(), Windows.end(),
					[](const Types::Layer& a, const Types::Layer& b)
					{
						return a.priority < b.priority;
					});

				for (Types::Layer& i : data::Layers)
				{
					auto& objs = i.objects;

					for (auto it = objs.begin(); it != objs.end(); )
					{
						auto& j = *it;

						if (j.type == Types::_Button)
						{
							if (j.btn.exec == SpawnFunction ||
								j.btn.exec == MakeModule ||
								j.btn.exec == List ||
								j.btn.exec == Delete)
							{
								it = objs.erase(it);
								continue;
							}
						}

						++it;
					}
				}

				return;
			}
		}
	}

		namespace callbacks
		{
			void UpdateDebugValues(int arg,void* ptr)
			{
				switch (arg)
				{
				case 1:
					static_cast<Types::Label*>(ptr)->text = std::to_string(mouse.x) + " || " + std::to_string(mouse.y);
					break;
				case 2:
					static_cast<Types::Label*>(ptr)->text = std::to_string(rl::GetFPS()) + " || " + std::to_string(rl::GetFrameTime());
					break;
				default:
					break;
				}
				return;
			}

			void RenderAllLayers()
			{
				std::vector<Types::Layer> Windows;

				for (auto& i : data::Layers)
				{
					Windows.push_back(i);
				}

				std::sort(Windows.begin(), Windows.end(),
					[](const Types::Layer& a, const Types::Layer& b)
					{
						return a.priority < b.priority;
					});

				for (auto& i : data::Layers) // reference, not copy
				{
					for (auto& j : i.objects) // reference, not copy
					{
						if (j.type == Types::_Button)
						{
							Types::Button& btn = j.btn;

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
								break;
							case Types::PIVOT::TopMiddle:
								textPos.x += (getsize.width - text.x) / 2;
								break;
							case Types::PIVOT::TopRight:
								textPos.x += getsize.width - text.x;
								break;
							case Types::PIVOT::MiddleLeft:
								textPos.y += (getsize.height - text.y) / 2;
								break;
							case Types::PIVOT::Middle:
								textPos.x += (getsize.width - text.x) / 2;
								textPos.y += (getsize.height - text.y) / 2;
								break;
							case Types::PIVOT::MiddleRight:
								textPos.x += getsize.width - text.x;
								textPos.y += (getsize.height - text.y) / 2;
								break;
							case Types::PIVOT::BottomLeft:
								textPos.y += getsize.height - text.y;
								break;
							case Types::PIVOT::BottomMiddle:
								textPos.x += (getsize.width - text.x) / 2;
								textPos.y += getsize.height - text.y;
								break;
							case Types::PIVOT::BottomRight:
								textPos.x += getsize.width - text.x;
								textPos.y += getsize.height - text.y;
								break;
							}

							rl::DrawTextPro(btn.font, btn.text.c_str(), textPos, { 0,0 }, 0, btn.fontsize, 0.2f, rl::WHITE);
						}
						else if (j.type == Types::_Label)
						{
							Types::Label& lbl = j.lbl;

							rl::Vector2 textSize = MeasureTextEx(lbl.font, lbl.text.c_str(), lbl.fontsize, 0.2f);
							rl::Vector2 pos = lbl.position;

							switch (lbl.pivot)
							{
							case Types::PIVOT::TopLeft:
								break;

							case Types::PIVOT::TopMiddle:
								pos.x -= textSize.x / 2;
								break;

							case Types::PIVOT::TopRight:
								pos.x -= textSize.x;
								break;

							case Types::PIVOT::MiddleLeft:
								pos.y -= textSize.y / 2;
								break;

							case Types::PIVOT::Middle:
								pos.x -= textSize.x / 2;
								pos.y -= textSize.y / 2;
								break;

							case Types::PIVOT::MiddleRight:
								pos.x -= textSize.x;
								pos.y -= textSize.y / 2;
								break;

							case Types::PIVOT::BottomLeft:
								pos.y -= textSize.y;
								break;

							case Types::PIVOT::BottomMiddle:
								pos.x -= textSize.x / 2;
								pos.y -= textSize.y;
								break;

							case Types::PIVOT::BottomRight:
								pos.x -= textSize.x;
								pos.y -= textSize.y;
								break;
							}

							rl::DrawTextPro(lbl.font, lbl.text.c_str(), pos, { 0,0 }, 0, lbl.fontsize, 0.2f, lbl.Def);
						}

					}
				}

				return;
			}

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
				std::vector<Types::Layer> Windows;

				for (Types::Layer i : data::Layers)
				{
					Windows.push_back(i);
				}

				std::sort(Windows.begin(), Windows.end(),
					[](const Types::Layer& a, const Types::Layer& b)
					{
						return a.priority < b.priority;
					});

				for (Types::Layer& i : data::Layers)
				{
					auto& objs = i.objects;

					for (auto it = objs.begin(); it != objs.end(); )
					{
						auto& j = *it;

						if (j.type == Types::_Button)
						{
							if (j.btn.disabled)
							{
								it = objs.erase(it);
								continue;
							}
						}

						if (CheckCollisionRecs(GetButtonSize(j.btn), { mouse.x, mouse.y, 1, 1 }))
						{
							j.btn.hovering = true;
						}
						else
						{
							j.btn.hovering = false;
						}

						if (j.btn.hovering)
						{
							if (rl::IsMouseButtonPressed(0))
							{
								if (j.btn.exec)
								{
									((void(*)())j.btn.exec)();
								}
								else
								{
									::Utils::LogFatal("Error", "uninitialized pointer or memory corruption occurred");
								}
							}
						}

						++it;
					}
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

					Types::Layer options = {};
					options.priority = 1;

					Types::Button SpawnFunction = { false, &UI::SpawnerDrop::SpawnFunction,"SpawnFunction",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, Types::PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
					Types::Button MakeModule = { false, &UI::SpawnerDrop::MakeModule,"MakeModule",false,{mouse.x,mouse.y},12, rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, Types::PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
					Types::Button List = { false, &UI::SpawnerDrop::List,"List",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, Types::PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
					Types::Button Delete = { false, &UI::SpawnerDrop::Delete,"Delete",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, Types::PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
					
					MakeModule.position.y = SpawnFunction.position.y + Qmessure(SpawnFunction).y;
					List.position.y = MakeModule.position.y + Qmessure(MakeModule).y;
					Delete.position.y = List.position.y + Qmessure(List).y;

					options.objects.push_back(SpawnFunction);
					options.objects.push_back(MakeModule);
					options.objects.push_back(List);
					options.objects.push_back(Delete);

					data::Layers.push_back(options);

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
		for (auto& layer : data::Layers)
		{
			if (layer.priority == 9999)
			{
				for (auto& obj : layer.objects)
				{
					if (obj.type == Types::_Label && obj.lbl.uniqueid == 1)
						obj.lbl.callback(1,&obj.lbl);
					else if (obj.type == Types::_Label && obj.lbl.uniqueid == 2)
						obj.lbl.callback(2,&obj.lbl);
				}
				break;
			}
		}
		return;
	}

	void DoRender()
	{
		mouse = GetMousePosPro();

		callbacks::DoButtonCallBacks();
		callbacks::DoInputCallbacksOnScreen(); //local area
		callbacks::DoInput();
		callbacks::RenderAllLayers();

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