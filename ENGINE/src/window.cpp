#ifdef _WIN32
#include <Windows.h>
#endif

#define TITLEBARHEIGHT 21
#define CHECKMARKHEIGHT 30

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

#include "Utils/textures/Textures.hpp"
#include <regex>

namespace Window
{
	rl::Vector2 mouse = { 0,0 };

	namespace Utils
	{
		void RenderSubUIElement(Types::UIObject _Object)
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

		void ToggleClicked(Types::Toggle* toggle)
		{
			Types::Toggle* _toggle = static_cast<Types::Toggle*>(toggle);

			_toggle->toggled = !_toggle->toggled;

			if (_toggle->uniqueid != Types::UniqueIds::NONE)
			{
				if (_toggle->uniqueid == Types::UniqueIds::VSYNC_TOGGLE)
				{
					data::config::vsync = toggle->toggled;
					data::config::updateini();
				}
			}

			return;
		}

		void WipeAwait()
		{
			for (int i = 0; i < (int)data::Layers.size(); i++)
			{
				if (data::Layers[i].priority == Types::LayerInts::AWAITING_WIPE)
				{
					data::Layers.erase(data::Layers.begin() + i);
					break;
				}
			}
			return;
		}

		void WindowTick(Types::Layer* input)
		{
			if (rl::IsKeyPressed(rl::KEY_ESCAPE))
			{
				return callbacks::WipeLayer(*input);
			}
			else {
				for (Types::UIObject& a : input->objects)
				{
					if (a.type != Types::_Window || !a.win)
						continue;

					if (a.type == Types::_Window)
					{
						if (rl::IsMouseButtonDown(0))
						{
							if (rl::CheckCollisionRecs({ a.win->rect.x,a.win->rect.y,a.win->rect.width,TITLEBARHEIGHT }, { mouse.x,mouse.y,4,4 }))
							{
								a.win->rect.x = mouse.x - (a.win->rect.width / 2);
								a.win->rect.y = mouse.y - (TITLEBARHEIGHT / 2);
								data::dragging = true;
							}
							else if (data::dragging == true)
							{
								a.win->rect.x = mouse.x - (a.win->rect.width / 2);
								a.win->rect.y = mouse.y - (TITLEBARHEIGHT / 2);
							}
						}
						else {
							data::dragging = false;
							return;
						}
					}
				}

				return;
			}
		}

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

		void Settings()
		{
			Types::Layer* layertowipe = nullptr;

			for (auto& l : data::Layers)
			{
				if (l.priority == Types::LayerInts::LAYER_WINDOW_DEFAULT)
				{
					layertowipe = &l;
					break;
				}
			}

			if (layertowipe)
			{
				layertowipe->priority = ::Types::LayerInts::AWAITING_WIPE;
			}

			::Types::Layer WindowLayer;

			WindowLayer.priority = ::Types::LayerInts::LAYER_WINDOW_DEFAULT;
			WindowLayer.objects = {};

			Types::Window* win = new Types::Window{
				false,
				"Settings UI",
				{200, 200, 200, 200},
				{},
				Types::UniqueIds::SETTINGS_WINDOW_ID,
				rl::GRAY,
				&Utils::WindowTick
			};

			Types::Label text;
			text.text = "Vsync toggle";
			text.fontsize = 12;
			text.position = { CHECKMARKHEIGHT, CHECKMARKHEIGHT / 2 };
			text.pivot = Types::PIVOT::TopLeft;

			Types::Toggle Vsync;
			Vsync.uniqueid = Types::UniqueIds::VSYNC_TOGGLE;
			Vsync.callback = &ToggleClicked;
			Vsync.toggletexture = Textures::Checkmark();
			Vsync.rect = { TITLEBARHEIGHT + 2, TITLEBARHEIGHT + 2, CHECKMARKHEIGHT, CHECKMARKHEIGHT };
			Vsync.text = text;
			Vsync.toggled = data::config::vsync;

			Types::InputLabel FpsInput;

			FpsInput.rect = { TITLEBARHEIGHT + 2, 100, 150, 24 };
			FpsInput.regex = R"(^\d+$)";
			FpsInput.uniqueid = Types::UniqueIds::FRAMERATE_INPUT;
			FpsInput.callback = &callbacks::DoLabelFieldCallBacks;

			FpsInput.Label.fontsize = 12;
			FpsInput.Label.pivot = Types::PIVOT::Middle;
			FpsInput.Label.position = {
				FpsInput.rect.width * 0.5f,
				FpsInput.rect.height * 0.5f
			};

			Types::Label fps;
			fps.text = "Fps limiter";
			fps.fontsize = 12;
			fps.position = { TITLEBARHEIGHT + 2, 80 };
			fps.pivot = Types::PIVOT::TopLeft;

			FpsInput.value = std::to_string(::data::config::framerate);

			win->elements.push_back(Types::UIObject(Vsync));
			win->elements.push_back(Types::UIObject(fps));
			win->elements.push_back(Types::UIObject(FpsInput));

			WindowLayer.objects.emplace_back(Types::UIObject(win));

			::data::Layers.push_back(WindowLayer);

			::Utils::Log("Settings opened");
			return;
		}
	}

