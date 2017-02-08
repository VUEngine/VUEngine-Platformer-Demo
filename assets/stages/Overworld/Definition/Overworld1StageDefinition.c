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
#include <Fonts.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition FLOWER_A_AG;
extern EntityDefinition GUI_OVERWORLD_AG;
extern EntityDefinition HERO_IDLE_AG;
extern EntityDefinition OVERWORLD_1_IM;
extern EntityDefinition SMOKE_PS;
extern EntityDefinition WATER_A_AG;
extern u16 KRISSE_BGM[][2];



//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef OVERWORLD1_STAGE_ST_ENTITIES[] =
{
	{&WATER_A_AG, {FTOFIX19_13(26), FTOFIX19_13(86), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Water
	{&WATER_A_AG, {FTOFIX19_13(70), FTOFIX19_13(18), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Water
	{&WATER_A_AG, {FTOFIX19_13(74), FTOFIX19_13(176), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Water
	{&FLOWER_A_AG, {FTOFIX19_13(124), FTOFIX19_13(118), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&FLOWER_A_AG, {FTOFIX19_13(130), FTOFIX19_13(82), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&FLOWER_A_AG, {FTOFIX19_13(156), FTOFIX19_13(200), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&HERO_IDLE_AG, {FTOFIX19_13(160), FTOFIX19_13(92), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Hero (Idle)
	{&OVERWORLD_1_IM, {FTOFIX19_13(192), FTOFIX19_13(112), FTOFIX19_13(LAYER_0_BACKGROUND)}, 0, NULL, NULL, NULL, false}, // Overworld Static Image
	{&FLOWER_A_AG, {FTOFIX19_13(218), FTOFIX19_13(168), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&SMOKE_PS, {FTOFIX19_13(222.5), FTOFIX19_13(48), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Smoke
	{&FLOWER_A_AG, {FTOFIX19_13(226), FTOFIX19_13(132), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&FLOWER_A_AG, {FTOFIX19_13(290), FTOFIX19_13(136), FTOFIX19_13(LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef OVERWORLD1_STAGE_ST_UI_ENTITIES[] =
{
	{&GUI_OVERWORLD_AG, {FTOFIX19_13(192), FTOFIX19_13(216), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // GUI

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const OVERWORLD1_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef OVERWORLD1_STAGE_ST =
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
		(FontDefinition**)OVERWORLD1_STAGE_ST_FONTS,

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
			OVERWORLD1_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		OVERWORLD1_STAGE_ST_ENTITIES,
	},
};
