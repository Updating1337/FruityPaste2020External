#include "includes.h"

struct initial_player
{
public:
	Vector3 top{};
	Vector3 bottom{};

	initial_bones bones{};

	Vector3 position{};

	bool teammate = false;
	float distance;

	float health = 100.f;
	std::string name = "";
	std::string active_weapon = "";
};

struct final_player
{
public:
	Vector2 top{};
	Vector2 bottom{};
	Vector2 radarpoint{};

	player_bones bones{};

	bool teammate = false;
	float distance;

	float health = 100.f;
	std::string name = "";
	std::string active_weapon = "";
};

struct initial_tool_cupboard
{
public:
	Vector3 position{};
	std::vector<std::string> authed_players{};
	bool is_decaying = false;
};

struct final_tool_cupboard
{
public:
	Vector2 position{};
	std::vector<std::string> authed_players{};
	bool is_decaying = false;
	float distance;
};

class cache_t
{
public:
	Player* local_player;
	Player* target;
	ModelState* modelstate;
	PlayerWalkMovement* movement;
	Item* item;

	Time* time;
	Buttons* buttons;
	UIInventory* inventory;

	Graphics* graphics;
	Sky* sky;

	std::string name;

	list_info list{};

	/* players */
	std::vector<initial_player> inital_player_list{};
	std::vector<final_player> final_player_list{};
	/* */

	/* objects */
	std::vector<object_info_initial> inital_object_list{};
	std::vector<object_info> final_object_list{};
	/* */

	/* tracers */
	std::vector<inital_tracer> initial_tracers{};
	std::vector<tracer_info> tracers{};
	/* */

	/* weapon */
	std::map<std::string, weapon_info> weapon_map{};

	/* tool cupboards */
	std::vector<initial_tool_cupboard> initial_tool_cupboards{};
	std::vector<final_tool_cupboard> final_tool_cupboards{};
	/* */


	void update()
	{
		while (true)
		{

			BaseNetworkable* networkable = BaseNetworkable::get_instance();

			list = networkable->get_list();
			camera.update();

			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		}
	}

