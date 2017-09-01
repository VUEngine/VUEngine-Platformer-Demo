/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <VIPManager.h>
#include <Fonts.h>
#include <Hero.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_MAIN_TOWER_EP;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern u16 KRISSE_BGM[][2];

extern EntityDefinition BANDANA_AG;
extern EntityDefinition COIN_AG;
extern EntityDefinition COG_WHEEL_IM;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition COLLISION_HIT_CL;
extern EntityDefinition COLLISION_TOP_CL;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition KEY_DOOR_AG;
extern EntityDefinition GOAL_DOOR_AG;
extern EntityDefinition GRASS_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition LAVA_IG;
extern EntityDefinition LAVA_TOP_AG;
extern EntityDefinition LAVA_TRIGGER_IG;
extern EntityDefinition LEVEL_1_TOWER_MAIN_1_IM;
extern EntityDefinition LEVEL_1_TOWER_MAIN_2_IM;
extern EntityDefinition LEVEL_1_TOWER_MAIN_BACK_IM;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition MOVING_PLATFORM_V6_AC;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition SNAIL_8_AC;
extern EntityDefinition TORCH_AG;
extern EntityDefinition TORCH_OFF_IM;
extern EntityDefinition TORCH_LIGHT_AG;
extern EntityDefinition DARKNESS_OVERLAY_IM;
extern EntityDefinition TORCH_SMOKE_PS;


extern TextureDefinition COG_WHEEL_TX;
extern TextureDefinition DOOR_TX;
extern TextureDefinition GUI_TX;
extern TextureDefinition LAVA_TOP_TX;
extern TextureDefinition LAVA_TX;
extern TextureDefinition LEVEL_1_TOWER_BACK_1_TX;
extern TextureDefinition LEVEL_1_TOWER_MAIN_1_TX;
extern TextureDefinition LEVEL_1_TOWER_MAIN_BACK_1_TX;
extern TextureDefinition DARKNESS_OVERLAY_TX;

extern Size collision_2_64_1;
extern Size collision_4_2_1;
extern Size collision_4_4_1;
extern Size collision_4_8_1;
extern Size collision_6_4_1;
extern Size collision_7_2_1;
extern Size collision_8_4_1;
extern Size collision_8_20_1;
extern Size collision_14_6_1;
extern Size collision_16_2_1;
extern Size collision_20_2_1;
extern Size collision_32_4_1;
extern Size collision_48_2_1;
extern Size collision_48_4_1;
extern Size collision_48_28_1;


