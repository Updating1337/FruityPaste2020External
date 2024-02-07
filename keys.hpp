#pragma once

#include "includes.h"

class keys_t
{
public:
	std::vector<const char*> key_names = { "F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12" };
	std::vector<DWORD> key_codes = { VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8,VK_F9,VK_F10,VK_F11,VK_F12 };

	bool grab_key = false;
	int selected_index = 0;

	int debug_camera_key = 1;
	int flyhack_key = 2;
}keys;