	void view_matrix()
	{
		while (true)
		{

			camera.vmatrix = driver.Read<vmatrix_t>(camera.object + 0x2E4);
			camera.position = driver.Read<Vector3>(camera.object + 0x42C);

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void local()
	{
		while (true)
		{

			local_player = Player::local_player();
			modelstate = local_player->modelState();
			movement = local_player->movement();

			item = local_player->get_held_item();
			name = item->get_shortname();

			inventory = UIInventory::get_instance();
			graphics = Graphics::get_instance();
			buttons = Buttons::get_instance();

			time = Time::get_instance();
			sky = Sky::get_instance();


			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}

	//Radar Function
	Vector2 WorldToRadar(Vector3 origin, Vector2 position, INT size, FLOAT rotation)
	{
		Vector2 clampRotation
		((float)cosf((rotation * (M_PI / 180.f)) + M_PI),
			-(float)sinf((rotation * (M_PI / 180.f)) + M_PI));

		Vector2 clampCoords
		((origin.x * clampRotation.x + origin.z * clampRotation.y),
			(origin.x * clampRotation.y - origin.z * clampRotation.x));

		INT clampSize
		(size / 2.0f);

		Vector2 bVec
		(-clampCoords.x + position.x + clampSize,
			-clampCoords.y + position.y + clampSize);

		bVec.x = -clampCoords.x + position.x + clampSize;
		bVec.y = -clampCoords.y + position.y + clampSize;

		if (bVec.x > (position.x + size)) bVec.x = (position.x + size);
		else if (bVec.x < (position.x)) bVec.x = position.x;

		if (bVec.y > (position.y + size)) bVec.y = (position.y + size);
		else if (bVec.y < (position.y)) bVec.y = position.y;

		return bVec;
	}

	void players()
	{
		while (true)
		{
			std::vector<initial_player> temp{};

			for (int i = 0; i < list.players.size(); i++)
			{
				if (list.players.size() <= 0) continue;
				Player* player = list.players[i];

				if (!cfg.skeleton && !cfg.tracers && !cfg.nickname && !cfg.active_weapon && !cfg.border_box && !cfg.corner_box && !cfg.health_bar) continue;
				if (player->is_dead() || player->is_local_player() || player->get_distance(camera.position) > cfg.max_player_distance || (player->has_flag(Player::Flags::Sleeping) && cfg.hide_sleeper) || (player->is_npc() && cfg.hide_npc)) continue;

				//player->model()->swap_material();

				initial_player info{};

				Vector3 temp_bottom = (player->get_bone(bone_list::l_foot) + player->get_bone(bone_list::r_foot)) / 2;
				Vector3 temp_top = player->get_bone(bone_list::head);

				info.top = { temp_top.x,temp_top.y + 0.25f,temp_top.z };
				info.bottom = { temp_bottom.x,temp_bottom.y - 0.125f,temp_bottom.z };


				if (cfg.skeleton) info.bones = player->get_bones();
				if(cfg.nickname) info.name = player->get_name();
				if(cfg.health_bar) info.health = player->get_health();
				if (info.name == player->get_held_item()->get_shortname()) info.active_weapon = _("None");
				else info.active_weapon = player->get_held_item()->get_name();
				if (info.active_weapon.length() <= 3) info.active_weapon = _("None");

				info.teammate = player->is_teammate(local_player->get_team());

				temp.push_back(info);
			}
			
			inital_player_list = temp;
			temp.clear();

			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}
	}

	void objects()
	{
		while (true)
		{


			std::vector<object_info_initial> temp{};

			for (int i = 0; i < list.objects.size(); i++)
			{
				if (list.objects.size() <= 0) continue;
				object_struct object = list.objects[i];

				std::string name = _("");
				ImColor color = ImColor(255, 255, 255);
				float max_distance = 100.f;

				/* stash */
				if (util.find_string(object.name,_("stash")) && cfg.stash)
				{
					name = _("Stash");
					color = get_color(cfg.stash_color);
					max_distance = cfg.max_stash_distance;
				}
				/*------*/

				/* hemp */
				if (util.find_string(object.name, _("hemp")) && cfg.hemp)
				{
					name = _("Hemp");
					color = get_color(cfg.hemp_color);
					max_distance = cfg.max_hemp_distance;
				}
				/*------*/

				/* stone */
				if (util.find_string(object.name, _("stone-ore")) && cfg.stone_ore)
				{
					name = _("Stone Ore");
					color = get_color(cfg.stone_ore_color);
					max_distance = cfg.max_ore_distance;
				}

				if (util.find_string(object.name, _("stone-collectable")) && cfg.collectable)
				{
					name = _("Stone Collectable");
					color = get_color(cfg.collectable_color);
					max_distance = cfg.max_collectable_distance;
				}
				/*------*/

				/* sulfur */
				if (util.find_string(object.name, _("sulfur-ore")) && cfg.sulfur_ore)
				{
					name = _("Sulfur Ore");
					color = get_color(cfg.sulfur_ore_color);
					max_distance = cfg.max_ore_distance;
				}

				if (util.find_string(object.name, _("sulfur-collectable")) && cfg.collectable)
				{
					name = _("Sulfur Collectable");
					color = get_color(cfg.collectable_color);
					max_distance = cfg.max_collectable_distance;
				}
				/*------*/

				/* metal */
				{
					if (util.find_string(object.name, _("metal-ore")) && cfg.metal_ore)
					{
						name = _("Metal Ore");
						color = get_color(cfg.metal_ore_color);
						max_distance = cfg.max_ore_distance;
					}

					if (util.find_string(object.name, _("metal-collectable")) && cfg.collectable)
					{
						name = _("Metal Collectable");
						color = get_color(cfg.collectable_color);
						max_distance = cfg.max_collectable_distance;
					}
				}
				/*------*/

				/* food */
				{
					if (util.find_string(object.name, _("mushroom-cluster")) && cfg.food)
					{
						name = _("Mushroom");
						color = get_color(cfg.food_color);
						max_distance = cfg.max_food_distance;
					}

					if (util.find_string(object.name, _("potato-collectable")) && cfg.food)
					{
						name = _("Potato");
						color = get_color(cfg.food_color);
						max_distance = cfg.max_food_distance;
					}

					if (util.find_string(object.name, _("crate_normal_2_food")) && cfg.food)
					{
						name = _("Food Crate");
						color = get_color(cfg.food_color);
						max_distance = cfg.max_food_distance;
					}
				}
				/*------*/

				/* crates */
				{
					if (util.find_string(object.name, _("crate_elite")) && cfg.elite_crate)
					{
						name = _("Elite Crate");
						color = get_color(cfg.elite_crate_color);
						max_distance = cfg.max_crate_distance;
					}

					if (util.find_string(object.name, _("crate_normal")) && cfg.military_crate)
					{
						name = _("Military Crate");
						color = get_color(cfg.military_crate_color);
						max_distance = cfg.max_crate_distance;
					}

					if (util.find_string(object.name, _("crate_normal_2")) && cfg.normal_crate)
					{
						name = _("Normal Crate");
						color = get_color(cfg.normal_crate_color);
						max_distance = cfg.max_crate_distance;
					}

					if (util.find_string(object.name, _("crate_tools")) && cfg.tool_crate)
					{
						name = _("Tool Box");
						color = get_color(cfg.tool_crate_color);
						max_distance = cfg.max_crate_distance;
					}
				}
				/*------*/

				if (name != _("").c_str())
				{
					GameObject* game_object = driver.ReadChain<GameObject*>(object.pointer, { 0x10,0x30 });

					object_info_initial info{};

					info.location = game_object->get_world_position();
					info.distance = info.location.distance(camera.position);
					info.name = name;
					info.color = color;

					if (info.distance < max_distance) temp.push_back(info);
				}
			}

			inital_object_list = temp;
			temp.clear();

			std::vector<initial_tool_cupboard> temp_cupbards{};

			for (tc_object_struct tc : list.tool_cupboard)
			{
				BuildingPrivlidge* privlidge = reinterpret_cast<BuildingPrivlidge*>(tc.pointer);

				initial_tool_cupboard info{};

				info.authed_players = privlidge->players();
				info.is_decaying = privlidge->is_decaying();
				info.position = tc.world_pos;

				temp_cupbards.push_back(info);
			}

			initial_tool_cupboards = temp_cupbards;
			temp_cupbards.clear();

			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	
	void convert()
	{
		while (true)
		{

			std::vector<final_player> temp_players{};

			for (initial_player player : inital_player_list)
			{
				final_player info{};

				info.teammate = player.teammate;
				info.health = player.health;
				info.name = player.name;
				info.active_weapon = player.active_weapon;
				info.distance = player.top.distance(camera.position);

				Vector3 angles = local_player->input()->RadarGetViewAngles();

				info.radarpoint = WorldToRadar(player.top - camera.position, Vector2(cfg.radarpos.x, cfg.radarpos.y), cfg.radarsize, angles.y);

				if(!world_to_screen(player.top,info.top)) continue;
				if(!world_to_screen(player.bottom, info.bottom)) continue;

				
				if (cfg.skeleton)
				{
					/* upper */
					{
						world_to_screen(player.bones.upper_spine, info.bones.upper_spine);

						world_to_screen(player.bones.left_shoulder, info.bones.left_shoulder);
						world_to_screen(player.bones.right_shoulder, info.bones.right_shoulder);

						world_to_screen(player.bones.left_elbow, info.bones.left_elbow);
						world_to_screen(player.bones.right_elbow, info.bones.right_elbow);

						world_to_screen(player.bones.left_wrist, info.bones.left_wrist);
						world_to_screen(player.bones.right_wrist, info.bones.right_wrist);
					}

					/* lower */
					{
						world_to_screen(player.bones.lower_spine, info.bones.lower_spine);

						world_to_screen(player.bones.left_hip, info.bones.left_hip);
						world_to_screen(player.bones.right_hip, info.bones.right_hip);

						world_to_screen(player.bones.left_knee, info.bones.left_knee);
						world_to_screen(player.bones.right_knee, info.bones.right_knee);

						world_to_screen(player.bones.left_ankle, info.bones.left_ankle);
						world_to_screen(player.bones.right_ankle, info.bones.right_ankle);
					}
				}

				temp_players.push_back(info);
			}
	
			final_player_list = temp_players;
			temp_players.clear();

			std::vector<object_info> temp_objects{};

			for (object_info_initial object : inital_object_list)
			{
				object_info info{};

				if (!world_to_screen(object.location, info.pos)) continue;
				info.name = object.name + _(" (") + std::to_string((int)object.distance) + _(")");
				info.color = object.color;

				temp_objects.push_back(info);
			}

			final_object_list = temp_objects;
			temp_objects.clear();

			std::vector<tracer_info> temp_tracers{};

			for (inital_tracer info : cache.initial_tracers)
			{
				tracer_info tracer{};

				if (!world_to_screen(info.start_point, tracer.start_point)) continue;
				if (!world_to_screen(info.end_point, tracer.end_point)) continue;

				temp_tracers.push_back(tracer);
			}

			tracers = temp_tracers;
			temp_tracers.clear();

			std::vector<final_tool_cupboard> temp_cupboard{};

			for (initial_tool_cupboard tc : cache.initial_tool_cupboards)
			{
				final_tool_cupboard info{};

				info.is_decaying = tc.is_decaying;
				info.authed_players = tc.authed_players;
				info.distance = tc.position.distance(camera.position);

				if (!world_to_screen(tc.position, info.position)) continue;

				temp_cupboard.push_back(info);
			}

			final_tool_cupboards = temp_cupboard;
			temp_cupboard.clear();

			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}
	
}cache;