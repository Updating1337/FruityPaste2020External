#pragma once

#include "includes.h"

class PlayerWalkMovement
{
private:
	void set_capsule_center(float center)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_capsule_center, center);
	}

	void set_ground_angle(float angle)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_ground_angle, angle);
	}

	void set_ground_angle_new(float angle)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_ground_angle_new, angle);
	}

	void set_jump_time(float jump_time)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_jump_time, jump_time);
	}

	void set_ground_time(float ground_time)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_ground_time, ground_time);
	}

	void set_gravity_multiplier(float multiplier)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_gravitymultiplier, multiplier);
	}

	void set_land_time(float land_time)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_land_time , land_time);
	}
public:
	Vector3 get_target_movement()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return Vector3();

		return driver.Read<Vector3>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_target_movement);
	}

	void set_target_movement(Vector3 target)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<Vector3>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_target_movement, target);
	}

	auto omnisprint() -> void
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x40, 1.f);
	}

	void set_grounded(float grounded)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_grounded, grounded);
	}

	void set_sprinting(float sprinting)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_sprinting, sprinting);
	}

	void set_forcesprint(float sprinting)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::player_walk_movement_sprintforced, sprinting);
	}

	void infinite_jump()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		set_ground_time(99999.f);
		set_jump_time(0.51f);
		set_land_time(0.3f);
	}

	void spiderman()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		set_ground_angle(0.f);
		set_ground_angle_new(0.f);
	}

	void flyhack()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;
		
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0xC4, 0.f);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0xC8, 0.f);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x84, 0.f);
		//driver.Write<float>(reinterpret_cast<uintptr_t>(modelstate) + 0x14, 1.f);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x68, -999.f);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x6C, -999.f);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x88, 0.f);

		if (GetAsyncKeyState(VK_SPACE))
		{
			driver.Write<Vector3>(reinterpret_cast<uintptr_t>(this) + 0x34, Vector3(0, 3.5f, 0));
		}

	}

	auto undoflyhack() -> void
	{
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x84, 2.5f);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x68, 1.79f);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x6C, 0.899f);
	}

	void gravity(float amount)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		set_gravity_multiplier(amount);
	}
};