#pragma once

#include "includes.h"

class RecoilProperties
{
public:
	void set(Vector4 recoil)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<Vector4>(reinterpret_cast<uintptr_t>(this) + 0x18, recoil);
	}

	Vector4 get()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return Vector4();

		return driver.Read<Vector4>(reinterpret_cast<uintptr_t>(this) + 0x18);
	}
};