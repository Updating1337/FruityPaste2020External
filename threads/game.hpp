#pragma once

#include "includes.h"

class game_t
{
public:
	float completion_percentage = 0.0f;

	void sky()
	{
		while (true)
		{
			if (!reinterpret_cast<uintptr_t>(cache.sky)) cfg.chams = false;

			if (cfg.chams) cache.sky->enable_chams();
			if (cfg.brightnight) cache.sky->bright_night();
			if (cfg.cloudchanger) cache.sky->cloud_color();

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void time()
	{
		int itterations = FLT_MAX;

		while (true)
		{
			if (cfg.fast_loot)
			{
				if ((cache.buttons->hover_loot() || GetAsyncKeyState(VK_RBUTTON)) && cache.inventory->is_open())
				{
					cache.time->set_timescale(5.f);
					itterations = 0;
				}

				if (itterations < 100) cache.movement->set_target_movement(Vector3());
				else if (itterations > 100 || !cache.inventory->is_open()) cache.time->set_timescale(1.0f);

				itterations++;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void interactive_debug()
	{
		Vector3 total_offset = Vector3();

		while (true)
		{
			if (cfg.interactive_debug_camera)
			{
				cache.movement->set_target_movement(Vector3());

				Vector3 current_offset = Vector3();

				if (GetAsyncKeyState('W')) current_offset += {0,0, 0.01};
				if (GetAsyncKeyState('S')) current_offset += {0, 0, -0.01};

				if (GetAsyncKeyState('A')) current_offset += {-0.01, 0, 0};
				if (GetAsyncKeyState('D')) current_offset += {0.01, 0, 0};

				if (GetAsyncKeyState(VK_SPACE)) current_offset += {0, 0.01, 0};
				if (GetAsyncKeyState(VK_LCONTROL)) current_offset += {0, -0.01, 0};

				if (GetAsyncKeyState(VK_SHIFT)) current_offset = current_offset * 3;

				total_offset += current_offset;

				cache.local_player->eyes()->set_view_offset(total_offset);
			}

			if (!cfg.interactive_debug_camera) total_offset = Vector3{};

			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}

	void bullet()
	{
		while (true)
		{
			if (cfg.thick_bullet && cache.item->is_weapon()) cache.item->bullet_thickness(1.44f);

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void omnisprint()
	{
		while (true)
		{
			if (cfg.omnisprint/* && cache.item->is_weapon()*/) cache.movement->omnisprint();
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void local()
	{
		while (true)
		{
			if (cfg.spiderman) cache.movement->spiderman();
			cfg.gravity ? cache.movement->gravity(cfg.gravitymultiplier) : cache.movement->gravity(2.35f);
			cfg.flyhack ? cache.movement->flyhack() : cache.movement->undoflyhack();
			if (cfg.flyhack) cache.local_player->modelState()->set_waterlevel(1.f);
			cfg.flyhack ? cache.local_player->speed_hack(-2.5f) : cache.local_player->speed_hack(0.f);

			if (cfg.infinite_jump) cache.movement->infinite_jump();
			cfg.fakelag ? cache.local_player->client_tick_interval(0.5f) : cache.local_player->client_tick_interval(0.05f);
			cfg.noclothingslowdown ? cache.local_player->no_clothing_slowdown(false) : cache.local_player->no_clothing_slowdown(true);
			cfg.unlockangles ? cache.local_player->unlock_angles(false) : cache.local_player->unlock_angles(true);
			if (cfg.alwayssprint) cache.movement->set_forcesprint(true);

			if (cfg.shoot_in_air)
			{
				cache.movement->set_grounded(1.f);
				cache.modelstate->add_flag(ModelState::Flag::OnGround);
			}


			if (cache.item->is_weapon())
			{
				if (cfg.instant_eoka && cache.name.find("eoka") != std::string::npos) cache.item->insta_eoka();
				if (cfg.no_spread) cache.item->no_spread();
				if (cfg.no_sway) cache.item->no_sway();
				cache.item->fast_bullet(cfg.fast_bullet);
			}

			cfg.speedhack ? cache.local_player->speed_hack(-0.25f) : cache.local_player->speed_hack(0.f);

			cfg.admin_flags ? cache.local_player->add_flag(Player::Flags::IsAdmin) : cache.local_player->remove_flag(Player::Flags::IsAdmin);

			if (cfg.shoot_in_mini) cache.local_player->mounted()->shoot_in_mini(true);

			cache.graphics->set_fov(cfg.graphics_fov);

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}

	void hit_sound()
	{
		while (true)
		{
			for (Player* player : cache.list.players)
			{
				if (player->is_local_player()) continue;

				if (player->did_headshot() || player->did_bodyshot())
				{
					if (cfg.hit_sounds) PlaySoundA(get_sound(cfg.hit_sound), NULL, SND_MEMORY | SND_ASYNC);

					if (cfg.hit_tracers)
					{
						inital_tracer info{};

						info.start_point = cache.item->get_muzzle_point(cache.local_player->input()->get_rotation());
						info.end_point = player->did_bodyshot() ? player->get_bone(bone_list::spine3) : player->get_bone(bone_list::head);
						info.end_time = util.get_time() + 1500;

						cache.initial_tracers.push_back(info);
					}
				}
			}


			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}

	void tracer()
	{
		while (true)
		{
			for (int i = 0; i < cache.initial_tracers.size(); i++)
			{
				inital_tracer info = cache.initial_tracers.at(i);

				if (info.end_time < util.get_time())
				{
					cache.initial_tracers.erase(cache.initial_tracers.begin() + i);
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}

	void reload_timer()
	{
		std::string current_weapon = "";
		bool started_timer = false;
		unsigned long current_time = 0;
		unsigned long end_time = 0;

		while (true)
		{
			if (cfg.reload_bar)
			{
				unsigned long reload_time = cache.item->get_reload_time();

				if (cache.item->is_reloading() && cache.item->is_weapon())
				{
					/* start timer */
					if (!started_timer)
					{
						current_weapon = cache.item->get_name();
						end_time = util.get_time() + (reload_time / cache.item->divisor());
						started_timer = true;
					}
				}

				if (started_timer)
				{	
					current_time = util.get_time();

					float time_left = ((float)reload_time - ((float)end_time - (float)current_time)) / (float)reload_time;

					completion_percentage = time_left;

					/* has finished */
					if (current_time > end_time)
					{
						current_weapon = "";
						end_time = 0;
						current_time = 0;
						completion_percentage = 0.0f;
						started_timer = false;

						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					}
				}

				if (!cache.item->is_weapon() || cache.item->get_name() != current_weapon)
				{
					current_weapon = "";
					end_time = 0;
					current_time = 0;
					completion_percentage = 0.0f;
					started_timer = false;
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void weapon()
	{
		while (true)
		{
			/* not inside list */
			if(cache.weapon_map.count(cache.name) == 0 && cache.item->is_weapon())
			{
				weapon_info info{};

				info.automatic = cache.item->is_automatic();
				info.repeat_delay = cache.item->get_repeat_delay();
				info.recoil = cache.item->recoil()->get();

				cache.weapon_map.insert({ cache.name,info });
			}

			/* inside of list */
			else if (cache.weapon_map.count(cache.name) > 0 && cache.item->is_weapon())
			{
				weapon_info info = cache.weapon_map.find(cache.name)->second;

				cfg.force_automatic ? cache.item->set_automatic(true) : cache.item->set_automatic(info.automatic);
				cfg.no_recoil ? cache.item->recoil()->set({ 0,0,0,0 }) : cache.item->recoil()->set(info.recoil);
				cfg.rapid_fire ? cache.item->set_repeat_delay(0.02f) : cache.item->set_repeat_delay(info.repeat_delay);
				cfg.no_melee_slowdown ? cache.item->no_melee_slowdown(false) : cache.item->no_melee_slowdown(true);
				if (cfg.instant_bow) cache.item->fast_bow(true, 1.f);
				if (cfg.instant_compound_bow) cache.item->fast_compound_bow(0.f, 0.f);
				if (cfg.no_weapon_sway) cache.item->no_weapon_sway(false, { 0, 0, 0, 0 }, { 0, 0, 0, 0 });
				if (cfg.extended_melee) cache.item->extended_melee(5.f);
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}game;