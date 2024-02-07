#pragma once

#include "includes.h"

struct bullet_info
{
	float velocity = 333;
	float drag = 1.0f;
	float gravity = 1.0f;
	float velocity_scale = 1.0f;
	float velocity_scalar = 1.0f;
};

struct ProjectileWeaponModModifier
{
	bool enabled;
	float scalar;
	float _offset;
};


class Item
{
public:
	bool is_weapon()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		return driver.Read<int>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_definition) + 0x40) == 0;
	}


	bool is_pistol()
	{
		uintptr_t magazine = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x2B8);

		uintptr_t nameptr = driver.Read<uintptr_t>(driver.Read<uintptr_t>(magazine + off::item_definition) + 0x20);
		std::wstring shortname = driver.ReadUnicode(nameptr + 0x14);

		std::string name = std::string(shortname.begin(), shortname.end());

		return name.find("pistol") != std::string::npos;
	}

	void fast_bullet(bool on)
	{
		float multiplier = on ? (is_pistol() ? 1.195f : 1.44f) : 1.f;

		driver.Write<float>(reinterpret_cast<uintptr_t>(this) + 0x284, multiplier);
	}

	void insta_eoka()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);

		if (!base_projectile) return;

		driver.Write<float>(base_projectile + 0x360, 1.0f);

		GetAsyncKeyState(VK_LBUTTON) & 0x8000 ?
			driver.Write<bool>(base_projectile + 0x370, true), driver.Write<bool>(base_projectile + 0x371, true)
			: driver.Write<bool>(base_projectile + 0x370, false);
	}

	void apply_chams()
	{
		uintptr_t item_skin = driver.Read<uintptr_t>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile) + 0xB8);

		uintptr_t material = Sky::get_instance()->get_stuff();

		uintptr_t skin_list = driver.Read<uintptr_t>(item_skin + 0x78);

		uintptr_t item_skin_list = driver.Read<uintptr_t>(skin_list + 0x20);

		int item_list_size = driver.Read<int>(skin_list + 0x18);
		for (int i = 0; i < item_list_size; i++)
		{
			printf("%i\n", i);

			uintptr_t current_ptr = driver.Read<uintptr_t>(item_skin_list + (0x20 + (i * 8)));
			driver.Write<uintptr_t>(current_ptr, material);
		}
	}

	unsigned long get_reload_time()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return 0;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);

		if (!base_projectile) return 0;

		return driver.Read<float>(base_projectile + 0x2b0) * 1000;
	}

	Vector3 get_muzzle_point(Vector4 body_rotation)
	{
		Vector3 pos = bone.get_transform_position(driver.ReadChain<uintptr_t>(reinterpret_cast<uintptr_t>(this), { off::item_baseprojectile,0x2a8,0x10 }));

		return pos == Vector3() ? camera.position + quaternion_mult(&vec_forward, &body_rotation) : pos + quaternion_mult(&vec_forward, &body_rotation);
	}

	bool is_reloading()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);

		if (!base_projectile) return false;

		return driver.Read<bool>(base_projectile + 0x324);
	}

	int divisor()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return 1;
		
		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return 1;

		return driver.Read<bool>(base_projectile + 0x2C0) ? driver.Read<int>(base_projectile + 0x340) : 1;
	}

	void set_automatic(bool automatic)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		driver.Write<bool>(base_projectile  + off::baseprojectile_automatic, automatic);
	}

	bool is_automatic()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return false;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return false;

		return driver.Read<bool>(base_projectile + off::baseprojectile_automatic);
	}

	void fast_bow(bool attackready, float arrowback)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		driver.Write<bool>(base_projectile + off::baseprojectile_attackready, attackready);
		driver.Write<bool>(base_projectile + off::baseprojectile_arrowback, arrowback);
	}

	void fast_compound_bow(float stringHoldDurationMax, float movementPenaltyRampUpTime)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		driver.Write<float>(base_projectile + off::baseprojectile_stringholddurationmax, stringHoldDurationMax);
		driver.Write<float>(base_projectile + off::baseprojectile_movementpenaltyrampuptime, movementPenaltyRampUpTime);
	}

	void no_melee_slowdown(bool blocksprintonattack)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		driver.Write<bool>(base_projectile + off::basemelee_blocksprintonattack, blocksprintonattack);
	}

	auto no_weapon_sway(bool lowering, Vector4 bobbing, Vector4 bobb) -> void
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		auto viewmodel = driver.Read<uintptr_t>(base_projectile + off::heldentity_viewModel);
		auto instance = driver.Read<uintptr_t>(viewmodel + 0x28);
		auto sway = driver.Read<uintptr_t>(instance + 0x68);
		auto lower = driver.Read<uintptr_t>(instance + 0x70);
		auto bob = driver.Read<uintptr_t>(instance + 0x78);

		driver.Write<bool>(lower + 0x20, lowering);
		driver.Write<Vector4>(bob + 0x18, bobbing);
		driver.Write<Vector4>(bob + 0x28, bobb);
	}

	auto extended_melee(float distance) -> void
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		driver.Write<bool>(base_projectile + off::basemelee_maxdistance, distance);
	}

	float get_repeat_delay()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return 0.133f;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return 0.0f;

		return driver.Read<float>(base_projectile + off::baseprojectile_delay);
	}

	void set_repeat_delay(float delay)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		driver.Write<float>(base_projectile + off::baseprojectile_delay,delay);
	}

	auto no_sway() -> void
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return;

		driver.Write<float>(base_projectile + off::baseprojectile_sway, 0.0f);
	}

	void bullet_thickness(float thickness)
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		auto list = driver.Read<uintptr_t>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile) + 0x358);

		if (!list) return;

		uintptr_t list_ptr = driver.Read<uintptr_t>(list + 0x10);
		int list_size = driver.Read<int>(list + 0x18);

		if (!list_ptr) return;

		for (int i = 0; i < list_size; i++)
		{
			auto current_projectile = driver.Read<uintptr_t>(list_ptr + (0x20 + (i * 0x8)));
			if(current_projectile) driver.Write<float>(current_projectile + 0x2C, thickness);
		}
	}

	std::string get_shortname()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return "";

		uintptr_t nameptr = driver.Read<uintptr_t>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_definition) + 0x20);
		std::wstring shortname = driver.ReadUnicode(nameptr + 0x14);

		return std::string(shortname.begin(), shortname.end());
	}

	std::string get_name()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return "";

		uintptr_t translation = driver.Read<uintptr_t>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_definition) + 0x28);
		uintptr_t nameptr = driver.Read<uintptr_t>(translation + 0x18);
		std::wstring shortname = driver.ReadUnicode(nameptr + 0x14);

		// shotgun filter
		{
			std::wstring shotgun_filter = L" Shotgun";
			size_t shotgun_pos = shortname.find(shotgun_filter);
			if (shotgun_pos != std::string::npos)
				shortname.erase(shotgun_pos, shotgun_filter.length());
		}
		// shorten some names more
		{
			std::wstring automatic_filter = L"Automatic "; // so we can keep 'semi-rifle', 'semi-pistol', etc...
			size_t automatic_pos = shortname.find(automatic_filter);
			if (automatic_pos != std::string::npos)
				shortname.erase(automatic_pos, automatic_filter.length());

			std::wstring lr_300_filter = L"LR-300 Assault Rifle"; // shorten to 'LR-300'
			size_t lr_300_pos = shortname.find(lr_300_filter);
			if (lr_300_pos != std::string::npos) shortname = L"LR-300";
		}

		return (shortname.length() > 128 || shortname.empty()) ? "None" : std::string(shortname.begin(), shortname.end());
	}

	bullet_info get_bullet_info()
	{
		bullet_info info{};

		if (!reinterpret_cast<uintptr_t>(this)) return info;

		info.velocity_scale = driver.Read<float>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile) + 0x284);

		auto magazine = driver.Read<uintptr_t>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile) + 0x2B8);
		auto unity_class = driver.ReadChain<uintptr_t>(magazine, { 0x20,0x10,0x30 });
		auto itemModProjectile = get_component(unity_class, "ItemModProjectile", false);

		info.velocity = driver.Read<float>(itemModProjectile + 0x34);

		uintptr_t projectile_object = driver.ReadChain<uintptr_t>(itemModProjectile, { 0x18, 0x18, 0x10 });

		if (!projectile_object) return info;

		uintptr_t projectile = get_component(projectile_object, "Projectile", false);

		if (!projectile) return info;

		Vector2 proj_info = driver.Read<Vector2>(projectile + 0x24);

		info.drag = proj_info.x;
		info.gravity = proj_info.y;

		uintptr_t children_list = driver.Read<uintptr_t>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile) + 0x40);

		if (!children_list) return info;

		int child_count = driver.Read<int>(children_list + 0x18);
		children_list = driver.Read<uintptr_t>(children_list + 0x10);

		if (!children_list) return info;

		for (int x = 0; x < child_count; x++)
		{
			Object* child_entity = driver.Read<Object*>(children_list + (0x20 + (x * 0x8)));

			if (child_entity->get_class_name().find("ProjectileWeaponMod") != std::string::npos)
			{
				uintptr_t modifier = driver.Read<uintptr_t>((reinterpret_cast<uintptr_t>(child_entity) + 0x178));
				if (driver.Read<bool>(modifier)) info.velocity_scalar = driver.Read<float>(modifier + 0x4);
			}
		}

		return info;
	}

	void no_spread()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return;

		uintptr_t magazine = driver.Read<uintptr_t>(driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile) + 0x2b8);

		if (!magazine) return;

		magazine = driver.Read<uintptr_t>(magazine + 0x20);
		magazine = driver.Read<uintptr_t>(magazine + 0x10);
		uintptr_t klass = driver.Read<uintptr_t>(magazine + 0x30);

		if (!klass) return;

		uintptr_t itemModProjectile = get_component(klass, "ItemModProjectile", false);

		if (!itemModProjectile) return;

		driver.Write<float>(itemModProjectile + 0x30, 0.0f);
		driver.Write<float>(itemModProjectile + 0x38, 0.0f);

		uintptr_t base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);

		if (!base_projectile) return;

		driver.Write<float>(base_projectile + 0x2E8, 0.0f);
		driver.Write<float>(base_projectile + 0x2EC, 0.0f);
		driver.Write<float>(base_projectile + 0x2F4, 0.0f);
		driver.Write<float>(base_projectile + 0x2F0, 0.0f);
		driver.Write<float>(base_projectile + 0x300, 0.0f);
	}

	RecoilProperties* recoil()
	{
		if (!reinterpret_cast<uintptr_t>(this)) return nullptr;

		uintptr_t base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		if (!base_projectile) return nullptr;

		return driver.Read<RecoilProperties*>(base_projectile + off::baseprojectile_recoil);
	}

	auto NextReloadTime() -> float
	{
		//if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		//if (!base_projectile) return;

		return driver.Read<float>(base_projectile + off::baseprojectile_nextreloadtime);
	}

	//auto HasReloadCooldown() -> bool
	//{
	//	return cache.time->get_time() < this->NextReloadTime();
	//}

	auto ReloadTime() -> float
	{
		//if (!reinterpret_cast<uintptr_t>(this)) return;

		auto base_projectile = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + off::item_baseprojectile);
		//if (!base_projectile) return;

		return driver.Read<float>(base_projectile + off::baseprojectile_reloadtime);
	}

	auto CalculateCooldownTime(float nextTime, float cooldown) -> float
	{
		float num = util.get_time();
		float num2 = 0.f;

		float ret = nextTime;

		if (ret < 0.f) {
			ret = max(0.f, num + cooldown - num2);
		}
		else if (num - ret <= num2) {
			ret = min(ret + cooldown, num + cooldown);
		}
		else {
			ret = max(ret + cooldown, num + cooldown - num2);
		}
		return ret;
	}
};