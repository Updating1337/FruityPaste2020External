#pragma once

#include "includes.h"

class Player
{
public:
	static enum Flags
	{
		Unused1 = 1,
		Unused2 = 2,
		IsAdmin = 4,
		ReceivingSnapshot = 8,
		Sleeping = 16,
		Spectating = 32,
		Wounded = 64,
		IsDeveloper = 128,
		Connected = 256,
		ThirdPersonViewmode = 1024,
		EyesViewmode = 2048,
		ChatMute = 4096,
		NoSprint = 8192,
		Aiming = 16384,
		DisplaySash = 32768,
		Relaxed = 65536,
		SafeZone = 131072,
		ServerFall = 262144,
		Incapacitated = 524288,
		Workbench1 = 1048576,
		Workbench2 = 2097152,
		Workbench3 = 4194304
	};

	static enum CameraMode
	{
		FirstPerson,
		ThirdPerson,
		Hidden,
		FirstPersonWithArms,
		Last,
	};

	static Player* local_player()
	{
		return driver.ReadChain<Player*>(storage.game_assembly, { off::local_player_c,0xB8,0x0 });
	}

	PlayerWalkMovement* movement()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		return driver.Read<PlayerWalkMovement*>(reinterpret_cast<uintptr_t>(this) + off::base_player_playerwalkmovement);
	}

	Mounted* mounted()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		return driver.Read<Mounted*>(reinterpret_cast<uintptr_t>(this) + off::base_player_mounted);
	}

	Model* model()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		return driver.Read<Model*>(reinterpret_cast<uintptr_t>(this) + off::base_player_playermodel);
	}

	ModelState* modelState()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		return driver.Read<ModelState*>(reinterpret_cast<uintptr_t>(this) + off::base_player_modelstate);
	}

	Input* input()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		return driver.Read<Input*>(reinterpret_cast<uintptr_t>(this) + off::base_player_input);
	}

	Eyes* eyes()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		return driver.Read<Eyes*>(reinterpret_cast<uintptr_t>(this) + off::base_player_eyes);
	}

	void speed_hack(float speed)
	{
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::base_player_clothingmovespeedreduction, speed);
	}

	auto client_tick_interval(float amount) -> void
	{
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::base_player_clienttickinterval, amount);
	}

	auto no_clothing_slowdown(bool enabled) -> void
	{
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::base_player_clothingblocksaiming, enabled);
	}

	auto unlock_angles(bool enabled) -> void
	{
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::base_player_clothingblocksaiming, enabled);
		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + off::base_player_equippingblocked, enabled);
	}

	void apply_chams()
	{
		uintptr_t model = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::base_player_playermodel);
		uintptr_t material = Sky::get_instance()->get_stuff();

		// get skin type
		int skin_type = driver.Read<int>(model + 0x1cc);

		uintptr_t skinsetcollection{};

		// female
		if (skin_type == SKINTYPE_FEMALE) skinsetcollection = driver.Read<uintptr_t>(model + 0x198);

		// male
		if (skin_type != SKINTYPE_FEMALE) skinsetcollection = driver.Read<uintptr_t>(model + 0x190);

		uintptr_t skin_set_list = driver.Read<uintptr_t>(skinsetcollection + 0x18);

		uintptr_t list_ptr = driver.Read<uintptr_t>(skin_set_list + 0x20);
		int list_size = driver.Read<int>(skin_set_list + 0x18);

		for (int i = 0; i < list_size; i++)
		{
			uintptr_t current_skin_set = driver.Read<uintptr_t>(skin_set_list + (0x20 + (i * 8)));

			// null materials
			auto eye_material = driver.Write<uintptr_t>(current_skin_set + 0x78, material);
			auto body_material = driver.Write<uintptr_t>(current_skin_set + 0x70, material);
			auto head_material = driver.Write<uintptr_t>(current_skin_set + 0x68, material);
		}
	}

	int get_team()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return 0;

		return driver.Read<unsigned long>(reinterpret_cast<uintptr_t>(this) + 0x598);
	}

	bool is_teammate(unsigned long local_team)
	{
		if (!reinterpret_cast<uintptr_t>(this) || local_team == 0) return false;

		return driver.Read<unsigned long>(reinterpret_cast<uintptr_t>(this) + 0x598) == local_team;
	}

	bool is_local_player()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		return driver.Read<bool>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::base_player_playermodel) + off::player_model_islocalplayer);
	}

	bool is_npc()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		return driver.Read<bool>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::base_player_playermodel) + off::player_model_isnpc);
	}

	bool is_dead()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return true;

		return driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::base_combat_entity_lifestate) == 1;
	}

	float get_health()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return 0.0f;

		return driver.Read<float>(reinterpret_cast<uintptr_t>(this) + off::base_combat_enity_health);
	}

	bool has_flag(int flag)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		return (driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_flags)) & flag;
	}

	void add_flag(int flag)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		int current_flags = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_flags);
		driver.Write<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_flags, current_flags |= flag);
	}

	void remove_flag(int flag)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		int player_flags = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_flags);
		if (has_flag(flag)) player_flags -= flag;
		driver.Write<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_flags, player_flags);
	}

	void set_camera_mode(CameraMode mode)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		driver.Write<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_camera_mode, mode);
	}

	bool did_bodyshot()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		int hit_time = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::base_combat_entity_last_notify_frame);
		return hit_time > 0 ? driver.Write<int>(reinterpret_cast<uintptr_t>(this) + off::base_combat_entity_last_notify_frame, 0) : false;
	}

	bool did_headshot()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		int hit_time = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_lastheadshottime);
		return hit_time > 0 ? driver.Write<int>(reinterpret_cast<uintptr_t>(this) + off::base_player_lastheadshottime, 0) : false;
	}

	std::string get_name()
	{
		std::wstring wname = driver.ReadUnicode(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::base_player_name) + 0x14);

		if (wname.length() > 32 || wname.length() < 2) return _("");

		return std::string(wname.begin(), wname.end());
	}


	Vector3 get_bone(bone_list index)
	{
		return bone.get_entity_bone(reinterpret_cast<uintptr_t>(this), index);
	}

	float get_distance(Vector3 from)
	{
		return get_bone(bone_list::head).distance(from);
	}

	initial_bones get_bones()
	{
		initial_bones info{};

		info.upper_spine = get_bone(bone_list::neck);

		info.left_shoulder = get_bone(bone_list::l_upperarm);
		info.right_shoulder = get_bone(bone_list::r_upperarm);

		info.left_elbow = get_bone(bone_list::l_forearm);
		info.right_elbow = get_bone(bone_list::r_forearm);

		info.left_wrist = get_bone(bone_list::l_hand);
		info.right_wrist = get_bone(bone_list::r_hand);

		info.lower_spine = get_bone(bone_list::spine1);

		info.left_hip = get_bone(bone_list::l_hip);
		info.right_hip = get_bone(bone_list::r_hip);

		info.left_knee = get_bone(bone_list::l_knee);
		info.right_knee = get_bone(bone_list::r_knee);

		info.left_ankle = get_bone(bone_list::l_ankle_scale);
		info.right_ankle = get_bone(bone_list::r_ankle_scale);

		return info;
	}

	Item* get_held_item()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		int active_id = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + 0x5d0);

		uintptr_t contents = driver.ReadChain<uintptr_t>(reinterpret_cast<uintptr_t>(this), { 0x690,0x28,0x38 });

		if (!contents) return nullptr;

		int size = driver.Read<int>(contents + 0x18);
		uintptr_t ptr = driver.Read<uintptr_t>(contents + 0x10);

		if (!ptr) return nullptr;

		for (int i = 0; i < size; i++)
		{
			Item* item = driver.Read<Item*>(ptr + (0x20 + (i * 0x8)));
			auto item_id = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(item) + 0x28);
			if (item_id == active_id) return item;
		}

		return nullptr;
	}
};