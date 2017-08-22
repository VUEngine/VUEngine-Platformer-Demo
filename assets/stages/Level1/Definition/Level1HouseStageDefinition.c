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

const VBVec3D level1_house_stage_collision_128_16_8 = {128, 16, 8};
const VBVec3D level1_house_stage_collision_16_96_8 = {16, 96, 8};
const VBVec3D level1_house_stage_collision_24_24_8 = {24, 24, 8};
extern CharSetDefinition LEVEL_1_HOUSE_MAIN_CH;
extern EntityDefinition CLOCK_AG;
extern EntityDefinition CLOUDS_IM;
extern EntityDefinition COIN_AG;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition COLLISION_TOP_CL;
extern EntityDefinition FIRE_SMALL_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition KEY_DOOR_AG;
extern EntityDefinition LEVEL_1_HOUSE_LIGHT_IM;
extern EntityDefinition LEVEL_1_HOUSE_MAIN_IM;
extern EntityDefinition MOUND_BG_BACK_IM;
extern StageEntryPointROMDef LEVEL_1_MAIN_HOUSE_EP;
extern u16 KRISSE_BGM[][2];


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL1_HOUSE_STAGE_ST_ENTITIES[] =
{
	{&COLLISION_CL, {FTOFIX19_13(120), FTOFIX19_13(128), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_house_stage_collision_16_96_8, false}, // Left Collision
	{&KEY_DOOR_AG, {FTOFIX19_13(148), FTOFIX19_13(144), FTOFIX19_13(LAYER_0_DOORS)}, 0, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_HOUSE_EP, false}, // Door
	{&HERO_AC, {FTOFIX19_13(163), FTOFIX19_13(148), FTOFIX19_13(LAYER_0)}, 0, HERO_NAME, NULL, NULL, false}, // Hero
	{&CLOCK_AG, {FTOFIX19_13(180), FTOFIX19_13(128), FTOFIX19_13(LAYER_0 + 24)}, 0, NULL, NULL, NULL, false}, // Clock
	{&LEVEL_1_HOUSE_MAIN_IM, {FTOFIX19_13(192), FTOFIX19_13(112), FTOFIX19_13(LAYER_0_BACKGROUND)}, 0, NULL, NULL, NULL, false}, // House Background
	{&COLLISION_CL, {FTOFIX19_13(192), FTOFIX19_13(168), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_house_stage_collision_128_16_8, false}, // Bottom Collision
	{&COLLISION_CL, {FTOFIX19_13(192), FTOFIX19_13(88), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_house_stage_collision_128_16_8, false}, // Top Collision
	{&CLOUDS_IM, {FTOFIX19_13(194), FTOFIX19_13(149), FTOFIX19_13(LAYER_4)}, 0, NULL, NULL, NULL, false}, // Clouds
	{&LEVEL_1_HOUSE_LIGHT_IM, {FTOFIX19_13(196), FTOFIX19_13(140), FTOFIX19_13(LAYER_0_ITEMS - 1)}, 0, NULL, NULL, NULL, false}, // Light
	{&COIN_AG, {FTOFIX19_13(204), FTOFIX19_13(146), FTOFIX19_13(LAYER_0_ITEMS)}, 26, NULL, NULL, NULL, false}, // Coin
	{&FIRE_SMALL_AG, {FTOFIX19_13(240), FTOFIX19_13(155), FTOFIX19_13(12)}, 0, NULL, NULL, NULL, false}, // Fire
	{&COLLISION_TOP_CL, {FTOFIX19_13(240), FTOFIX19_13(152), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_house_stage_collision_24_24_8, false}, // Fireplace Collision
	{&MOUND_BG_BACK_IM, {FTOFIX19_13(255), FTOFIX19_13(80), FTOFIX19_13(LAYER_5)}, 0, NULL, NULL, NULL, false}, // Mountains
	{&COLLISION_CL, {FTOFIX19_13(264), FTOFIX19_13(128), FTOFIX19_13(0)}, 0, NULL, NULL, (void*)&level1_house_stage_collision_16_96_8, false}, // Right Collision

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL1_HOUSE_STAGE_ST_UI_ENTITIES[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(216), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // GUI

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL1_HOUSE_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMDef* const LEVEL1_HOUSE_STAGE_ST_CHARSETS[] =
{
	&LEVEL_1_HOUSE_MAIN_CH,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL1_HOUSE_STAGE_ST =
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
			FTOFIX19_13(0),
			// __spt1
			FTOFIX19_13(0),
			// __spt2
			FTOFIX19_13(0),
			// __spt3
			FTOFIX19_13(0),
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
		(FontDefinition**)LEVEL1_HOUSE_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)LEVEL1_HOUSE_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureDefinition**)NULL,

		// background music
		(const u16 (*)[])KRISSE_BGM,
	},

	// entities
	{
		// ui
		{
			LEVEL1_HOUSE_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		LEVEL1_HOUSE_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL1_HOUSE_STAGE_MAIN_EP =
{
	// the stage to load
	(StageDefinition*)&LEVEL1_HOUSE_STAGE_ST,

	// name of the entity to start at
	"EntryDoor",

	// offset from entry point (x, y, z)
	{
		FTOFIX19_13(14),
		FTOFIX19_13(0),
		FTOFIX19_13(-SORT_INCREMENT),
	},

	// whether this entry point acts as a checkpoint
	false,
};

