#pragma once

#include <Windows.h>

#define MAXIMUM_AIMBOT_ACCURACY 100
#define MINIMUM_AIMBOT_ACCURACY 1

class config_t
{
public:
	/* AIMBOT */
	int selected_bone = 0;
	float aimbot_fov = 100.f;
	bool enabled = false;
	bool memory = false;
	bool silent = false;
	float hitchance = 100.f;

	/* PLAYER VISUALS */
	float max_player_distance = 350.f;
	bool hide_sleeper = false;
	bool hide_npc = false;

	bool health_bar = false;
	bool distance = false;

	bool tracers = false;
	float tracers_color[3] = { 1.0f,1.0f,1.0f };

	bool skeleton = false;
	float skeleton_color[3] = { 1.0f,1.0f,1.0f };

	bool radar = false;
	float radar_color[3] = { 0.f,0.f,0.f };
	float radarsize = 250;

	Vector2 radarpos = { 50, 50 };

	bool border_box = false;
	float border_box_color[3] = { 1.0f,1.0f,1.0f };

	bool corner_box = false;
	float corner_box_color[3] = { 1.0f,1.0f,1.0f };

	bool fill_box = false;

	bool nickname = false;
	float nickname_color[3] = { 1.0f,1.0f,1.0f };

	bool active_weapon = false;
	float active_weapon_color[3] = { 1.0f,1.0f,1.0f };


	/* misc visuals */
	bool reload_bar = false;
	float chams_color[3] = { 1.0f,1.0f,1.0f };
	bool chams = false;


	bool brightnight = false;
	bool cloudchanger = false;
	float cloud_color[3] = { 1.0f,1.0f,1.0f };

	float hit_tracers_color[3] = { 1.0f,1.0f,1.0f };
	bool hit_tracers = false;
	float hit_tracersopacity = 0.4f;
	float hit_tracerthickness = 3.f;


	bool crosshair = false;
	float crosshair_color[3] = { 1.0f,0.f,0.f };


	bool fov_circle = false;
	float fov_circle_color[3] = { 1.0f,1.0f,1.0f };

	/* WORLD VISUALS */
	bool stash = false;
	float max_stash_distance = 100.f;
	float stash_color[3] = { 1.0f,1.0f,1.0f };

	bool hemp = false;
	float max_hemp_distance = 100.f;
	float hemp_color[3] = { 1.0f,1.0f,1.0f };

	bool collectable = false;
	float max_collectable_distance = 100.f;
	float collectable_color[3] = { 1.0f,1.0f,1.0f };

	bool food = false;
	float max_food_distance = 100.f;
	float food_color[3] = { 1.0f,1.0f,1.0f };

	/* ore */
	float max_ore_distance = 100.f;

	bool metal_ore = false;
	float metal_ore_color[3] = { 1.0f,1.0f,1.0f };

	bool sulfur_ore = false;
	float sulfur_ore_color[3] = { 1.0f,1.0f,1.0f };

	bool stone_ore = false;
	float stone_ore_color[3] = { 1.0f,1.0f,1.0f };
	/*    */

	bool drawTC = false;
	float tc_color[3] = { 1.0f,1.0f,1.0f };

	bool hotbar = false;

	/* crate */
	float max_crate_distance = 100.f;

	bool military_crate = false;
	float military_crate_color[3] = { 1.0f,1.0f,1.0f };

	bool elite_crate = false;
	float elite_crate_color[3] = { 1.0f,1.0f,1.0f };

	bool normal_crate = false;
	float normal_crate_color[3] = { 1.0f,1.0f,1.0f };

	bool tool_crate = false;
	float tool_crate_color[3] = { 1.0f,1.0f,1.0f };
	/*  */

	/* vehicle */
	float max_vehicle_distance = 100.f;

	bool minicopter = false;
	float minicopter_color[3] = { 1.0f,1.0f,1.0f };
	/* */

	/* WEAPON */
	bool no_recoil = false;
	bool no_sway = false;
	bool no_spread = false;
	bool instant_eoka = false;
	bool force_automatic = false;
	bool thick_bullet = false;
	bool rapid_fire = false;
	bool fast_bullet = false;
	bool instant_bow = false;
	bool instant_compound_bow = false;
	bool no_melee_slowdown = false;
	bool no_weapon_sway = false;
	bool extended_melee = false;

	/* MISC */
	float graphics_fov = 90.f;
	bool admin_flags = false;
	bool shoot_in_air = false;
	bool spiderman = false;
	bool infinite_jump = false;
	bool speedhack = false;
	bool gravity = false;
	float gravitymultiplier = 2.35f;
	bool fakelag = false;
	bool noclothingslowdown = false;
	bool unlockangles = false;
	bool alwayssprint = false;
	bool omnisprint = false;
	bool flyhack = false;

	int hit_sound = 0;
	bool hit_sounds = false;

	/* EXPLOITS */
	bool interactive_debug_camera = false;
	bool fast_loot = false;
	bool shoot_in_mini = false;
}cfg;