//---------------------------------------------------------------------------------------------------------
//												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_1_TOWER_HEIGHT 	1024
#define SCREEN_Y_POSITION 		LEVEL_1_TOWER_HEIGHT - __SCREEN_HEIGHT


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LAVA_CHILD_ENTITIES[] =
{
	{&LAVA_TOP_AG, 					{__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(-102), 	__F_TO_FIX19_13(-1)}, 0, NULL, NULL, NULL, false},
	{&DARKNESS_OVERLAY_IM, 			{__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(-428), 	__F_TO_FIX19_13(-2)}, 0, NULL, NULL, NULL, false},
	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_1_ENTITIES[] =
{
	{&LEVEL_1_TOWER_MAIN_1_IM,		{__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(-1)}, 0, "Main_1", NULL, NULL, false},
	{&KEY_DOOR_AG,					{__F_TO_FIX19_13(-144), __F_TO_FIX19_13(159), 	__F_TO_FIX19_13(0)}, 0, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_TOWER_EP, false},
	{&TORCH_LIGHT_AG,				{__F_TO_FIX19_13(-107), __F_TO_FIX19_13(136), 	__F_TO_FIX19_13(-SORT_INCREMENT)}, 0, NULL, NULL, NULL, false},
	{&TORCH_AG,						{__F_TO_FIX19_13(-107), __F_TO_FIX19_13(136), 	__F_TO_FIX19_13(SORT_INCREMENT)}, 0, NULL, NULL, NULL, false},
//	{&TORCH_LIGHT_AG,				{__F_TO_FIX19_13(12), 	__F_TO_FIX19_13(136), 	__F_TO_FIX19_13(-SORT_INCREMENT)}, 0, NULL, NULL, NULL, false},
	{&TORCH_OFF_IM,					{__F_TO_FIX19_13(12), 	__F_TO_FIX19_13(140), 	__F_TO_FIX19_13(SORT_INCREMENT)}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_1_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(-184), __F_TO_FIX19_13(0), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_2_64_1, false}, // outer left wall
	{&COLLISION_CL,					{__F_TO_FIX19_13(184),	__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_2_64_1, false}, // outer right wall
	{&COLLISION_CL,					{__F_TO_FIX19_13(-128), __F_TO_FIX19_13(288), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_28_1, false}, // bottom left floor
	{&COLLISION_CL,					{__F_TO_FIX19_13(302),	__F_TO_FIX19_13(256), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_28_1, false}, // bottom right floor
	{&COLLISION_CL,					{__F_TO_FIX19_13(160),	__F_TO_FIX19_13(144), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_8_1, false}, // step stone bottom right
	{&COLLISION_CL,					{__F_TO_FIX19_13(80),	__F_TO_FIX19_13(72), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_2_1, false}, // floating stone

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_1_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(-172), __F_TO_FIX19_13(32), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_4_1, false}, // 2nd level floor left
	{&COLLISION_CL,					{__F_TO_FIX19_13(32),	__F_TO_FIX19_13(-96),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_32_4_1, false}, // 3rd level floor right
	{&COLLISION_CL,					{__F_TO_FIX19_13(160),	__F_TO_FIX19_13(-40), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_16_2_1, false}, // small stone right under 3rd
	{&COLLISION_CL,					{__F_TO_FIX19_13(-80),	__F_TO_FIX19_13(-176),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_4_1, false}, // 4th level floor left
	{&COLLISION_CL,					{__F_TO_FIX19_13(-82),	__F_TO_FIX19_13(-248),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_2_1, false}, // floor below spikes
	{&COLLISION_CL,					{__F_TO_FIX19_13(-136), __F_TO_FIX19_13(-216),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_14_6_1, false}, // left wall below spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(-184), __F_TO_FIX19_13(0), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_2_64_1, false}, // outer left wall
	{&COLLISION_CL,					{__F_TO_FIX19_13(184),	__F_TO_FIX19_13(0), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_2_64_1, false}, // outer right wall
	{&COLLISION_CL,					{__F_TO_FIX19_13(-104), __F_TO_FIX19_13(256), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_6_4_1, false}, // block between spikes left
	{&COLLISION_CL,					{__F_TO_FIX19_13(-16),	__F_TO_FIX19_13(256), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_4_1, false}, // block between spikes middle
	{&COLLISION_CL,					{__F_TO_FIX19_13(78),	__F_TO_FIX19_13(256), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_8_4_1, false}, // block between spikes right
	{&COLLISION_HIT_CL,				{__F_TO_FIX19_13(-104), __F_TO_FIX19_13(256),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_20_2_1, false}, // spikes
	{&COLLISION_HIT_CL,				{__F_TO_FIX19_13(-16),	__F_TO_FIX19_13(256),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_20_2_1, false}, // spikes

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(-176), __F_TO_FIX19_13(200), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_2_1, false}, // stepstone left
	{&COLLISION_CL,					{__F_TO_FIX19_13(-96),	__F_TO_FIX19_13(168), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_2_1, false}, // floating stone 1
	{&COLLISION_CL,					{__F_TO_FIX19_13(-16),	__F_TO_FIX19_13(136),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_2_1, false}, // floating stone 2
	{&COLLISION_CL,					{__F_TO_FIX19_13(64),	__F_TO_FIX19_13(104), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_2_1, false}, // floating stone 3
	{&COLLISION_CL,					{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(72), 	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_16_2_1, false}, // stepstone right
	{&COLLISION_CL,					{__F_TO_FIX19_13(-80),	__F_TO_FIX19_13(-16),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_4_1, false}, // floor above floating platforms

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_2_COLLISIONS_3[] =
{
	{&COLLISION_TOP_CL,				{__F_TO_FIX19_13(-80),	__F_TO_FIX19_13(-152),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_7_2_1, false}, // top room one way
	{&COLLISION_CL,					{__F_TO_FIX19_13(144),	__F_TO_FIX19_13(-144),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_4_1, false}, // top room right floor
	{&COLLISION_CL,					{__F_TO_FIX19_13(-144), __F_TO_FIX19_13(-80),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_8_20_1, false}, // top room left floor
	{&COLLISION_CL,					{__F_TO_FIX19_13(0),	__F_TO_FIX19_13(-232),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_48_2_1, false}, // top room ceiling
	{&COLLISION_CL,					{__F_TO_FIX19_13(80),	__F_TO_FIX19_13(-192),	__F_TO_FIX19_13(0)}, 0, NULL, NULL, (void*)&collision_4_8_1, false}, // top room right wall

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_TOWER_STAGE_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&LEVEL_1_TOWER_MAIN_BACK_IM,	{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT), 			__F_TO_FIX19_13(LAYER_0)}, 0, "BkgImg", NULL, NULL, true},

	{&HERO_AC, 						{__F_TO_FIX19_13(72), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 128), 	__F_TO_FIX19_13(LAYER_0)}, 0, HERO_NAME, NULL, NULL, false},
	{&LAVA_IG,						{__F_TO_FIX19_13(190), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT + 64), 	__F_TO_FIX19_13(LAYER_0)}, 0, "Lava", (struct PositionedEntity*)LAVA_CHILD_ENTITIES, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// part 1
	{&MANAGED_ENTITY,				{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 256),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_ENTITIES, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 257),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 257),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_2, NULL, false},
	{&TORCH_SMOKE_PS,				{__F_TO_FIX19_13(204),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 126), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND + 8)},	0, NULL, NULL, NULL, false},

	{&LAVA_TRIGGER_IG,				{__F_TO_FIX19_13(174),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 130), 	__F_TO_FIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false},
	{&COG_WHEEL_IM,					{__F_TO_FIX19_13(296),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 40), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, NULL, NULL, false},

	{&COIN_AG, 						{__F_TO_FIX19_13(132),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 48, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(148),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 49, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(164), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 50, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(180), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 51, NULL, NULL, NULL, false},

	{&GRASS_AG, 					{__F_TO_FIX19_13(324), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 121), 	__F_TO_FIX19_13(LAYER_0_BACKGROUND)}, 0, NULL, NULL, NULL, false},

	{&COIN_AG, 						{__F_TO_FIX19_13(264), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 204), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 52, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(280), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 204), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 53, NULL, NULL, NULL, false},

	{&SNAIL_8_AC, 					{__F_TO_FIX19_13(132),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 248), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{__F_TO_FIX19_13(60),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 296), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false},

	{&BANDANA_AG, 					{__F_TO_FIX19_13(296), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 317), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 3, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(312),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 317), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 54, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(328),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 317), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 55, NULL, NULL, NULL, false},

	{&SAW_BLADE_H8_AC, 				{__F_TO_FIX19_13(200),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 370), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 0, NULL, NULL, NULL, false},
	{&SAW_BLADE_H8_AC, 				{__F_TO_FIX19_13(224),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 450), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 0, NULL, NULL, NULL, false},

	{&COIN_AG, 						{__F_TO_FIX19_13(120),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 464), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 56, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(136),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 464), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 57, NULL, NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{__F_TO_FIX19_13(336),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 424), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false},

	// part 2
	{&LEVEL_1_TOWER_MAIN_2_IM,		{__F_TO_FIX19_13(192), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 768), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, "Main_2", NULL, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 769),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 769),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_2, NULL, false},

	{&COIN_AG, 						{__F_TO_FIX19_13(88),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 623), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 58, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(104), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 623), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 59, NULL, NULL, NULL, false},

	{&COIN_AG, 						{__F_TO_FIX19_13(168),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 655), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 60, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(184), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 655), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 61, NULL, NULL, NULL, false},

	{&COIN_AG, 						{__F_TO_FIX19_13(248),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 687), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 62, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(264), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 687), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 63, NULL, NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{__F_TO_FIX19_13(336),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 760),	__F_TO_FIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false},

	{&SNAIL_8_AC, 					{__F_TO_FIX19_13(210),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 808), 	__F_TO_FIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{__F_TO_FIX19_13(112),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 852),	__F_TO_FIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false},
	{&COIN_AG, 						{__F_TO_FIX19_13(40), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 942), 	__F_TO_FIX19_13(LAYER_0_ITEMS)}, 64, NULL, NULL, NULL, false},
	{&GOAL_DOOR_AG, 				{__F_TO_FIX19_13(208), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 944), 	__F_TO_FIX19_13(LAYER_0_DOORS)}, 0, "GoalDoor", NULL, NULL, false},
	{&TORCH_OFF_IM,					{__F_TO_FIX19_13(176), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 948), 	__F_TO_FIX19_13(LAYER_0)}, 			0, NULL, NULL, NULL, false},
	{&TORCH_SMOKE_PS,				{__F_TO_FIX19_13(176), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 958), 	__F_TO_FIX19_13(LAYER_0_FOREGROUND + 8)},	0, NULL, NULL, NULL, false},
	{&TORCH_OFF_IM,					{__F_TO_FIX19_13(240), 	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 948), 	__F_TO_FIX19_13(LAYER_0)}, 			0, NULL, NULL, NULL, false},

	{&MANAGED_ENTITY,	{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(LEVEL_1_TOWER_HEIGHT - 769),	__F_TO_FIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_3, NULL, false},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_STAGE_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {__F_TO_FIX19_13(192), __F_TO_FIX19_13(215), __F_TO_FIX19_13(-4)}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL_1_TOWER_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMDef* const LEVEL_1_TOWER_STAGE_ST_CHARSETS[] =
{
	NULL
};

TextureDefinition* const LEVEL_1_TOWER_STAGE_ST_TEXTURES[] =
{
	&COG_WHEEL_TX,
	&LEVEL_1_TOWER_BACK_1_TX,
	&LEVEL_1_TOWER_MAIN_BACK_1_TX,
	&LEVEL_1_TOWER_MAIN_BACK_1_TX,
	&LEVEL_1_TOWER_MAIN_1_TX,
	&LEVEL_1_TOWER_MAIN_1_TX,
	&DOOR_TX,
	&GUI_TX,
	&LAVA_TX,
	&LAVA_TOP_TX,
	&DARKNESS_OVERLAY_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_TOWER_STAGE_ST =
{
	// level
	{
		// size
		{
			// x
			__SCREEN_WIDTH,
			// y
			LEVEL_1_TOWER_HEIGHT,
			// z
			__SCREEN_DEPTH,
		},

		// screen's initial position inside the game world
		{
			// x
			__I_TO_FIX19_13(0),
			// y
			__I_TO_FIX19_13(SCREEN_Y_POSITION - __SCREEN_HEIGHT / 2),
			// z
			__I_TO_FIX19_13(0)
		},
	},

	// streaming
	{
		// load padding
		80,
		// unload padding
		32,
		// streaming amplitude
		28,
		// particle removal delay cycles
		0,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		__TARGET_FPS / 10,

		// maximum number of texture's rows to write each time the texture writing is active
		32,

		// maximum number of rows to compute on each call to the affine functions
		24,

		// colors config
		{
			// background color
			__COLOR_BLACK,

			// brightness
			// these values times the repeat values specified in the column table (max. 16) make the final
			// brightness values on the respective regions of the screen. maximum brightness is 128.
			{
				// dark red
				2,
				// medium red
				4,
				// bright red
				8,
			},

			// brightness repeat
			(BrightnessRepeatDefinition*)&EDGE_FADE_OUT_BRIGHTNESS_REPEAT,
		},

		// palettes' config
		{
			{
				// bgmap palette 0
				__BGMAP_PALETTE_0,
				// bgmap palette 1
				__BGMAP_PALETTE_1,
				// bgmap palette 2
				__BGMAP_PALETTE_2,
				// bgmap palette 3
				__BGMAP_PALETTE_3,
			},
			{
				// object palette 0
				__OBJECT_PALETTE_0,
				// object palette 1
				__OBJECT_PALETTE_1,
				// object palette 2
				__OBJECT_PALETTE_2,
				// object palette 3
				__OBJECT_PALETTE_3,
			},
		},

		// bgmap segments configuration
		// number of segments reserved for the param table
		4,

		// obj segments sizes (must total 1024)
		{
			// __spt0
			0,
			// __spt1
			0,
			// __spt2
			0,
			// __spt3
			80,
		},

		// OBJECT segments z coordinates
		// Note that each SPT's z coordinate must be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			__F_TO_FIX19_13(LAYER_0_PARTICLES),
			// __spt1
			__F_TO_FIX19_13(LAYER_0_PARTICLES),
			// __spt2
			__F_TO_FIX19_13(LAYER_0_PARTICLES),
			// __spt3
			__F_TO_FIX19_13(LAYER_0_PARTICLES),
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			__I_TO_FIX19_13(__DISTANCE_EYE_SCREEN),
			// distance from left to right eye (depth sensation)
			__I_TO_FIX19_13(__BASE_FACTOR),
			// horizontal View point center
			__I_TO_FIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
			// vertical View point center
			__I_TO_FIX19_13(__VERTICAL_VIEW_POINT_CENTER),
		},
	},

	// physics
	{
		// gravity
		{
			__I_TO_FIX19_13(0),
			__I_TO_FIX19_13(__GRAVITY),
			__I_TO_FIX19_13(0)
		},

		// friction
		__F_TO_FIX19_13(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)LEVEL_1_TOWER_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)LEVEL_1_TOWER_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureDefinition**)LEVEL_1_TOWER_STAGE_ST_TEXTURES,

		// background music
		(const u16 (*)[])KRISSE_BGM,
	},

	// entities
	{
		// ui
		{
			LEVEL_1_TOWER_STAGE_ST_UI_CHILDREN,
			__TYPE(UiContainer),
		},

		// children
		LEVEL_1_TOWER_STAGE_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL1_TOWER_STAGE_MAIN_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL_1_TOWER_STAGE_ST,

	// name of the entity to start at
	"EntryDoor",

	// offset from entry point (x, y, z)
	{__F_TO_FIX19_13(19), __F_TO_FIX19_13(-10), __F_TO_FIX19_13(-SORT_INCREMENT)},

	// whether this entry point acts as a checkpoint
	true,
};
