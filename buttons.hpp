#pragma once

#include "includes.h"

class Button
{
public:
	bool is_pressed()
	{
		return driver.Read<bool>(reinterpret_cast<uintptr_t>(this) + 0x10);
	}
};

class Buttons
{
public:
	static Buttons* get_instance()
	{
		return driver.ReadChain<Buttons*>(storage.game_assembly, { 0x3113990,0xB8});
	}

	bool hover_loot()
	{
		return driver.Read<Button*>(reinterpret_cast<uintptr_t>(this) + 0x78)->is_pressed();
	}
};