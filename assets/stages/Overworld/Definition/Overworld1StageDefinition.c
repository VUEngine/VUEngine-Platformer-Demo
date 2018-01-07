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
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef OVERWORLD1_STAGE_ST_ENTITIES[] =
{
	{&WATER_A_AG, {(26), (86), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Water
	{&WATER_A_AG, {(70), (18), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Water
	{&WATER_A_AG, {(74), (176), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Water
	{&FLOWER_A_AG, {(124), (118), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&FLOWER_A_AG, {(130), (82), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&FLOWER_A_AG, {(156), (200), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&HERO_IDLE_AG, {(160), (92), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Hero (Idle)
	{&OVERWORLD_1_IM, {(192), (112), (LAYER_0_BACKGROUND)}, 0, NULL, NULL, NULL, false}, // Overworld Static Image
	{&FLOWER_A_AG, {(218), (168), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&SMOKE_PS, {(222.5), (48), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Smoke
	{&FLOWER_A_AG, {(226), (132), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower
	{&FLOWER_A_AG, {(290), (136), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Flower

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef OVERWORLD1_STAGE_ST_UI_ENTITIES[] =
{
	{&GUI_OVERWORLD_AG, {(192), (216), (0)}, 0, NULL, NULL, NULL, false}, // GUI

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
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

		// camera's initial position inside the game world
		{
			// x
			__I_TO_FIX10_6(0),
			// y
			__I_TO_FIX10_6(0),
			// z
			__I_TO_FIX10_6(0),
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

		// OBJECT segments z coordinates
		// note that each spt's z coordinate much be larger than or equal to the previous one's,
		// since the vip renders obj worlds in reverse order (__spt3 to __spt0)
		{
			// __spt0
			__F_TO_FIX10_6(LAYER_0 - 1),
			// __spt1
			__F_TO_FIX10_6(LAYER_0 - 1),
			// __spt2
			__F_TO_FIX10_6(LAYER_0 - 1),
			// __spt3
			__F_TO_FIX10_6(LAYER_0 - 1),
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			__I_TO_FIX10_6(__DISTANCE_EYE_SCREEN),
			// distance from left to right eye (depth sensation)
			__I_TO_FIX10_6(__BASE_FACTOR),
			// horizontal view point center
			__I_TO_FIX10_6(__HORIZONTAL_VIEW_POINT_CENTER),
			// vertical view point center
			__I_TO_FIX10_6(__VERTICAL_VIEW_POINT_CENTER),
		},
	},

	// physics
	{
		// gravity
		{
			__I_TO_FIX10_6(0),
			__I_TO_FIX10_6(__GRAVITY),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)OVERWORLD1_STAGE_ST_FONTS,

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
			OVERWORLD1_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		OVERWORLD1_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};
