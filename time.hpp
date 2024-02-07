#pragma once

#include "includes.h"

class Time
{
public:
	static Time* get_instance()
	{
		return driver.Read<Time*>(storage.unity_player + 0x17C1CD0 + 7 * 8);
	}

	float get_time()
	{
		return driver.Read<float>(storage.game_assembly + 0x208D840);
	}

	void set_timescale(float scale)
	{
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0xFC, scale);
	}
};