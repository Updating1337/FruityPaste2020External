#pragma once

#include "includes.h"

class Eyes
{
public:
	void set_view_offset(Vector3 view_offset)
	{
		driver.Write<Vector3>(reinterpret_cast<uintptr_t>(this) + off::eyes_view_offest, view_offset);
	}

	Vector3 get_view_offset()
	{
		return driver.Read<Vector3>(reinterpret_cast<uintptr_t>(this) + off::eyes_view_offest);
	}

	void look_at_point(Vector2 angles)
	{
		angles.normalize();
		driver.Write<Vector4>(reinterpret_cast<uintptr_t>(this) + off::eyes_body_rotation, ToQuat({ angles.x,angles.y, 0 }));
	}
};