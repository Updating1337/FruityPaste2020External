#pragma once

#include "includes.h"

class keyhandling_t
{
public:
	void run()
	{
		while (true)
		{
			//if (keys.grab_key)
			//{
			//	int selected_index = 0;
			//	int itterations = 0;
			//
			//	while(itterations < 5000 || selected_index == 0)
			//	{
			//		for (int i = 0; i < 12; i++)
			//		{
			//			if (GetAsyncKeyState(0x70 + (i * 0x1))) selected_index = i;
			//		}
			//
			//		itterations++;
			//
			//		std::this_thread::sleep_for(std::chrono::milliseconds(1));
			//	}
			//
			//	keys.selected_index = selected_index;
			//	keys.grab_key = false;
			//}

			if (GetAsyncKeyState(keys.key_codes[keys.debug_camera_key]) & 0x1) cfg.interactive_debug_camera = !cfg.interactive_debug_camera;
			if (GetAsyncKeyState(keys.key_codes[keys.flyhack_key]) & 0x1) cfg.flyhack = !cfg.flyhack;

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
}keyhandler;