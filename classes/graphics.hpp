#pragma once

#include "includes.h"

class Graphics
{
public:
	static Graphics* get_instance()
	{
		return driver.ReadChain<Graphics*>(storage.game_assembly, { off::graphics_c,0xB8 });
	}

	void set_fov(float fov)
	{
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x18, fov);
	}
};