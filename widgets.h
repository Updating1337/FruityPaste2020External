#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <chrono>

#include "ui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

struct notifcation
{
	const char* title;
	long long max_time = 0;
};

class widgets
{
private:
	long long current_time = 0;
	int total_size = 0;
	ImVec2 start_point = { 0,0 };

	int enabled_index = 0;
	bool open = true;

	bool started = false;

	std::vector<notifcation> notifications = { {"empty",0} };
public:
	int item_count = 0;

	ImFont* font;
	ImFont* sliderfont;

	static void init();

	void draw_notifications();

	void child(const char* name, ImVec2 size, ImVec2 pos);

	void slider(const char* label, float* val, float min, float max);
	void checkbox(const char* label, bool* state);
	void color_selector(const char* label, float color[3]);
	void combo(std::vector<const char*> list, int* selected);
	void keybind(const char* key_name, int key);
	void spacing(float spacing);
	void add_notification(const char* title, int time);
};

