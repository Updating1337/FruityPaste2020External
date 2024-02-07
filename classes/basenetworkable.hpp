#pragma once

#include "includes.h"

struct object_struct
{
public:
	uintptr_t pointer;
	std::string name;
};

struct tc_object_struct
{
public:
	Vector3 world_pos{};
	uintptr_t pointer;
};

struct list_info
{
public:
	std::vector<Player*> players;
	std::vector<object_struct> objects;
	std::vector<tc_object_struct> tool_cupboard;
};

class GameObject
{
public:

	unsigned short get_tag()
	{
		return driver.Read<unsigned short>(reinterpret_cast<uintptr_t>(this) + 0x54);
	}

	Vector3 get_world_position()
	{
		return driver.ReadChain<Vector3>(reinterpret_cast<uintptr_t>(this), { 0x30,0x8,0x38,0x90 });
	}

	std::string get_name()
	{
		const char* prefab_name = driver.read_str(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x60), 128);

		return prefab_name;
	}
};

static bool random = false;

class BaseNetworkable
{
public:
	static enum tags
	{
		prefab = 0,
		player = 6,
	};

	static BaseNetworkable* get_instance()
	{
		uintptr_t base_networkable = driver.Read<uintptr_t>(storage.game_assembly + off::basenetworkable_c);
		return driver.ReadChain<BaseNetworkable*>(base_networkable, { 0xb8, 0x00, 0x10, 0x28 });
	}

	list_info get_list()
	{
		uintptr_t list_base = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x18);
		int list_size = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + 0x10);

		/* list */
		list_info info{};

		for (int i = 0; i < list_size; i++)
		{
			Object* object = driver.Read<Object*>(list_base + (0x20 + (i * 0x8)));
			
			GameObject* game_object = driver.read_chain<GameObject*>(reinterpret_cast<uintptr_t>(object), { 0x10,0x30 });

			if (game_object->get_tag() == tags::player) info.players.push_back(driver.read_chain<Player*>(reinterpret_cast<uintptr_t>(object), { 0x10,0x28 }));

			if (game_object->get_tag() == tags::prefab)
			{
				if (object->get_class_name().find(_("BuildingPrivlidge")) != std::string::npos) {
					info.tool_cupboard.push_back({ game_object->get_world_position() ,object->get_class<uintptr_t>() });
				}
				else {
					info.objects.push_back({ reinterpret_cast<uintptr_t>(object),game_object->get_name() });
				}
			}
		}


		return info;
	}
};