#pragma once

#include <Windows.h>
#include <functional>
#include <thread>

#include <dwmapi.h> 
#include <dwrite.h>

#pragma comment(lib, "Dwmapi.lib") 
#pragma comment(lib, "Dwrite")

#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib") 

#include <d3d9.h>
#include <d3dx9.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include "fonts/verdana.hpp"
#include "fonts/ahroni.hpp"
#include "fonts/segoe.hpp"

#include "encryption.hpp"

#define function_callback std::function<void()>

static class style
{
public:
	const static ImU32 text = IM_COL32(255, 255, 255, 255);
	const static ImU32 text_inactive = IM_COL32(144, 144, 144, 255);
	const static ImU32 header_text = IM_COL32(200, 200, 200, 200);

	const static ImU32 accent = IM_COL32(207, 96, 230, 255);
	const static ImU32 outline = IM_COL32(21, 21, 21, 255);

	const static ImU32 window_bg = IM_COL32(36, 36, 36, 255);
	const static ImU32 nav_bg = IM_COL32(46, 46, 46, 255);

	const static ImU32 child_banner = IM_COL32(63, 191, 144, 210);
	const static ImU32 child_bg = IM_COL32(28, 28, 28, 255);


	const static ImU32 checkbox_bg = IM_COL32(30, 30, 30, 255);
	const static ImU32 checkbox_hovered = IM_COL32(45, 45, 45, 255);

	const static ImU32 tick = IM_COL32(255, 0, 255, 255);

};

class user_interface
{
private:

	void input_handling(bool* status);

	void set_window_active(HWND window);

	void safe_exit();
	void begin_scene();
	void end_scene();
public:
	bool status = false;

	ImFont* smallest;
	ImFont* slidersmall;

	bool has_opened = false;

	int selected_tab = 0;

	void window_check(HWND window);

	bool initialize(HWND window, std::vector<const char*> tabs, function_callback menu, function_callback draw);

};