	void DoInit()
	{
		mouse = GetMousePosPro();

		data::Layers.reserve(128);

		Types::Button Quit = { false, Utils::Quit,"Quit",false,{0,670},24,rl::GetFontDefault(),{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Types::Button Save = { false, Utils::Save,"Save",false,{0,670},24,rl::GetFontDefault(),{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Types::Button Load = { false, Utils::Load,"Load",false,{0,670},24,rl::GetFontDefault(),{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Types::Button Build = { false, Utils::Build,"Build",false,{0,670},24,rl::GetFontDefault(),{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Types::Button Settings = { false, Utils::Settings,"Settings",false,{0,670},24,rl::GetFontDefault(),{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX},Types::PIVOT::Middle, rl::DARKGRAY , rl::BLACK };

		Quit.position.x = offset;
		Save.position.x = Quit.position.x + Qmessure(Quit).x + offset;
		Load.position.x = Save.position.x + Qmessure(Save).x + offset;
		Build.position.x = Load.position.x + Qmessure(Load).x + offset;
		Settings.position.x = Build.position.x + Qmessure(Build).x + offset;

		data::rootlayer.priority = Types::LayerInts::LAYER_APPLICATION_QUICK_ACTIONS;

		data::rootlayer.objects.push_back(Types::UIObject(Load));
		data::rootlayer.objects.push_back(Types::UIObject(Save));
		data::rootlayer.objects.push_back(Types::UIObject(Quit));
		data::rootlayer.objects.push_back(Types::UIObject(Build));
		data::rootlayer.objects.push_back(Types::UIObject(Settings));

		data::Layers.push_back(data::rootlayer);

		Types::Layer debug = {};
		debug.priority = Types::LayerInts::LAYER_DEBUG;

		Types::Label PosInfo = { 24,std::to_string(mouse.x) + " || " + std::to_string(mouse.y),rl::GetFontDefault(),Types::PIVOT::TopLeft,{ INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX } ,{ 0,8 } ,callbacks::UpdateDebugValues,{ 0,0,0,255 } ,{ 0,0,0,255} ,1 };
		Types::Label FrameRate = { 24,std::to_string(rl::GetFPS()) + " || " + std::to_string(rl::GetFrameTime()),rl::GetFontDefault(),Types::PIVOT::TopLeft,{INT16_MIN,INT16_MIN,INT16_MAX,INT16_MAX} ,{0,PosInfo.position.y + 24} ,callbacks::UpdateDebugValues,{0,0,0,255} ,{0,0,0,255},2 };

		debug.objects.push_back(Types::UIObject(PosInfo));
		debug.objects.push_back(Types::UIObject(FrameRate));

		data::Layers.push_back(debug);

		return;
	}

	namespace UI
	{
		namespace SpawnerDrop
		{
			void SpawnFunction()
			{
				Types::Layer* layertowipe = nullptr;

				for (auto& l : data::Layers)
				{
					if (l.priority == Types::LayerInts::LAYER_WINDOW_DEFAULT)
					{
						layertowipe = &l;
						break;
					}
				}

				if (layertowipe)
				{
					layertowipe->priority = ::Types::LayerInts::AWAITING_WIPE;
				}

				::Types::Layer WindowLayer;

				WindowLayer.priority = ::Types::LayerInts::LAYER_WINDOW_DEFAULT;
				WindowLayer.objects = {};

				Types::Window* win = new Types::Window{
					false,
					"Spawn UI",
					{200, 200, 200, 200},
					{},
					Types::UniqueIds::SPAWN_WINDOW_ID,
					rl::GRAY,
					&Utils::WindowTick
				};

				WindowLayer.objects.emplace_back(Types::UIObject(win));

				::data::Layers.push_back(WindowLayer);

				::Utils::Log("SpawnFunction()");
				WipePreDrop();
				return;
			}

			void List()
			{
				Types::Layer* layertowipe = nullptr;

				for (auto& l : data::Layers)
				{
					if (l.priority == Types::LayerInts::LAYER_WINDOW_DEFAULT)
					{
						layertowipe = &l;
						break;
					}
				}

				if (layertowipe)
				{
					layertowipe->priority = ::Types::LayerInts::AWAITING_WIPE;
				}

				::Types::Layer WindowLayer;

				WindowLayer.priority = ::Types::LayerInts::LAYER_WINDOW_DEFAULT;
				WindowLayer.objects = {};

				Types::Window* win = new Types::Window{
					false,
					"List UI",
					{200, 200, 200, 200},
					{},
					Types::UniqueIds::LIST_WINDOW_ID,
					rl::GRAY,
					&Utils::WindowTick
				};

				WindowLayer.objects.emplace_back(Types::UIObject(win));

				::data::Layers.push_back(WindowLayer);

				::Utils::Log("List()");
				WipePreDrop();
				return;
			}

			void Delete()
			{
				::Utils::Log("Delete()");
				WipePreDrop();
				return;
			}

			//utility

			void WipePreDrop()
			{
				data::wipedrop = true;
			}

			void WipeDrop()
			{
				::Types::Layer a;
				a.priority = ::Types::LayerInts::LAYER_POPUP_MENU;
				callbacks::WipeLayer(a);
			}
		}
	}

	namespace callbacks
	{
		void WipeLayer(Types::Layer input)
		{
			for (auto it = data::Layers.begin(); it != data::Layers.end(); )
			{
				if (it->priority == input.priority)
				{
					it = data::Layers.erase(it);
				}
				else
				{
					++it;
				}
			}
			return;
		}

		void UpdateDebugValues(int arg, void* ptr)
		{
			switch (arg)
			{
			case Types::UniqueIds::MOUSE_POS_ID:
				static_cast<Types::Label*>(ptr)->text = std::to_string(mouse.x) + " || " + std::to_string(mouse.y);
				break;
			case Types::UniqueIds::FPS_ID:
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

			for (auto& i : data::Layers)
			{
				if (i.priority == ::Types::LayerInts::AWAITING_WIPE)
				{
					continue;
				}

				for (auto& j : i.objects)
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
					else if (j.type == Types::_Window)
					{
						if (!j.win) continue;

						Types::Window& win = *j.win;
						rl::Rectangle rect = win.rect;

						rl::DrawRectangleRec(rect, win.bgcolor);

						rl::DrawRectangleRec({ rect.x,rect.y,rect.width,17 + 4 }, { win.bgcolor.r,win.bgcolor.g,win.bgcolor.b,128 });

						rl::DrawTextPro(
							rl::GetFontDefault(),
							win.title.c_str(),
							{ rect.x + 4, rect.y + 4 },
							{ 0,0 },
							0,
							16,
							0,
							rl::BLACK
						);

						for (size_t i = 0; i != win.elements.size(); i++)
						{
							auto a = win.elements[i];
							switch (win.elements[i].type)
							{
							case Types::_Button:
								a.btn.position.x = a.btn.position.x + rect.x;
								a.btn.position.y = a.btn.position.y + rect.y;
								Utils::RenderSubUIElement(a);
								break;
							case Types::_Window:
								assert("not implemented");
								break;
							case Types::_Label:
								a.lbl.position.x = a.lbl.position.x + rect.x;
								a.lbl.position.y = a.lbl.position.y + rect.y;
								Utils::RenderSubUIElement(a);
								break;
							case Types::_InputLabel:
								a.ilb.rect.x = a.ilb.rect.x + rect.x;
								a.ilb.rect.y = a.ilb.rect.y + rect.y;
								Utils::RenderSubUIElement(a);
								break;
							case Types::_Toggle:
								a.tog.rect.x = a.tog.rect.x + rect.x;
								a.tog.rect.y = a.tog.rect.y + rect.y;
								Utils::RenderSubUIElement(a);
								break;
							default:
								break;
							}
						}
						if (j.win->callback) //drag
						{
							j.win->callback(&i);
						}
					}
					else if (j.type == Types::_Toggle)
					{
						Types::Toggle& tog = j.tog;

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
					else if (j.type == Types::_InputLabel)
					{
						auto& ilb = j.ilb;

						rl::DrawRectangleRec(ilb.rect, ilb.bgcolor);

						Types::Label& lbl = j.ilb.Label;

						const char* drawText = nullptr;

						if (ilb.value.empty())
						{
							drawText = "Input a value.";
						}
						else
						{
							drawText = ilb.value.c_str();
						}

						rl::Vector2 textSize = MeasureTextEx(lbl.font, drawText, lbl.fontsize, 0.2f);
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

						rl::DrawTextPro(ilb.Label.font, drawText, pos, { 0,0 }, 0, ilb.Label.fontsize, 0.2f, ilb.Label.Def);
					}
				}
			}

			Utils::WipeAwait();

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

		void DoToggleCallBacks()
		{
			std::vector<Types::Layer> Windows;

			for (Types::Layer& i : data::Layers)
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

				for (auto it = objs.begin(); it != objs.end();)
				{
					auto& j = *it;

					if (j.type == Types::_Toggle)
					{
						rl::DrawRectangleRec(j.tog.rect, rl::RED);
						if (rl::CheckCollisionRecs(j.tog.rect, { mouse.x, mouse.y, 1, 1 }))
						{
							if (rl::IsMouseButtonPressed(0))
							{
								if (j.tog.callback)
								{
									::Utils::Log("Toggled");
									j.tog.callback(&j.tog);
								}
							}
						}
					}
					else if (j.type == Types::_Window)
					{
						for (Types::UIObject& a : j.win->elements)
						{
							if (a.type == Types::_Toggle)
							{
								rl::DrawRectangleRec({ a.tog.rect.x + j.win->rect.x,a.tog.rect.y + j.win->rect.y,a.tog.rect.width,a.tog.rect.height }, rl::RED);
								if (rl::CheckCollisionRecs({ a.tog.rect.x + j.win->rect.x,a.tog.rect.y + j.win->rect.y,a.tog.rect.width,a.tog.rect.height }, {mouse.x, mouse.y, 1, 1}))
								{
									if (rl::IsMouseButtonPressed(0))
									{
										if (a.tog.callback)
										{
											::Utils::Log("Toggled");
											a.tog.callback(&a.tog);
										}
									}
								}
							}
						}
					}

					++it; // only increment when not erased
				}
			}

			return;
		}

		void DoLabelFieldCallBacks()
		{
			std::vector<Types::Layer> Windows;

			for (Types::Layer& i : data::Layers)
			{
				Windows.push_back(i);
			}

			std::sort(Windows.begin(), Windows.end(),
				[](const Types::Layer& a, const Types::Layer& b)
				{
					return a.priority < b.priority;
				});

			bool cfocused = false;

			for (Types::Layer& i : data::Layers)
			{
				auto& objs = i.objects;

				for (auto it = objs.begin(); it != objs.end();)
				{
					auto& j = *it;

					if (j.type == Types::_InputLabel)
					{
						rl::Rectangle fieldRect = j.ilb.rect;

						if (rl::CheckCollisionRecs(fieldRect, { mouse.x, mouse.y, 1, 1 }))
						{
							j.ilb.focused = true;
						}
						else
						{
							j.ilb.focused = false;
						}

						if (j.ilb.focused)
						{
							cfocused = true;
							int key = 0;
							while ((key = rl::GetCharPressed()) != 0)
							{
								if (key >= 32 && key <= 126)
								{
									std::string next = j.ilb.value + (char)key;

									if (std::regex_match(next, std::regex(j.ilb.regex)))
									{
										j.ilb.value.push_back((char)key);
									}
								}
							}

							if (rl::IsKeyPressed(rl::KEY_BACKSPACE) && !j.ilb.value.empty())
							{
								j.ilb.value.pop_back();
							}
						}

					}
					else if (j.type == Types::_Window && j.win)
					{
						for (Types::UIObject& a : j.win->elements)
						{
							if (a.type != Types::_InputLabel)
							{
								continue;
							}

							rl::Rectangle fieldRect =
							{
								a.ilb.rect.x + j.win->rect.x,
								a.ilb.rect.y + j.win->rect.y,
								a.ilb.rect.width,
								a.ilb.rect.height
							};

							if (rl::CheckCollisionRecs(fieldRect, { mouse.x, mouse.y, 1, 1 }))
							{
								a.ilb.focused = true;
							}
							else
							{
								a.ilb.focused = false;
							}

							if (a.ilb.focused)
							{
								cfocused = true;
								int key = 0;
								while ((key = rl::GetCharPressed()) != 0)
								{
									if (key >= 32 && key <= 126)
									{
										std::string next = a.ilb.value + (char)key;

										try
										{
											if (std::regex_match(next, std::regex(a.ilb.regex)))
											{
												a.ilb.value.push_back((char)key);

												rl::Vector2 fullSize = MeasureTextEx(
													a.ilb.Label.font,
													a.ilb.value.c_str(),
													a.ilb.Label.fontsize,
													0.2f
												);

												while (fullSize.x > (a.ilb.rect.width - 4))
												{
													a.ilb.scrolloffset++;
													fullSize = MeasureTextEx(
														a.ilb.Label.font,
														a.ilb.value.c_str() + a.ilb.scrolloffset,
														a.ilb.Label.fontsize,
														0.2f
													);
												}
											}

										}
										catch (...)
										{
											a.ilb.value.push_back((char)key);
										}
									}
								}

								if (rl::IsKeyPressed(rl::KEY_BACKSPACE) && !a.ilb.value.empty())
								{
									a.ilb.value.pop_back();

									if (a.ilb.scrolloffset > 0)
										a.ilb.scrolloffset--;
								}
							}

							if (a.ilb.uniqueid == Types::UniqueIds::FRAMERATE_INPUT)
							{
								if (!a.ilb.value.empty())
								{
									int val = std::stoi(a.ilb.value);
									if (val != data::config::framerate)
									{
										data::config::framerate = clamp(val,12,9999);
										data::config::updateini();
									}
								}
							}
						}
					}

					++it;
				}
			}

			if (cfocused)
			{
				rl::SetMouseCursor(rl::MOUSE_CURSOR_IBEAM);
			}
			else 
			{
				rl::SetMouseCursor(rl::MOUSE_CURSOR_DEFAULT);
			}

			return;
		}

		void DoButtonCallBacks()
		{
			std::vector<Types::Layer> Windows;

			for (Types::Layer& i : data::Layers)
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

				for (auto it = objs.begin(); it != objs.end();)
				{
					auto& j = *it;

					if (j.type == Types::_Button)
					{
						if (j.btn.disabled)
						{
							it = objs.erase(it);
							continue;
						}
						if (rl::CheckCollisionRecs(GetButtonSize(j.btn), {mouse.x, mouse.y, 1, 1}))
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
									j.btn.exec();
								}
								else
								{
									::Utils::LogFatal("Error", "uninitialized pointer or memory corruption occurred");
								}
							}
						}
					}
					else if (j.type == Types::_Window)
					{
						for (Types::UIObject& a : j.win->elements)
						{
							if (a.type != Types::_Button)
							{
								continue;
							}
							if (a.btn.disabled)
							{
								it = objs.erase(it);
								continue;
							}
							if (rl::CheckCollisionRecs({ GetButtonSize(j.btn).x + j.win->rect.x,GetButtonSize(j.btn).y + j.win->rect.y,GetButtonSize(j.btn).width,GetButtonSize(j.btn).height }, { mouse.x, mouse.y, 1, 1 }))
							{
								a.btn.hovering = true;
							}
							else
							{
								a.btn.hovering = false;
							}

							if (a.btn.hovering)
							{
								if (rl::IsMouseButtonPressed(0))
								{
									if (a.btn.exec)
									{
										a.btn.exec();
									}
									else
									{
										::Utils::LogFatal("Error", "uninitialized pointer or memory corruption occurred");
									}
								}
							}
						}
					}

					++it; // only increment when not erased
				}
			}

			return;
		}

		bool i = false;

		void DoInputCallbacksOnScreen()
		{
			if (rl::IsMouseButtonPressed(0))
			{
				UI::SpawnerDrop::WipePreDrop();
				::Utils::Log("left mouse button pressed");
			}

			if (rl::IsMouseButtonPressed(1))
			{
				mouse = GetMousePosPro();

				UI::SpawnerDrop::WipeDrop();

				Types::Layer options = {};
				options.priority = Types::LayerInts::LAYER_POPUP_MENU;

				Types::Button SpawnFunction = { false, UI::SpawnerDrop::SpawnFunction,"SpawnFunction",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, Types::PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
				Types::Button List = { false, UI::SpawnerDrop::List,"List",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, Types::PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };
				Types::Button Delete = { false, UI::SpawnerDrop::Delete,"Delete",false,{mouse.x,mouse.y},12 ,rl::GetFontDefault(), { 200,INT16_MIN,INT16_MAX,INT16_MAX }, Types::PIVOT::MiddleLeft, rl::DARKGRAY, rl::BLACK };

				List.position.y = SpawnFunction.position.y + Qmessure(SpawnFunction).y;
				Delete.position.y = List.position.y + Qmessure(List).y;

				options.objects.push_back(Types::UIObject(SpawnFunction));
				options.objects.push_back(Types::UIObject(List));
				options.objects.push_back(Types::UIObject(Delete));

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
			if (layer.priority == Types::LayerInts::LAYER_DEBUG)
			{
				for (auto& obj : layer.objects)
				{
					if (obj.type == Types::_Label && obj.lbl.uniqueid == Types::UniqueIds::MOUSE_POS_ID)
					{
						obj.lbl.callback(Types::UniqueIds::MOUSE_POS_ID, &obj.lbl);
					}
					else if (obj.type == Types::_Label && obj.lbl.uniqueid == Types::UniqueIds::FPS_ID)
					{
						obj.lbl.callback(Types::UniqueIds::FPS_ID, &obj.lbl);
					}
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
		callbacks::DoToggleCallBacks();
		callbacks::DoLabelFieldCallBacks();

		callbacks::DoInputCallbacksOnScreen(); //local area
		callbacks::DoInput();
		callbacks::RenderAllLayers();

		if (data::wipedrop)
		{
			UI::SpawnerDrop::WipeDrop();
			data::wipedrop = false;
		}
		
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