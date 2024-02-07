#pragma once

#include "includes.h"

class ModelState
{
public:
	static enum Flag
	{
		Ducked = 1,
		Jumped = 2,
		OnGround = 4,
		Sleeping = 8,
		Sprinting = 16,
		OnLadder = 32,
		Flying = 64,
		Aiming = 128,
		Prone = 256,
		Mounted = 512,
		Relaxed = 1024,
		OnPhone = 2048,
		Crawling = 4096,
		HeadLook = 16384,
	};

	bool has_flag(int flag)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		return (driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::model_state_flags)) & flag;
	}

	auto set_waterlevel(float height) -> void
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x14, height);
	}

	void add_flag(int flag)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		int current_flags = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::model_state_flags);
		driver.Write<int>(reinterpret_cast<uintptr_t>(this) + off::model_state_flags, current_flags |= flag);
	}

	void remove_flag(int flag)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		int player_flags = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::model_state_flags);
		if (has_flag(flag)) player_flags -= flag;
		driver.Write<int>(reinterpret_cast<uintptr_t>(this) + off::model_state_flags, player_flags);
	}
};