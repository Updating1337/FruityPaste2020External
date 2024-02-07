#pragma once

#include "includes.h"

class Input
{
public:
	Vector2 get_view_angles()
	{
		return driver.Read<Vector2>(reinterpret_cast<uintptr_t>(this) + off::player_input_body_angles);
	}

	Vector3 RadarGetViewAngles()
	{
		return driver.Read<Vector3>(reinterpret_cast<uintptr_t>(this) + off::player_input_body_angles);
	}

	void set_view_angles(Vector2 angles)
	{
		driver.Write<Vector2>(reinterpret_cast<uintptr_t>(this) + off::player_input_body_angles, angles);
	}

	Vector4 get_rotation()
	{
		return driver.Read<Vector4>(reinterpret_cast<uintptr_t>(this) + off::player_input_rotation);
	}
};