#pragma once

#include <winternl.h>
#include <filesystem>
#include <stdio.h>
#include <intrin.h>
#include <map>
#include <thread>
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdio>


//#define DEV_BUILD

/* protector */
//#include "Obsidium/obsidium64.h"

/* math */
#include "vector.hpp"
#include "math.hpp"

/* structs */
#include "structs.hpp"

/* extra security */
#include "smart_heap.hpp"
#include "lazy_importer.hpp"

/* driver */
#include "driver.hpp"

/* rendering */
#include "rendering.hpp"

/* config */
#include "keys.hpp"
#include "cfg.hpp"

/* discord */
#include "discord.hpp"

/* security */
#include "encryption.hpp"
#include "security.hpp"

/* ui */
#include "widgets.h"
#include "ui.h"

/* creating menu class */
user_interface ui;


/* utils */
#include "utils.hpp"

/* game */
#include "offsets.hpp"
#include "sounds.hpp"
#include "storage.hpp"

/* classes */
#include "classes/bone.hpp"
#include "classes/object.hpp"
#include "classes/unity.hpp"

#include "gradient.hpp"
#include "classes/sky.hpp"
#include "mounted.hpp"
#include "buttons.hpp"
#include "time.hpp"
#include "classes/uiinventory.hpp"
#include "classes/modelstate.hpp"
#include "classes/model.hpp"
#include "classes/camera.hpp"
#include "classes/eyes.hpp"
#include "classes/input.hpp"
#include "classes/playerwalkmovement.hpp"
#include "classes/recoil.hpp"
#include "classes/item.hpp"
#include "classes/player.hpp"
#include "classes/basenetworkable.hpp"
#include "classes/graphics.hpp"
#include "buildingpriviledge.hpp"

/* threads */
#include "threads/cache.hpp"
#include "threads/aimbot.hpp"
#include "threads/game.hpp"
#include "threads/render.hpp"
#include "keyhandler.hpp"

/* menu */
#include "menu.hpp"

/* unity functions */
#include "unity_functions.hpp"


/* loader streaming functions */
#include "streaming.h"

/* console color */
#define better_print(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf(x); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)
#define console_color(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)