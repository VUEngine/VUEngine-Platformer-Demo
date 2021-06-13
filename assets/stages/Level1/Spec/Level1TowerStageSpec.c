/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

extern SoundROM* const LEVEL_1_SOUNDS[];

extern StageEntryPointROMSpec LEVEL_1_MAIN_TOWER_EP;
extern BrightnessRepeatROMSpec EDGE_FADE_OUT_BRIGHTNESS_REPEAT;

extern EntitySpec BANDANA_AG;
extern EntitySpec COIN_AG;
extern EntitySpec COG_WHEEL_IM;
extern EntitySpec COLLISION_CL;
extern EntitySpec COLLISION_HIT_CL;
extern EntitySpec COLLISION_TOP_CL;
extern EntitySpec MANAGED_ENTITY;
extern EntitySpec KEY_DOOR_AG;
extern EntitySpec GOAL_DOOR_AG;
extern EntitySpec GRASS_AG;
extern EntitySpec GUI_AG;
extern EntitySpec HERO_AC;
extern EntitySpec LAVA_IG;
extern EntitySpec LAVA_TOP_AG;
extern EntitySpec LAVA_TRIGGER_IG;
extern EntitySpec LEVEL_1_TOWER_MAIN_1_IM;
extern EntitySpec LEVEL_1_TOWER_MAIN_2_IM;
extern EntitySpec LEVEL_1_TOWER_MAIN_BACK_IM;
extern EntitySpec LOW_POWER_INDICATOR_LB;
extern EntitySpec MANAGED_ENTITY;
extern EntitySpec MOVING_PLATFORM_V6_AC;
extern EntitySpec SAW_BLADE_H8_AC;
extern EntitySpec SNAIL_8_AC;
extern EntitySpec TORCH_AG;
extern EntitySpec TORCH_OFF_IM;
extern EntitySpec TORCH_LIGHT_AG;
extern EntitySpec DARKNESS_OVERLAY_IM;
extern EntitySpec TORCH_SMOKE_PS;

extern TextureSpec COG_WHEEL_TX;
extern TextureSpec DOOR_TX;
extern TextureSpec GUI_TX;
extern TextureSpec LAVA_TOP_TX;
extern TextureSpec LAVA_TX;
extern TextureSpec LEVEL_1_TOWER_BACK_1_TX;
extern TextureSpec LEVEL_1_TOWER_MAIN_1_TX;
extern TextureSpec LEVEL_1_TOWER_MAIN_BACK_1_TX;
extern TextureSpec DARKNESS_OVERLAY_TX;

extern Size collision_2_64_4;
extern Size collision_4_2_4;
extern Size collision_4_4_4;
extern Size collision_4_8_4;
extern Size collision_6_4_4;
extern Size collision_6_2_4;
extern Size collision_8_4_4;
extern Size collision_8_20_4;
extern Size collision_14_6_4;
extern Size collision_16_2_4;
extern Size collision_20_2_4;
extern Size collision_32_4_4;
extern Size collision_48_2_4;
extern Size collision_48_4_4;
extern Size collision_48_28_4;


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

