#pragma once

#include "includes.h"

class Mounted
{
public:
	void shoot_in_mini(bool toggle)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<bool>(reinterpret_cast<uintptr_t>(this) + 0x2b0,toggle);
	}
};