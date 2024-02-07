#pragma once

#include "includes.h"

class Gradient
{
public:
	void set_color(Vector4 color)
	{
		driver.Write<Vector4>(reinterpret_cast<uintptr_t>(this),color);
	}

	Vector4 get_color()
	{
		return driver.Read<Vector4>(reinterpret_cast<uintptr_t>(this));
	}
};