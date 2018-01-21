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
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

const PixelSize level1_coin_room_stage_collision_16_96_8 = {16, 96, 8};
const PixelSize level1_coin_room_stage_collision_224_16_8 = {224, 16, 8};
const PixelSize level1_coin_room_stage_collision_320_16_8 = {320, 16, 8};
const PixelSize level1_coin_room_stage_collision_32_48_8 = {32, 48, 8};
const PixelSize level1_coin_room_stage_collision_80_48_8 = {80, 48, 8};
extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern EntityDefinition COIN_AG;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition DOOR_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition LEVEL1_COIN_ROOM_STAGE_BACK_1_IM;
extern EntityDefinition LEVEL1_COIN_ROOM_STAGE_MAIN_1_IM;
extern EntityDefinition LEVEL1_COIN_ROOM_STAGE_MAIN_BACK_1_IM;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition TORCH_AG;
extern EntityDefinition TORCH_LIGHT_AG;
extern StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_LOWER_EP;
extern StageEntryPointROMDef LEVEL_1_MAIN_COIN_ROOM_ENTRY_DOOR_EP;
extern u16 KRISSE_BGM[][2];


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL1_COIN_ROOM_STAGE_ST_ENTITIES[] =
{
	{&COLLISION_CL, {(8), (112), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_16_96_8, false}, // Left Collision
	{&COLLISION_CL, {(16), (40), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_32_48_8, false}, // Top Left Collision
	{&DOOR_AG, {(36), (144), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "CoinEntr", NULL, (void*)&LEVEL_1_MAIN_COIN_ROOM_ENTRY_DOOR_EP, false}, // Door (Entrance)
	{&COLLISION_CL, {(40), (184), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_80_48_8, false}, // Bottom Left Collision
	{&HERO_AC, {(62), (148), (LAYER_0), 0}, 0, HERO_NAME, NULL, NULL, false}, // Hero
	{&TORCH_LIGHT_AG, {(64), (128), (0), 0}, 0, NULL, NULL, NULL, false}, // Left Torch Light
	{&TORCH_AG, {(64), (126), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Left Torch
	{&COIN_AG, {(144), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 27, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(144), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 28, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(144), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 30, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(144), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 29, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(160), (168), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 31, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(176), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 35, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(176), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 34, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(176), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 33, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(176), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 32, NULL, NULL, NULL, false}, // Coin
	{&LEVEL1_COIN_ROOM_STAGE_MAIN_BACK_1_IM, {(192), (112), (-SORT_INCREMENT), 0}, 0, NULL, NULL, NULL, false}, // MainBack
	{&COLLISION_CL, {(192), (24), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_320_16_8, false}, // Top Collision
	{&COLLISION_CL, {(192), (200), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_224_16_8, false}, // Bottom Collision
	{&LEVEL1_COIN_ROOM_STAGE_BACK_1_IM, {(192), (112), LAYER_0_BACKGROUND, LAYER_0_BACKGROUND_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Back
	{&SAW_BLADE_H8_AC, {(192), (192), LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false}, // Saw Blade
	{&LEVEL1_COIN_ROOM_STAGE_MAIN_1_IM, {(192), (112), (-SORT_INCREMENT * 2), 0}, 0, NULL, NULL, NULL, false}, // Main
	{&COIN_AG, {(208), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 39, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(208), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 36, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(208), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 37, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(208), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 38, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(208), (168), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 40, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(224), (136), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 42, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(224), (104), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 41, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(224), (168), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 43, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(240), (120), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 44, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(240), (152), LAYER_0_ITEMS, LAYER_0_ITEMS_DISPLACEMENT}, 45, NULL, NULL, NULL, false}, // Coin
	{&TORCH_AG, {(320), (128), LAYER_0_BACKGROUND, 0}, 0, NULL, NULL, NULL, false}, // Right Torch
	{&TORCH_LIGHT_AG, {(320), (130), (0), 0}, 0, NULL, NULL, NULL, false}, // Right Torch Light
	{&COLLISION_CL, {(344), (184), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_80_48_8, false}, // Bottom Right Collision
	{&DOOR_AG, {(348), (144), LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 0, "CoinExit", NULL, (void*)&LEVEL1_INTERSECTION_STAGE_LOWER_EP, false}, // Door (Exit)
	{&COLLISION_CL, {(368), (40), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_32_48_8, false}, // Top Right Collision
	{&COLLISION_CL, {(376), (112), (0), 0}, 0, NULL, NULL, (void*)&level1_coin_room_stage_collision_16_96_8, false}, // Right Collision

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL1_COIN_ROOM_STAGE_ST_UI_ENTITIES[] =
{
	{&GUI_AG, {(192), (216), (0), 0}, 0, NULL, NULL, NULL, false}, // GUI

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL1_COIN_ROOM_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL1_COIN_ROOM_STAGE_ST =
{
	// level
	{
		// size
		{
			// x
			__SCREEN_WIDTH,
			// y
			__SCREEN_HEIGHT,
			// z
			__SCREEN_DEPTH + LAYER_5,
		},

		// camera's initial position inside the game world
		{
			// x
			0,
			// y
			0,
			// z
			0,
			// p
			0
		},
	},

	// streaming
	{
		// load padding
		40,
		// unload padding
		16,
		// streaming amplitude
		24,
		// particle removal delay cycles
		0,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		__TARGET_FPS / 10,

		// maximum number of texture's rows to write each time the texture writing is active
		12,

		// maximum number of rows to compute on each call to the affine functions
		16,

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
		1,

		// obj segments sizes (must total 1024)
		{
			// __spt0
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt1
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt2
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
			// __spt3
			__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
		},

		// OBJECT segments z coordinates
		// note that each spt's z coordinate much be larger than or equal to the previous one's,
		// since the vip renders obj worlds in reverse order (__spt3 to __spt0)
		{
			// __spt0
			LAYER_0_PARTICLES,
			// __spt1
			LAYER_0_PARTICLES,
			// __spt2
			LAYER_0_PARTICLES,
			// __spt3
			LAYER_0_PARTICLES,
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE_POWER, __MAXIMUM_Y_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			__DISTANCE_EYE_SCREEN,
			// distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// horizontal view point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical view point center
			__VERTICAL_VIEW_POINT_CENTER,
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
		(FontDefinition**)LEVEL1_COIN_ROOM_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)NULL,

		// textures to preload
		(TextureDefinition**)NULL,

		// background music
		(const u16 (*)[])KRISSE_BGM,
	},

	// entities
	{
		// ui
		{
			LEVEL1_COIN_ROOM_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		LEVEL1_COIN_ROOM_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL1_COIN_ROOM_STAGE_EXIT_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL1_COIN_ROOM_STAGE_ST,

	// name of the entity to start at
	"CoinExit",

	// offset from entry point (x, y, z)
	{
		-21,
		-0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

StageEntryPointROMDef LEVEL1_COIN_ROOM_STAGE_MAIN_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL1_COIN_ROOM_STAGE_ST,

	// name of the entity to start at
	"CoinEntr",

	// offset from entry point (x, y, z)
	{
		19,
		-0,
		(LAYER_0_FOREGROUND - LAYER_0_DOORS),
		LAYER_0_HERO_DISPLACEMENT
	},

	// whether this entry point acts as a checkpoint
	false,
};

