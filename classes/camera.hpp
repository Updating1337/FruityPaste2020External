#pragma once

#include "includes.h"

struct vmatrix_t
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

class camera_t
{
public:
	uintptr_t object = NULL;

	Vector3 position{};
	vmatrix_t vmatrix{};

	void update()
	{
		const uintptr_t object = driver.ReadChain<uintptr_t>(storage.unity_player, { 0x17C1F18, 0x08, 0x10, 0x30,0x18 });
		this->object = object;
	}
} camera;

bool world_to_screen(const Vector3& entity_position, Vector2& screen_position)
{
	vmatrix_t vmatrix = camera.vmatrix;

	Vector3 trans_vec{ vmatrix._14, vmatrix._24, vmatrix._34 };
	Vector3 right_vec{ vmatrix._11, vmatrix._21, vmatrix._31 };
	Vector3 up_vec{ vmatrix._12, vmatrix._22, vmatrix._32 };

	float w = trans_vec.dot(entity_position) + vmatrix._44;

	if (w < 0.098f) return false;

	float y = up_vec.dot(entity_position) + vmatrix._42;
	float x = right_vec.dot(entity_position) + vmatrix._41;

	Vector2 temp = Vector2((storage.screen_center.x) * (1 + x / w), (storage.screen_center.y) * (1 - y / w));

	if (temp.y == 0) return false;

	screen_position = temp;

	return true;
}