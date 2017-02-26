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

const VBVec3D test_room_stage_collision_160_48_8 = {160, 48, 8};
const VBVec3D test_room_stage_collision_16_64_8 = {16, 64, 8};
const VBVec3D test_room_stage_collision_176_16_8 = {176, 16, 8};
const VBVec3D test_room_stage_collision_256_16_8 = {256, 16, 8};
const VBVec3D test_room_stage_collision_80_48_8 = {80, 48, 8};
extern CharSetDefinition COG_WHEEL_CH;
extern CharSetDefinition DOOR_CH;
extern CharSetDefinition GUI_CH;
extern EntityDefinition COIN_AG;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition DOOR_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition TEST_ROOM_STAGE_MAIN_1_IM;
extern EntityDefinition TEST_ROOM_STAGE_MAIN_2_IM;
extern EntityDefinition TEST_ROOM_STAGE_TEST_1_IM;
extern TextureDefinition COG_WHEEL_TX;
extern TextureDefinition DOOR_TX;
extern TextureDefinition GUI_TX;
extern TextureDefinition HERO_TX;
extern TextureDefinition TEST_ROOM_STAGE_MAIN_1_TX;
extern TextureDefinition TEST_ROOM_STAGE_TEST_1_TX;
extern u16 KRISSE_BGM[][2];


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef TEST_ROOM_STAGE_ST_CHILD_ENTITIES_TEST[] =
{
	{&COIN_AG, {FTOFIX19_13(-100), FTOFIX19_13(32), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {FTOFIX19_13(-84), FTOFIX19_13(32), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Coin
	{&SAW_BLADE_H8_AC, {FTOFIX19_13(16), FTOFIX19_13(44), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // SawBlade
	{&DOOR_AG, {FTOFIX19_13(136), FTOFIX19_13(-4), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Exit Door

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TEST_ROOM_STAGE_ST_ENTITIES[] =
{
	{&COLLISION_CL, {FTOFIX19_13(8), FTOFIX19_13(160), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&test_room_stage_collision_16_64_8, false}, // Left
	{&DOOR_AG, {FTOFIX19_13(36), FTOFIX19_13(160), FTOFIX19_13(LAYER_0)}, 0, "EntryDoor", NULL, NULL, false}, // Entry Door
	{&HERO_AC, {FTOFIX19_13(44), FTOFIX19_13(164), FTOFIX19_13(LAYER_0)}, 0, HERO_NAME, NULL, NULL, false}, // Hero
	{&TEST_ROOM_STAGE_TEST_1_IM, {FTOFIX19_13(72), FTOFIX19_13(72), FTOFIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, NULL, NULL, false}, // Test Composite
	{&COLLISION_CL, {FTOFIX19_13(80), FTOFIX19_13(104), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&test_room_stage_collision_160_48_8, false}, // Top Left
	{&COLLISION_CL, {FTOFIX19_13(144), FTOFIX19_13(184), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&test_room_stage_collision_256_16_8, false}, // Bottom
	{&TEST_ROOM_STAGE_MAIN_1_IM, {FTOFIX19_13(144), FTOFIX19_13(136), FTOFIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, NULL, NULL, false}, // Main Layer (1)
	{&MANAGED_ENTITY, {FTOFIX19_13(180), FTOFIX19_13(132), FTOFIX19_13(LAYER_0)}, 0, NULL, (struct PositionedEntity*)TEST_ROOM_STAGE_ST_CHILD_ENTITIES_TEST, NULL, false}, // Child: Test
	{&COLLISION_CL, {FTOFIX19_13(248), FTOFIX19_13(88), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&test_room_stage_collision_176_16_8, false}, // Top
	{&COLLISION_CL, {FTOFIX19_13(312), FTOFIX19_13(168), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&test_room_stage_collision_80_48_8, false}, // Bottom Right
	{&TEST_ROOM_STAGE_MAIN_2_IM, {FTOFIX19_13(320), FTOFIX19_13(120), FTOFIX19_13(LAYER_0_FOREGROUND)}, 0, NULL, NULL, NULL, false}, // Main Layer (2)
	{&COLLISION_CL, {FTOFIX19_13(344), FTOFIX19_13(112), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&test_room_stage_collision_16_64_8, false}, // Right

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TEST_ROOM_STAGE_ST_UI_ENTITIES[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(216), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // GUI

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const TEST_ROOM_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMDef* const TEST_ROOM_STAGE_ST_CHARSETS[] =
{
	&COG_WHEEL_CH,
	&GUI_CH,
	&DOOR_CH,

	NULL
};

StageTextureEntryROMDef TEST_ROOM_STAGE_ST_TEXTURES[] =
{
	{&COG_WHEEL_TX, false},
	{&GUI_TX, false},
	{&DOOR_TX, false},
	{&HERO_TX, false},
	{&TEST_ROOM_STAGE_TEST_1_TX, true},
	{&TEST_ROOM_STAGE_MAIN_1_TX, true},

	{NULL, false}
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TEST_ROOM_STAGE_ST =
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
		10,
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
				__BRIGHTNESS_DARK_RED,
				// medium red
				__BRIGHTNESS_MEDIUM_RED,
				// bright red
				__BRIGHTNESS_BRIGHT_RED,
			},

			// brightness repeat
			(BrightnessRepeatDefinition*)NULL,
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
		(FontDefinition**)TEST_ROOM_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)TEST_ROOM_STAGE_ST_CHARSETS,

		// textures to preload
		(StageTextureEntryDefinition*)TEST_ROOM_STAGE_ST_TEXTURES,

		// background music
		(const u16 (*)[])KRISSE_BGM,
	},

	// entities
	{
		// ui
		{
			TEST_ROOM_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		TEST_ROOM_STAGE_ST_ENTITIES,
	},
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef TEST_ROOM_STAGE_MAIN_EP =
{
	// the stage to load
	(StageDefinition*)&TEST_ROOM_STAGE_ST,

	// name of the entity to start at
	"EntryDoor",

	// offset from entry point (x, y, z)
	{
		FTOFIX19_13(0),
		FTOFIX19_13(0),
		FTOFIX19_13(-SORT_INCREMENT),
	},
};

