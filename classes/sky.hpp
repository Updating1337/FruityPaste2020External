#pragma once

#include "includes.h"

#define default_light 8.f
#define default_ambience 0.75f

static bool set = false;

class Sky
{
public:

	static Sky* get_instance()
	{
		return driver.ReadChain<Sky*>(storage.game_assembly, { off::tod_sky_c,0xB8,0x0,0x10,0x20 });
	}

	void set_time(float time)
	{
		auto tod_cycle_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x38);

		driver.Write<float>(tod_cycle_parameters + 0x10, time);
	}

	uintptr_t get_stuff()
	{
		return driver.ReadChain<uintptr_t>(reinterpret_cast<uintptr_t>(this), { 0xA8,0x1A0,0x78 });
	}

	void enable_chams()
	{
		auto tod_night_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x58);
		auto tod_day_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x50);
		auto tod_reflection_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x98);
	
		driver.Write<uintptr_t>(tod_reflection_parameters + 0x18, 0);
	
		if (!set)
		{
			driver.Write<float>(tod_day_parameters + 0x50, 20.f);
			set = true;
		}

		Gradient* ambient = driver.Read<Gradient*>(tod_night_parameters + 0x40);
		ambient->set_color({ 1,1,1,0 });
	
	
		driver.Write<float>(tod_night_parameters + 0x54, 20);
		driver.Write<float>(tod_day_parameters + 0x54, 20);
	
		driver.Write<float>(tod_reflection_parameters + 0x24, 1);
	}
	
	auto bright_night() ->void
	{
		auto tod_night_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x58);


		driver.Write<float>(tod_night_parameters + 0x50, 6.f);
		driver.Write<float>(tod_night_parameters + 0x54, 1.f);

	}

	auto cloud_color() ->void
	{
		auto tod_night_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x58);
		auto tod_night_cloud = driver.Read<uintptr_t>(tod_night_parameters + 0x30);
		auto tod_night_cloud_color = driver.Read<uintptr_t>(tod_night_cloud + 0x10);

		driver.Write<Vector4>(tod_night_cloud_color, { cfg.cloud_color[0], cfg.cloud_color[1], cfg.cloud_color[2], 1 });

	}


	//void chams()
	//{
	//	auto tod_day_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x58);
	//	auto tod_cloud_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x78);
	//
	//	/* sky color */
	//	driver.ReadChain<Gradient*>(tod_day_parameters, { 0x28,0x10 })->set_color({ 0,0,0,0 });
	//
	//	/* sun color */
	//	driver.ReadChain<Gradient*>(tod_day_parameters, { 0x10,0x10 })->set_color({ 0,0,0,0 });
	//
	//	/* light color */
	//	driver.ReadChain<Gradient*>(tod_day_parameters, { 0x18,0x10 })->set_color({ 0,0,0,0 });
	//
	//	/* cloud color */
	//	driver.ReadChain<Gradient*>(tod_day_parameters, { 0x30,0x10 })->set_color({ 0,0,0,0 });
	//
	//	/* fog color */
	//	driver.ReadChain<Gradient*>(tod_day_parameters, { 0x38,0x10 })->set_color({ 0,0,0,0 });
	//
	//	/* ray color */
	//	driver.ReadChain<Gradient*>(tod_day_parameters, { 0x20,0x10 })->set_color({ 0,0,0,0 });
	//
	//	/* ambient color */
	//	driver.ReadChain<Gradient*>(tod_day_parameters, { 0x40,0x10 })->set_color({ 0,0,0,0 });
	//
	//	driver.Write<float>(tod_day_parameters + 0x54, 0);
	//	driver.Write<float>(tod_day_parameters + 0x50, 0);
	//	driver.Write<float>(tod_day_parameters + 0x48, 0);
	//
	//	/* tod cloud param */
	//	driver.Write<float>(tod_cloud_parameters + 0x14, 0.0f);
	//}
	


	//void enable_bright_night()
	//{
	//	auto tod_night_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x58);
	//	driver.Write<float>(tod_night_parameters + 0x50, 3.f);
	//	driver.Write<float>(tod_night_parameters + 0x48, 50.f);
	//
	//	set_time(0.0f);
	//}
	//
	//void disable_bright_night()
	//{
	//	auto tod_night_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x58);
	//	auto tod_day_parameters = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x50);
	//
	//	driver.Write<float>(tod_night_parameters + 0x48, default_light);
	//	driver.Write<float>(tod_night_parameters + 0x50, default_ambience);
	//}

};