#pragma once

#include "includes.h"

std::vector<const char*> bone_types = { "Head","Body","Random"};
std::vector<const char*> hit_sounds = { "Pop","Hitmarker"};

widgets elements;
bool exitcheat = false;
namespace menu
{
	void draw()
	{
		elements.font = ui.smallest;
		elements.sliderfont = ui.slidersmall;

		if (ui.selected_tab == 0)
		{
			elements.child(_("Aimbot Settings").c_str(), ImVec2(200, 450), ImVec2(170, 25));

			elements.slider(_("Aimbot FOV").c_str(), &cfg.aimbot_fov, 0.0f, 999.f);
			elements.combo(bone_types, &cfg.selected_bone);
			elements.checkbox(_("Memory Aimbot").c_str(), &cfg.memory);
			elements.checkbox(_("Silent Aimbot").c_str(), &cfg.silent);
			elements.slider(_("Hit Chance").c_str(), &cfg.hitchance, 1, MAXIMUM_AIMBOT_ACCURACY);
			//keybind
			//smoothing
			//vischeck
			//target team
			

			elements.child(_("Weapon Settings").c_str(), ImVec2(200, 235), ImVec2(390, 25));

			elements.checkbox(_("Force Automatic").c_str(), &cfg.force_automatic);
			elements.checkbox(_("Thick Bullet").c_str(), &cfg.thick_bullet);
			elements.checkbox(_("Instant Eoka").c_str(), &cfg.instant_eoka);
			elements.checkbox(_("No Sway").c_str(), &cfg.no_sway);
			elements.checkbox(_("No Spread").c_str(), &cfg.no_spread);
			elements.checkbox(_("Rapid Fire").c_str(), &cfg.rapid_fire);
			elements.checkbox(_("No Recoil").c_str(), &cfg.no_recoil);
			elements.checkbox(_("Fast Bullet").c_str(), &cfg.fast_bullet);
			elements.checkbox(_("Instant Bow").c_str(), &cfg.instant_bow);
			elements.checkbox(_("Instant Compound Bow").c_str(), &cfg.instant_compound_bow);

			elements.child(_("Recoil Settings").c_str(), ImVec2(200, 200), ImVec2(390, 275));

		}

		else if (ui.selected_tab == 1)
		{
			elements.child(_("World Settings").c_str(), ImVec2(200, 450), ImVec2(170, 25));

			elements.color_selector(_("###Stash Color").c_str(), cfg.stash_color);
			elements.checkbox(_("Stash").c_str(), &cfg.stash);

			elements.color_selector(_("###Hemp Color").c_str(), cfg.hemp_color);
			elements.checkbox(_("Hemp").c_str(), &cfg.hemp);

			elements.color_selector(_("###Collectable Color").c_str(), cfg.collectable_color);
			elements.checkbox(_("Collectable").c_str(), &cfg.collectable);

			elements.color_selector(_("###Food Color").c_str(), cfg.food_color);
			elements.checkbox(_("Food").c_str(), &cfg.food);

			elements.color_selector(_("###Stone Ore Color").c_str(), cfg.stone_ore_color);
			elements.checkbox(_("Stone Ore").c_str(), &cfg.stone_ore);

			elements.color_selector(_("###Sulfur Ore Color").c_str(), cfg.sulfur_ore_color);
			elements.checkbox(_("Sulfur Ore").c_str(), &cfg.sulfur_ore);

			elements.color_selector(_("###Metal Ore Color").c_str(), cfg.metal_ore_color);
			elements.checkbox(_("Metal Ore").c_str(), &cfg.metal_ore);

			elements.color_selector(_("###Elite Crate Color").c_str(), cfg.elite_crate_color);
			elements.checkbox(_("Elite Crate").c_str(), &cfg.elite_crate);

			elements.color_selector(_("###Military Crate Color").c_str(), cfg.military_crate_color);
			elements.checkbox(_("Military Crate").c_str(), &cfg.military_crate);

			elements.color_selector(_("###Normal Crate Color").c_str(), cfg.normal_crate_color);
			elements.checkbox(_("Normal Crate").c_str(), &cfg.normal_crate);

			elements.color_selector(_("###Toolbox Color").c_str(), cfg.tool_crate_color);
			elements.checkbox(_("Tool Box").c_str(), &cfg.tool_crate);

			elements.color_selector(_("###TC Color").c_str(), cfg.tc_color);
			elements.checkbox(_("ToolCupboard").c_str(), &cfg.drawTC);

			elements.color_selector(_("###Cloud Color").c_str(), cfg.cloud_color);
			elements.checkbox(_("Cloud Changer").c_str(), &cfg.cloudchanger);

			elements.checkbox(_("Brightnight").c_str(), &cfg.brightnight);

			elements.child(_("Entity Settings").c_str(), ImVec2(200, 200), ImVec2(390, 25));

			elements.color_selector(_("####Skeleton Color").c_str(), cfg.skeleton_color);
			elements.checkbox(_("Skeleton").c_str(), &cfg.skeleton);

			elements.color_selector(_("###Border Box Color").c_str(), cfg.border_box_color);
			elements.checkbox(_("Border Box").c_str(), &cfg.border_box);

			if (cfg.border_box)
				cfg.corner_box = false;

			elements.color_selector(_("###Corner Box Color").c_str(), cfg.corner_box_color);
			elements.checkbox(_("Corner Box").c_str(), &cfg.corner_box);

			if (cfg.corner_box)
				cfg.border_box = false;

			//distance
			//drawteam
			//hotbar

			elements.color_selector(_("###Tracers Color").c_str(), cfg.tracers_color);
			elements.checkbox(_("Tracers").c_str(), &cfg.tracers);

			elements.color_selector(_("###Nickname Color").c_str(), cfg.nickname_color);
			elements.checkbox(_("Nickname").c_str(), &cfg.nickname);
			 
			elements.color_selector(_("###Active Weapon Color").c_str(), cfg.active_weapon_color);
			elements.checkbox(_("Active Weapon").c_str(), &cfg.active_weapon);

			elements.checkbox(_("Health Bar").c_str(), &cfg.health_bar);

			elements.checkbox(_("Filled Box").c_str(), &cfg.fill_box);

			elements.child(_("Misc Settings").c_str(), ImVec2(200, 235), ImVec2(390, 240));

			elements.color_selector(_("###FOV Circle Color").c_str(), cfg.fov_circle_color);
			elements.checkbox(_("FOV Circle").c_str(), &cfg.fov_circle);

			elements.color_selector(_("###Hit Tracers Color").c_str(), cfg.hit_tracers_color);
			elements.checkbox(_("Hit Tracers").c_str(), &cfg.hit_tracers);

			elements.checkbox(_("Reload Bar").c_str(), &cfg.reload_bar);

			elements.color_selector(_("###FOV Circle Color").c_str(), cfg.crosshair_color);
			elements.checkbox(_("Crosshair").c_str(), &cfg.crosshair);

			elements.color_selector(_("###Chams Color").c_str(), cfg.chams_color);
			elements.checkbox(_("Chams").c_str(), &cfg.chams);

			elements.color_selector(_("###Radar Color").c_str(), cfg.radar_color);
			elements.checkbox(_("Radar").c_str(), &cfg.radar);

			if (cfg.hit_tracers)
			{
				elements.slider(_("Tracer Opacity").c_str(), &cfg.hit_tracersopacity, 0.f, 1.f);
				elements.slider(_("Tracer Thickness").c_str(), &cfg.hit_tracerthickness, 1.f, 10.f);
			}
		}

		else if (ui.selected_tab == 2)
		{
			elements.child(_("Misc Settings").c_str(), ImVec2(200, 450), ImVec2(170, 25));

			elements.slider(_("Graphics FOV").c_str(), &cfg.graphics_fov, 10, 160);
			//zoom
			//timechanger
			//brightnight
			//cloudcolor
			//skycolor
			//stars

			elements.combo(hit_sounds, &cfg.hit_sound);
			elements.checkbox(_("Hit Sounds").c_str(), &cfg.hit_sounds);

			elements.checkbox(_("Admin Flags").c_str(), &cfg.admin_flags);


			elements.child(_("Movement Settings").c_str(), ImVec2(200, 200), ImVec2(390, 25));
			elements.checkbox(_("Infinite Jump").c_str(), &cfg.infinite_jump);
			elements.checkbox(_("Spiderman").c_str(), &cfg.spiderman);
			elements.checkbox(_("Shoot In Air").c_str(), &cfg.shoot_in_air);
			elements.checkbox(_("Speedhack").c_str(), &cfg.speedhack);
			elements.checkbox(_("No Melee Slowdown").c_str(), &cfg.no_melee_slowdown);
			elements.checkbox(_("No Weapon Sway").c_str(), &cfg.no_weapon_sway);
			elements.keybind(keys.key_names[keys.flyhack_key], keys.flyhack_key);
			elements.checkbox(_("Flyhack").c_str(), &cfg.flyhack);
			elements.checkbox(_("Gravity").c_str(), &cfg.gravity);
			if (cfg.gravity)
				elements.slider(_("Gravity Multiplier").c_str(), &cfg.gravitymultiplier, 1.75f, 2.35f);

			elements.child(_("Exploit Settings").c_str(), ImVec2(200, 235), ImVec2(390, 240));

			elements.keybind(keys.key_names[keys.debug_camera_key], keys.debug_camera_key);
			elements.checkbox(_("Interactive Debug").c_str(), &cfg.interactive_debug_camera);

			elements.checkbox(_("Shoot In Minicopter").c_str(), &cfg.shoot_in_mini);
			elements.checkbox(_("Unlock Angles").c_str(), &cfg.unlockangles);
			elements.checkbox(_("Fast Loot").c_str(), &cfg.fast_loot);
			//elements.checkbox(_("Extended Melee").c_str(), &cfg.extended_melee); //needs check on if rock/spear/etc is held
			elements.checkbox(_("Fake Lag").c_str(), &cfg.fakelag);
			elements.checkbox(_("No Clothing Slowdown").c_str(), &cfg.noclothingslowdown);
			elements.checkbox(_("Always Sprint").c_str(), &cfg.alwayssprint);
			elements.checkbox(_("Omnisprint").c_str(), &cfg.omnisprint);
		}

		else if (ui.selected_tab == 3)
		{
			elements.child(_("Filter Settings").c_str(), ImVec2(200, 450), ImVec2(170, 25));

			elements.slider(_("Max Player Distance").c_str(), &cfg.max_player_distance, 0.f, 999.f);
			elements.slider(_("Max Collectable Distance").c_str(), &cfg.max_collectable_distance, 0.f, 999.f);
			elements.slider(_("Max Crate Distance").c_str(), &cfg.max_crate_distance, 0.f, 999.f);
			elements.slider(_("Max Food Distance").c_str(), &cfg.max_food_distance, 0.f, 999.f);
			elements.slider(_("Max Ore Distance").c_str(), &cfg.max_ore_distance, 0.f, 999.f);

			elements.child(_("Visual Settings").c_str(), ImVec2(200, 200), ImVec2(390, 25));

			elements.checkbox(_("Hide Sleepers").c_str(), &cfg.hide_sleeper);
			elements.checkbox(_("Hide NPC").c_str(), &cfg.hide_npc);

			elements.child(_("Cheat Info").c_str(), ImVec2(200, 235), ImVec2(390, 240));

			elements.checkbox(_("Exit Cheat").c_str(), &exitcheat);
			if (exitcheat)
				exit(1);

		}

		elements.item_count = 0;
	}
}