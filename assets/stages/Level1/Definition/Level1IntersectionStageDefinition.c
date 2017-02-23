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

const VBVec3D level1_intersection_stage_collision_112_128_8 = {112, 128, 8};
const VBVec3D level1_intersection_stage_collision_16_48_8 = {16, 48, 8};
const VBVec3D level1_intersection_stage_collision_224_16_8 = {224, 16, 8};
const VBVec3D level1_intersection_stage_collision_224_64_8 = {224, 64, 8};
const VBVec3D level1_intersection_stage_collision_272_16_8 = {272, 16, 8};
const VBVec3D level1_intersection_stage_collision_32_64_8 = {32, 64, 8};
const VBVec3D level1_intersection_stage_collision_48_32_8 = {48, 32, 8};
const VBVec3D level1_intersection_stage_collision_48_34_8 = {48, 34, 8};
extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern EntityDefinition COIN_AG;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition COLLISION_TOP_CL;
extern EntityDefinition DOOR_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition LEVEL1_INTERSECTION_STAGE_BACK_1_IM;
extern EntityDefinition LEVEL1_INTERSECTION_STAGE_MAIN_1_IM;
extern EntityDefinition LEVEL1_INTERSECTION_STAGE_MAIN_BACK_1_IM;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition TORCH_AG;
extern EntityDefinition TORCH_LIGHT_AG;
extern StageEntryPointROMDef LEVEL1_COIN_ROOM_STAGE_EXIT_EP;
extern StageEntryPointROMDef LEVEL_1_MAIN_INTERSECTION_ENTRY_DOOR_EP;
extern StageEntryPointROMDef LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP;
extern u16 KRISSE_BGM[][2];