PositionedEntityROMSpec LAVA_CHILD_ENTITIES[] =
{
	{&LAVA_TOP_AG, 					{0, -104, -1, 0}, 0, NULL, NULL, NULL, false},
	{&DARKNESS_OVERLAY_IM, 			{0, -460, -4, 0}, 0, NULL, NULL, NULL, false},
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_TOWER_MAIN_1_ENTITIES[] =
{
	{&LEVEL_1_TOWER_MAIN_1_IM,		{   0, 	  0, 	0, -SORT_INCREMENT}, 0, "Main_1", NULL, NULL, false},
	{&TORCH_LIGHT_AG,				{-107, 	136, 	-SORT_INCREMENT, 0}, 0, NULL, NULL, NULL, false},
	{&TORCH_AG,						{-107, 	136, 	LAYER_0_DECORATIONS - LAYER_0_FOREGROUND, LAYER_0_DECORATIONS_DISPLACEMENT - LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
//	{&TORCH_LIGHT_AG,				{  12, 	136, 	-SORT_INCREMENT, 0}, 0, NULL, NULL, NULL, false},
	{&TORCH_OFF_IM,					{  12, 	140, 	LAYER_0_DECORATIONS - LAYER_0_FOREGROUND, LAYER_0_DECORATIONS_DISPLACEMENT - LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_TOWER_MAIN_1_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{-185,	  0, 	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer left wall
	{&COLLISION_CL,					{ 183,	  0, 	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer right wall
	{&COLLISION_CL,					{-129,	288, 	0, 0}, 0, NULL, NULL, (void*)&collision_48_28_4, false}, // bottom left floor
	{&COLLISION_CL,					{ 301,	256, 	0, 0}, 0, NULL, NULL, (void*)&collision_48_28_4, false}, // bottom right floor
	{&COLLISION_CL,					{ 159,	144, 	0, 0}, 0, NULL, NULL, (void*)&collision_4_8_4, false}, // step stone bottom right
	{&COLLISION_CL,					{  79,	 72, 	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_TOWER_MAIN_1_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{-173, 	  32,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // 2nd level floor left
	{&COLLISION_CL,					{  29,	 -96,	0, 0}, 0, NULL, NULL, (void*)&collision_32_4_4, false}, // 3rd level floor right
	{&COLLISION_CL,					{ 159,	 -40,	0, 0}, 0, NULL, NULL, (void*)&collision_16_2_4, false}, // small stone right under 3rd
	{&COLLISION_CL,					{ -81,	-176,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // 4th level floor left
	{&COLLISION_CL,					{ -83,	-248,	0, 0}, 0, NULL, NULL, (void*)&collision_48_2_4, false}, // floor below spikes
	{&COLLISION_CL,					{-137, 	-216,	0, 0}, 0, NULL, NULL, (void*)&collision_14_6_4, false}, // left wall below spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_TOWER_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_CL,					{-185, 	  0,	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer left wall
	{&COLLISION_CL,					{ 183,	  0,	0, 0}, 0, NULL, NULL, (void*)&collision_2_64_4, false}, // outer right wall
	{&COLLISION_CL,					{-105,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_6_4_4, false}, // block between spikes left
	{&COLLISION_CL,					{ -17,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_4_4_4, false}, // block between spikes middle
	{&COLLISION_CL,					{  77,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_8_4_4, false}, // block between spikes right
	{&COLLISION_HIT_CL,				{-105,  256,	0, 0}, 0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes
	{&COLLISION_HIT_CL,				{ -17,	256,	0, 0}, 0, NULL, NULL, (void*)&collision_20_2_4, false}, // spikes

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_TOWER_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_CL,					{-177,	200,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // stepstone left
	{&COLLISION_CL,					{ -97,	168,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone 1
	{&COLLISION_CL,					{ -17,	136,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone 2
	{&COLLISION_CL,					{  63,	104,	0, 0}, 0, NULL, NULL, (void*)&collision_4_2_4, false}, // floating stone 3
	{&COLLISION_CL,					{ 191,	 72,	0, 0}, 0, NULL, NULL, (void*)&collision_16_2_4, false}, // stepstone right
	{&COLLISION_CL,					{ -81,	-16,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // floor above floating platforms

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_TOWER_MAIN_2_COLLISIONS_3[] =
{
	{&COLLISION_TOP_CL,				{ -81,	-152,	0, 0}, 0, NULL, NULL, (void*)&collision_6_2_4, false}, // top room one way
	{&COLLISION_CL,					{ 143,	-144,	0, 0}, 0, NULL, NULL, (void*)&collision_48_4_4, false}, // top room right floor
	{&COLLISION_CL,					{-145,   -80,	0, 0}, 0, NULL, NULL, (void*)&collision_8_20_4, false}, // top room left floor
	{&COLLISION_CL,					{  -1,	-232,	0, 0}, 0, NULL, NULL, (void*)&collision_48_2_4, false}, // top room ceiling
	{&COLLISION_CL,					{  79,	-192,	0, 0}, 0, NULL, NULL, (void*)&collision_4_8_4, false}, // top room right wall

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec LEVEL_1_TOWER_STAGE_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this spec
	{&LEVEL_1_TOWER_MAIN_BACK_IM,	{192,	LEVEL_1_TOWER_HEIGHT, 32, LAYER_0_BACKGROUND_DISPLACEMENT + 1}, 0, "BkgImg", NULL, NULL, true},
	{&LAVA_IG,						{190,	LEVEL_1_TOWER_HEIGHT + 64, 	LAYER_0, 0}, 0, "Lava", (struct PositionedEntity*)LAVA_CHILD_ENTITIES, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

	// part 1
	{&KEY_DOOR_AG,					{48, 	LEVEL_1_TOWER_HEIGHT - 96, 		LAYER_0_DOORS - LAYER_0_FOREGROUND, LAYER_0_DOORS_DISPLACEMENT - LAYER_0_FOREGROUND_DISPLACEMENT}, 0, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_TOWER_EP, false},
	{&MANAGED_ENTITY,				{192,	LEVEL_1_TOWER_HEIGHT - 256,		LAYER_0_FOREGROUND, 0}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_ENTITIES, NULL, false},
	{&MANAGED_ENTITY,				{192,	LEVEL_1_TOWER_HEIGHT - 257,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{192,	LEVEL_1_TOWER_HEIGHT - 257,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_2, NULL, false},
	{&TORCH_SMOKE_PS,				{204,	LEVEL_1_TOWER_HEIGHT - 126, 	LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},

	{&LAVA_TRIGGER_IG,				{174,	LEVEL_1_TOWER_HEIGHT - 130, 	LAYER_0, 0}, 0, NULL, NULL, NULL, false},
	{&COG_WHEEL_IM,					{310,	LEVEL_1_TOWER_HEIGHT - 40, 		LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT + 1}, 0, NULL, NULL, NULL, false},

	{&COIN_AG, 						{132,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "48", NULL, NULL, false},
	{&COIN_AG, 						{148,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "49", NULL, NULL, false},
	{&COIN_AG, 						{164,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "50", NULL, NULL, false},
	{&COIN_AG, 						{180,	LEVEL_1_TOWER_HEIGHT - 92, 		LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "51", NULL, NULL, false},

	{&GRASS_AG, 					{324,	LEVEL_1_TOWER_HEIGHT - 121, 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&COIN_AG, 						{264,	LEVEL_1_TOWER_HEIGHT - 204, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "52", NULL, NULL, false},
	{&COIN_AG, 						{280,	LEVEL_1_TOWER_HEIGHT - 204, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "53", NULL, NULL, false},

	{&SNAIL_8_AC, 					{132,	LEVEL_1_TOWER_HEIGHT - 248, 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{60,	LEVEL_1_TOWER_HEIGHT - 300, 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&BANDANA_AG, 					{296,	LEVEL_1_TOWER_HEIGHT - 317, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "3", NULL, NULL, false},
	{&COIN_AG, 						{312,	LEVEL_1_TOWER_HEIGHT - 317, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "54", NULL, NULL, false},
	{&COIN_AG, 						{328,	LEVEL_1_TOWER_HEIGHT - 317, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "55", NULL, NULL, false},

	{&SAW_BLADE_H8_AC, 				{200,	LEVEL_1_TOWER_HEIGHT - 370, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
	{&SAW_BLADE_H8_AC, 				{224,	LEVEL_1_TOWER_HEIGHT - 450, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&COIN_AG, 						{120,	LEVEL_1_TOWER_HEIGHT - 464, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "56", NULL, NULL, false},
	{&COIN_AG, 						{136,	LEVEL_1_TOWER_HEIGHT - 464, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "57", NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{336,	LEVEL_1_TOWER_HEIGHT - 424, 	LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	// part 2
	{&LEVEL_1_TOWER_MAIN_2_IM,		{192,	LEVEL_1_TOWER_HEIGHT - 768, 	LAYER_0_FOREGROUND, 0}, 0, "Main_2", NULL, NULL, false},
	{&MANAGED_ENTITY,				{192,	LEVEL_1_TOWER_HEIGHT - 769,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_1, NULL, false},
	{&MANAGED_ENTITY,				{192,	LEVEL_1_TOWER_HEIGHT - 769,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_2, NULL, false},

	{&COIN_AG, 						{88,	LEVEL_1_TOWER_HEIGHT - 623, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "58", NULL, NULL, false},
	{&COIN_AG, 						{104,	LEVEL_1_TOWER_HEIGHT - 623, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "59", NULL, NULL, false},

	{&COIN_AG, 						{168,	LEVEL_1_TOWER_HEIGHT - 655, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "60", NULL, NULL, false},
	{&COIN_AG, 						{184,	LEVEL_1_TOWER_HEIGHT - 655, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "61", NULL, NULL, false},

	{&COIN_AG, 						{248,	LEVEL_1_TOWER_HEIGHT - 687, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "62", NULL, NULL, false},
	{&COIN_AG, 						{264,	LEVEL_1_TOWER_HEIGHT - 687, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "63", NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{336,	LEVEL_1_TOWER_HEIGHT - 760,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&SNAIL_8_AC, 					{210,	LEVEL_1_TOWER_HEIGHT - 808, 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&MOVING_PLATFORM_V6_AC,		{112,	LEVEL_1_TOWER_HEIGHT - 852,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
	{&COIN_AG, 						{40, 	LEVEL_1_TOWER_HEIGHT - 942, 	LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 0, "64", NULL, NULL, false},
	{&GOAL_DOOR_AG, 				{208,	LEVEL_1_TOWER_HEIGHT - 944, 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "GoalDoor", NULL, NULL, false},
	{&TORCH_OFF_IM,					{176,	LEVEL_1_TOWER_HEIGHT - 948, 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
	{&TORCH_SMOKE_PS,				{176,	LEVEL_1_TOWER_HEIGHT - 958, 	LAYER_0_FOREGROUND + 12, LAYER_0_FOREGROUND_DISPLACEMENT},	0, NULL, NULL, NULL, false},
	{&TORCH_OFF_IM,					{240,	LEVEL_1_TOWER_HEIGHT - 948, 	LAYER_0_DECORATIONS, LAYER_0_DECORATIONS_DISPLACEMENT}, 0, NULL, NULL, NULL, false},

	{&MANAGED_ENTITY,				{192,	LEVEL_1_TOWER_HEIGHT - 769,		LAYER_0_FOREGROUND, LAYER_0_FOREGROUND_DISPLACEMENT}, 0, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_3, NULL, false},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec LEVEL_1_TOWER_STAGE_ST_UI_CHILDREN[] =
{
	{&LOW_POWER_INDICATOR_LB, 	{INGAME_LOW_POWER_ENTITY_X_POSITION, INGAME_LOW_POWER_ENTITY_Y_POSITION, INGAME_LOW_POWER_ENTITY_Z_POSITION, INGAME_LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, true},
	{&GUI_AG, {192, 215, -2, 0}, 0, NULL, NULL, NULL, true},

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const LEVEL_1_TOWER_STAGE_ST_FONTS[] =
{
	&PLATFORMER_FONT,
	&ASTONISH_S_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMSpec* const LEVEL_1_TOWER_STAGE_ST_CHARSETS[] =
{
	NULL
};

TextureSpec* const LEVEL_1_TOWER_STAGE_ST_TEXTURES[] =
{
/*	&COG_WHEEL_TX,
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
*/
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec LEVEL_1_TOWER_STAGE_ST =
{
	// allocator
	__TYPE(Stage),

	// Timer config
	{
		__TIMER_100US,
		10,
		kMS
	},

	// Sound config
	{
		__DEFAULT_PCM_HZ,
		false	},

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

		// camera's initial position inside the game world
		{
			// x
			0,
			// y
			SCREEN_Y_POSITION - __SCREEN_HEIGHT / 2,
			// z
			0,
			// p
			0,
		},

		// camera's frustum
        {
        	// x0
        	INGAME_CAMERA_FRUSTUM_X0,
        	// y0
			INGAME_CAMERA_FRUSTUM_Y0,
			// z0
			INGAME_CAMERA_FRUSTUM_Z0,
        	// x1
        	INGAME_CAMERA_FRUSTUM_X1,
        	// y1
        	INGAME_CAMERA_FRUSTUM_Y1,
        	// z1
        	INGAME_CAMERA_FRUSTUM_Z1,
        }
	},

	// streaming
	{
		// load padding
		80,
		// unload padding
		32,
		// streaming amplitude
		48,
		// particle removal delay cycles
		4,
		// deferred
		false,
	},

	// rendering
	{
		// maximum number of texture's rows to write each time the texture writing is active
		64,

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
			(BrightnessRepeatSpec*)&EDGE_FADE_OUT_BRIGHTNESS_REPEAT,
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
		2,

		// object segments sizes (up to 1024 in total)
		// can impact performance, make sure to configure only as large as maximally needed
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

		// object segments z coordinates
		// Note that each SPT's z coordinate must be larger than or equal to the previous one's,
		// since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
		{
			// __spt0
			LAYER_0_PARTICLES,
			// __spt1
			LAYER_0_PARTICLES,
			// __spt2
			LAYER_0_PARTICLES,
			// __spt3
			15,
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE, __MAXIMUM_Y_VIEW_DISTANCE,
			// distance of the eyes to the screen
			__DISTANCE_EYE_SCREEN,
			// distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// horizontal View point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical View point center
			__VERTICAL_VIEW_POINT_CENTER,
			// scaling factor
			__SCALING_MODIFIER_FACTOR,
		},
	},

	// physics
	{
		// gravity
		{
			__I_TO_FIX10_6(0),
			__F_TO_FIX10_6(__GRAVITY),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)LEVEL_1_TOWER_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)LEVEL_1_TOWER_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureSpec**)LEVEL_1_TOWER_STAGE_ST_TEXTURES,

		// background sounds
		(Sound**)NULL,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)LEVEL_1_TOWER_STAGE_ST_UI_CHILDREN,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)LEVEL_1_TOWER_STAGE_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec LEVEL1_TOWER_STAGE_MAIN_EP =
{
	// the stage to load
	(StageSpec*)&LEVEL_1_TOWER_STAGE_ST,

	// name of the entity to start at
	"EntryDoor",

	// offset from entry point (x, y, z)
	{
		19,
		3,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	true,
};
