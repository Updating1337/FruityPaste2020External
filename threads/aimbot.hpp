#pragma once

#include "includes.h"

static enum bone_choice
{
	HEAD,
	BODY,
	RANDOM,
};

class aimbot_t
{
private:
	Vector3 target{};
public:

	Vector3 prediction(Vector3 target_position)
	{
		bullet_info info{};

		info = cache.item->get_bullet_info();

		float distance = target_position.distance(camera.position);
		float velocity = info.velocity * info.velocity_scale;

		float delta = target_position.y - camera.position.y;

		target_position -= delta < -10.f ? 2.f : 0;

		if (distance > 0.1f && info.velocity > 0.1f)
		{
			float bullet_time = (distance / velocity);

			Vector3 predicted_velocity = (cache.target->model()->get_velcocity() * bullet_time) * 0.75f;

			predicted_velocity *= 1 - 0.0166666666666667f * info.drag;

			target_position += predicted_velocity;
			target_position.y += (4.905f * powf(bullet_time, 2)) * info.gravity;
		}

		return target_position;
	}

	void find_target()
	{
		srand(time(NULL));

		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(8));

			float smallest = FLT_MAX;

			Vector3 target{};
			Player* player_target = cache.local_player;

			for (int i = 0; i < cache.list.players.size(); i++)
			{
				if (cache.list.players.size() <= 0) continue;
				Player* player = cache.list.players[i];

				if (player->has_flag(Player::Flags::Sleeping) && cfg.hide_sleeper) continue;
				if (cfg.hide_npc && player->is_npc()) continue;
				if (player->is_teammate(cache.local_player->get_team())) continue;
				if (player->is_dead()) continue;

				Vector3 head{}, body{};

				float current = 0.0f;

				if (cfg.selected_bone == bone_choice::HEAD || cfg.selected_bone == bone_choice::RANDOM) head = player->get_bone(bone_list::head);
				if (cfg.selected_bone == bone_choice::BODY || cfg.selected_bone == bone_choice::RANDOM) body = player->get_bone(bone_list::spine3);

				if (cfg.selected_bone == bone_choice::HEAD)
				{
					Vector2 head_screen{};
					world_to_screen(head, head_screen);

					current = head_screen.distance(storage.screen_center);

					if (current < smallest && cfg.aimbot_fov >= current)
					{
						target = head;
						smallest = current;
						player_target = player;
					}
				}

				if (cfg.selected_bone == bone_choice::BODY)
				{
					Vector2 body_screen{};
					world_to_screen(body, body_screen);

					current = body_screen.distance(storage.screen_center);

					if (current < smallest && cfg.aimbot_fov >= current)
					{
						target = body;
						smallest = current;
						player_target = player;
					}
				}

				if (cfg.selected_bone == bone_choice::RANDOM)
				{
					int random_choice = (rand() % 2) + 1;

					/* head */
					if (random_choice == 1)
					{
						Vector2 head_screen{};
						world_to_screen(head, head_screen);

						current = head_screen.distance(storage.screen_center);

						if (current < smallest && cfg.aimbot_fov >= current)
						{
							target = head;
							smallest = current;
							player_target = player;
						}
					}

					/* body */
					if (random_choice == 2)
					{
						Vector2 body_screen{};
						world_to_screen(body, body_screen);

						current = body_screen.distance(storage.screen_center);

						if (current < smallest && cfg.aimbot_fov >= current)
						{
							target = body;
							smallest = current;
							player_target = player;
						}
					}
				}
			}

			cache.target = player_target;
			this->target = prediction(target);
		}
	}

	void run()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			if (!cfg.memory && !cfg.silent) continue;
			if (this->target == Vector3{ 0,0,0 }) continue;

			if (GetAsyncKeyState(VK_RBUTTON) && cfg.memory && cache.item->is_weapon())
				cache.local_player->input()->set_view_angles(calc_angle(camera.position, this->target).normalize());

			int aimbot_percentage = (rand() % (MAXIMUM_AIMBOT_ACCURACY - MINIMUM_AIMBOT_ACCURACY + 1)) + MINIMUM_AIMBOT_ACCURACY;

			if (aimbot_percentage <= int(cfg.hitchance))
			{
				if (GetAsyncKeyState(VK_LBUTTON) && cfg.silent && cache.item->is_weapon())
					cache.local_player->eyes()->look_at_point(calc_angle(camera.position, this->target).normalize());
			}
		}
	}
}aimbot;