#pragma once

#include "includes.h"

class UIInventory
{
public:
	static UIInventory* get_instance()
	{
		return driver.ReadChain<UIInventory*>(storage.game_assembly, { 0x3113DE8,0xB8 });
	}

	bool is_open()
	{
		return driver.Read<bool>(reinterpret_cast<uintptr_t>(this));
	}
};