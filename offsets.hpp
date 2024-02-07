#pragma once

#include <windows.h>

#define offset constexpr uintptr_t

namespace off
{
	offset local_player_c = 0x31B7EF8;
	offset basenetworkable_c = 0x31B68B8;
	offset admin_c = 0x31B00D8;
	offset graphics_c = 0x31B4530;
	offset tod_sky_c = 0x31B9130;

	/* base player offsets */
	offset base_player_playermodel = 0x4C0;
	offset base_player_mounted = 0x5F8;
	offset base_player_modelstate = 0x5F0;
	offset base_player_eyes = 0x680;
	offset base_player_input = 0x4E0;
	offset base_player_playerwalkmovement = 0x4E8;
	offset base_player_lastheadshottime = 0x740;
	offset base_player_flags = 0x678;
	offset base_player_camera_mode = 0x4A4;
	offset base_player_name = 0x6D8;
	offset base_player_clienttickinterval = 0x648;
	offset base_player_clothingblocksaiming = 0x748;
	offset base_player_equippingblocked = 0x758;
	offset base_player_clothingmovespeedreduction = 0x74C;

	/* modelstate offsets */
	offset model_state_flags = 0x24;

	/* base combat entity offsets */
	offset base_combat_entity_lifestate = 0x21C;
	offset base_combat_enity_health = 0x224;
	offset base_combat_entity_last_notify_frame = 0x234;

	/* player model offsets */
	offset player_model_velocity = 0x224;
	offset player_model_islocalplayer = 0x299;
	offset player_model_maleskin = 0x190;
	offset player_model_femaleskin = 0x198;
	offset player_model_isnpc = 0x320;

	/* item offsets */
	offset item_baseprojectile = 0x98;
	offset item_definition = 0x20;

	/* base projectile offsets */
	offset baseprojectile_automatic = 0x288;
	offset baseprojectile_sway = 0x2d0;
	offset baseprojectile_recoil = 0x2d8;
	offset baseprojectile_delay = 0x1f4;
	offset baseprojectile_attackready = 0x360;
	offset baseprojectile_arrowback = 0x364;
	offset baseprojectile_stringholddurationmax = 0x378;
	offset baseprojectile_movementpenaltyrampuptime = 0x388;
	offset baseprojectile_nextreloadtime = 0x314;
	offset baseprojectile_reloadtime = 0x2B0;

	/* held entity offsets */
	offset heldentity_viewModel = 0x198;

	/* base melee offsets */
	offset basemelee_blocksprintonattack = 0x299;
	offset basemelee_maxdistance = 0x290;

	/* player walk movement */
	offset player_walk_movement_ground_angle = 0xC4;
	offset player_walk_movement_ground_angle_new = 0xC8;
	offset player_walk_movement_ground_time = 0xCC;
	offset player_walk_movement_jump_time = 0xD0;
	offset player_walk_movement_land_time = 0xD4;
	offset player_walk_movement_grounded = 0x4C;
	offset player_walk_movement_sprinting = 0x40;
	offset player_walk_movement_sprintforced = 0x134;
	offset player_walk_movement_target_movement = 0x34;
	offset player_walk_movement_capsule_center = 0x6C;
	offset player_walk_movement_gravitymultiplier = 0x84;

	/* player input */
	offset player_input_body_angles = 0x3C;
	offset player_input_rotation = 0x2C;

	/* player eyes */
	offset eyes_view_offest = 0x38;
	offset eyes_body_rotation = 0x44;
}