//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL1_INTERSECTION_STAGE_ST_ENTITIES[] =
{
	{&COLLISION_CL, {FTOFIX19_13(8), FTOFIX19_13(152), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_16_48_8, false}, // Left Collision
	{&DOOR_AG, {FTOFIX19_13(36), FTOFIX19_13(160), FTOFIX19_13(LAYER_0_DOORS)}, 0, "IntEntr2", NULL, (void*)&LEVEL1_COIN_ROOM_STAGE_EXIT_EP, false}, // Door (Lower Entrance)
	{&TORCH_LIGHT_AG, {FTOFIX19_13(56), FTOFIX19_13(148), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Lower Left Torch Light
	{&TORCH_AG, {FTOFIX19_13(56), FTOFIX19_13(146), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Lower Left Torch
	{&HERO_AC, {FTOFIX19_13(56), FTOFIX19_13(164), FTOFIX19_13(LAYER_0)}, 0, HERO_NAME, NULL, NULL, false}, // Hero
	{&COLLISION_CL, {FTOFIX19_13(112), FTOFIX19_13(96), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_224_64_8, false}, // Center Collision
	{&COLLISION_CL, {FTOFIX19_13(136), FTOFIX19_13(184), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_272_16_8, false}, // Bottom Collision
	{&COLLISION_CL, {FTOFIX19_13(144), FTOFIX19_13(32), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_32_64_8, false}, // Top Left Collision
	{&SAW_BLADE_H8_AC, {FTOFIX19_13(162), FTOFIX19_13(176), FTOFIX19_13(LAYER_0_ENEMIES)}, 0, NULL, NULL, NULL, false}, // Cog Wheel
	{&DOOR_AG, {FTOFIX19_13(178), FTOFIX19_13(48), FTOFIX19_13(LAYER_0_DOORS)}, 0, "IntEntr1", NULL, (void*)&LEVEL_1_MAIN_INTERSECTION_ENTRY_DOOR_EP, false}, // Door (Upper Entrance)
	{&LEVEL1_INTERSECTION_STAGE_MAIN_BACK_1_IM, {FTOFIX19_13(192), FTOFIX19_13(96), FTOFIX19_13(-SORT_INCREMENT)}, 0, NULL, NULL, NULL, false}, // MainBack
	{&LEVEL1_INTERSECTION_STAGE_BACK_1_IM, {FTOFIX19_13(192), FTOFIX19_13(96), FTOFIX19_13(LAYER_0_BACKGROUND)}, 0, NULL, NULL, NULL, false}, // Back
	{&LEVEL1_INTERSECTION_STAGE_MAIN_1_IM, {FTOFIX19_13(192), FTOFIX19_13(96), FTOFIX19_13(-SORT_INCREMENT * 2)}, 0, NULL, NULL, NULL, false}, // Main
	{&TORCH_AG, {FTOFIX19_13(206), FTOFIX19_13(146), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Lower Right Torch
	{&TORCH_LIGHT_AG, {FTOFIX19_13(206), FTOFIX19_13(148), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Lower Right Torch Light
	{&TORCH_AG, {FTOFIX19_13(206), FTOFIX19_13(34), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Upper Left Torch
	{&TORCH_LIGHT_AG, {FTOFIX19_13(206), FTOFIX19_13(36), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Upper Left Torch Light
	{&COIN_AG, {FTOFIX19_13(236), FTOFIX19_13(108), FTOFIX19_13(LAYER_0_ITEMS)}, 47, NULL, NULL, NULL, false}, // Coin
	{&COLLISION_TOP_CL, {FTOFIX19_13(248), FTOFIX19_13(135), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_48_34_8, false}, // Lower One-Way
	{&COLLISION_TOP_CL, {FTOFIX19_13(248), FTOFIX19_13(80), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_48_32_8, false}, // Upper One-Way
	{&COIN_AG, {FTOFIX19_13(260), FTOFIX19_13(108), FTOFIX19_13(LAYER_0_ITEMS)}, 46, NULL, NULL, NULL, false}, // Coin
	{&COLLISION_CL, {FTOFIX19_13(272), FTOFIX19_13(8), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_224_16_8, false}, // Top Collision
	{&TORCH_AG, {FTOFIX19_13(320), FTOFIX19_13(34), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Upper Right Torch
	{&TORCH_LIGHT_AG, {FTOFIX19_13(320), FTOFIX19_13(36), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Upper Right Torch Light
	{&COLLISION_CL, {FTOFIX19_13(328), FTOFIX19_13(128), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_112_128_8, false}, // Bottom Right Collision
	{&DOOR_AG, {FTOFIX19_13(350), FTOFIX19_13(48), FTOFIX19_13(LAYER_0_DOORS)}, 0, "IntExit", NULL, (void*)&LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP, false}, // Door (Exit)
	{&COLLISION_CL, {FTOFIX19_13(376), FTOFIX19_13(40), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_intersection_stage_collision_16_48_8, false}, // Top Right Collision

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL1_INTERSECTION_STAGE_ST_UI_ENTITIES[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(216), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // GUI

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL1_INTERSECTION_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL1_INTERSECTION_STAGE_ST =
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
			__SCREEN_DEPTH,
		},

		// screen's initial position inside the game world
		{
			// x
			ITOFIX19_13(0),
			// y
			ITOFIX19_13(0),
			// z
			ITOFIX19_13(0),
		},
	},

	// streaming
	{
		// minimum free ms in the current game frame to allow streaming to quick in
		5,
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

		// obj segments z coordinates
		// note that each spt's z coordinate much be larger than or equal to the previous one's,
		// since the vip renders obj worlds in reverse order (__spt3 to __spt0)
		{
			// __spt0
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt1
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt2
			FTOFIX19_13(LAYER_0_PARTICLES),
			// __spt3
			FTOFIX19_13(LAYER_0_PARTICLES),
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			ITOFIX19_13(__DISTANCE_EYE_SCREEN),
			// distance from left to right eye (depth sensation)
			ITOFIX19_13(__BASE_FACTOR),
			// horizontal view point center
			ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
			// vertical view point center
			ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER),
		},
	},

	// physics
	{
		// gravity
		{
			ITOFIX19_13(0),
			ITOFIX19_13(__GRAVITY),
			ITOFIX19_13(0)
		},

		// friction
		FTOFIX19_13(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)LEVEL1_INTERSECTION_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)NULL,

		// textures to preload
		(StageTextureEntryDefinition*)NULL,

		// background music
		(const u16 (*)[])KRISSE_BGM,
	},

	// entities
	{
		// ui
		{
			LEVEL1_INTERSECTION_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		LEVEL1_INTERSECTION_STAGE_ST_ENTITIES,
	},
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_EXIT_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"IntExit",

	// offset from entry point (x, y, z)
	{
		FTOFIX19_13(-16),
		FTOFIX19_13(0),
		FTOFIX19_13(-SORT_INCREMENT),
	},
};

StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_LOWER_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"IntEntr2",

	// offset from entry point (x, y, z)
	{
		FTOFIX19_13(16),
		FTOFIX19_13(0),
		FTOFIX19_13(-SORT_INCREMENT),
	},
};

StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_UPPER_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL1_INTERSECTION_STAGE_ST,

	// name of the entity to start at
	"IntEntr1",

	// offset from entry point (x, y, z)
	{
		FTOFIX19_13(16),
		FTOFIX19_13(0),
		FTOFIX19_13(-SORT_INCREMENT),
	},
};

