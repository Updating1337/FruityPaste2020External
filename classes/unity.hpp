#pragma once

#include "includes.h"

uintptr_t get_component(uintptr_t game_object, std::string component_name, bool debug)
{
	if (game_object == 0)
		return 0;

	uintptr_t componentList = driver.Read<uintptr_t>(game_object + 0x30);

	for (int h = 0; h < 255; h++)
	{
		uintptr_t component = driver.Read<uintptr_t>(componentList + (0x10 * h + 0x8));

		if (component == NULL)
			continue;

		uintptr_t object_class = driver.Read<uintptr_t>(component + 0x28);

		uintptr_t name_obj = driver.Read<uintptr_t>(object_class);

		const char* comp_name = driver.read_str(driver.Read<uintptr_t>(name_obj + 0x10), 18);

		if (debug) std::cout << "component name : " << comp_name << std::endl;

		if (comp_name == component_name)
			return object_class;
	}

	return 0;
}