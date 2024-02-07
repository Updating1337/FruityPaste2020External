#pragma once

#include "includes.h"

#define SKINTYPE_FEMALE 1

class Model
{
public:
	Vector3 get_velcocity()
	{
		return driver.Read<Vector3>(reinterpret_cast<uintptr_t>(this) + off::player_model_velocity);
	}

	void z_index_chams()
	{
        // get skin type
        int skin_type = driver.Read<int>(reinterpret_cast<uintptr_t>(this) + 0x1bc);
    
        uintptr_t skinsetcollection{};
    
        // female
        if (skin_type == SKINTYPE_FEMALE)
            skinsetcollection = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x198);
    
        // male
        if (skin_type != SKINTYPE_FEMALE)
            skinsetcollection = driver.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x190);
    
        uintptr_t skin_set_list = driver.Read<uintptr_t>(skinsetcollection + 0x18);
    
        uintptr_t list_ptr = driver.Read<uintptr_t>(skin_set_list + 0x20);
        int list_size = driver.Read<int>(skin_set_list + 0x18);
    
        for (int i = 0; i < list_size; i++)
        {
            uintptr_t current_skin_set = driver.Read<uintptr_t>(skin_set_list + (0x20 + (i * 8)));
    
            uintptr_t material = Sky::get_instance()->get_stuff();

            // null materials
            auto eye_material = driver.Write<uintptr_t>(current_skin_set + 0x78, material);
            auto body_material = driver.Write<uintptr_t>(current_skin_set + 0x70, material);
            auto head_material = driver.Write<uintptr_t>(current_skin_set + 0x68, material);
        }
	}
};