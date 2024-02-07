#pragma once

#include "imgui/imgui.h"
#include "vector.hpp"

struct player_bones
{
	Vector2 upper_spine{};

	Vector2 left_shoulder{};
	Vector2 left_elbow{};
	Vector2 left_wrist{};

	Vector2 right_shoulder{};
	Vector2 right_elbow{};
	Vector2 right_wrist{};

	Vector2 lower_spine{};

	Vector2 left_hip{};
	Vector2 left_knee{};
	Vector2 left_ankle{};

	Vector2 right_hip{};
	Vector2 right_knee{};
	Vector2 right_ankle{};
};


struct initial_bones
{
public:
	Vector3 upper_spine{};

	Vector3 left_shoulder{};
	Vector3 left_elbow{};
	Vector3 left_wrist{};

	Vector3 right_shoulder{};
	Vector3 right_elbow{};
	Vector3 right_wrist{};

	Vector3 lower_spine{};

	Vector3 left_hip{};
	Vector3 left_knee{};
	Vector3 left_ankle{};

	Vector3 right_hip{};
	Vector3 right_knee{};
	Vector3 right_ankle{};
};


struct weapon_info
{
public:
	float repeat_delay;
	bool automatic = false;
	Vector4 recoil = { 0,0,0,0 };
};

struct inital_tracer
{
public:
	Vector3 start_point{};
	Vector3 end_point{};

	unsigned long end_time = 0;
};

struct tracer_info
{
public:
	Vector2 start_point{};
	Vector2 end_point{};
};

struct object_info_initial
{
	ImColor color;
	Vector3 location{};
	std::string name;
	float distance;
};

struct object_info
{
	ImColor color;
	Vector2 pos{};
	std::string name;
};

class color_t
{
public:

	float r, g, b, a;

};