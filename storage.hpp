#pragma once

#include "includes.h"

class storage_t
{
public:
	uintptr_t game_assembly;
	uintptr_t unity_player;

	const Vector2 screen = { (float)GetSystemMetrics(SM_CXSCREEN) ,(float)GetSystemMetrics(SM_CYSCREEN) };
	const Vector2 screen_center = { (float)GetSystemMetrics(SM_CXSCREEN) / 2 , (float)GetSystemMetrics(SM_CYSCREEN) / 2 };
}storage;