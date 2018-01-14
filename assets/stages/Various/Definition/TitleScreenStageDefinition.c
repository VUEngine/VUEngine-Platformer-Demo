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

extern EntityDefinition BUSH_AG;
extern EntityDefinition CLOUDS_IM;
extern EntityDefinition COIN_AG;
extern EntityDefinition GRASS_AG;
extern EntityDefinition HERO_BANDANA_AG;
extern EntityDefinition LOGO_IM;
extern EntityDefinition MOUND_BG_BACK_IM;
extern EntityDefinition MOUND_BG_CASTLE_FLAG_AG;
extern EntityDefinition MOUND_BG_CASTLE_IM;
extern EntityDefinition MOUND_BG_FRONT_IM;
extern EntityDefinition STAR_AG;
extern EntityDefinition TITLE_SCREEN_STAGE_MAIN_1_IM;
extern EntityDefinition TITLE_SCREEN_STAGE_MAIN_FRONT_1_IM;
extern EntityDefinition VUENGINE_LOGO_IM;
extern TextureDefinition LOGO_L_TX;
extern TextureDefinition LOGO_OUTLINE_L_TX;
extern TextureDefinition LOGO_OUTLINE_R_TX;
extern TextureDefinition LOGO_R_TX;
extern u16 KRISSE_BGM[][2];


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef TITLE_SCREEN_STAGE_ST_ENTITIES[] =
{
	{&MOUND_BG_FRONT_IM, {(192 + 48 + 8 ), (144), (LAYER_3)}, 0, NULL, NULL, NULL, false}, // Front
	{&GRASS_AG, {(32), (152), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Grass
	{&COIN_AG, {(56), (134), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Coin
	{&COIN_AG, {(72), (134), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Coin
	{&TITLE_SCREEN_STAGE_MAIN_1_IM, {(192), (168), (LAYER_0_FOREGROUND)}, 0, NULL, NULL, NULL, false}, // Main Layer
	{&LOGO_IM, {(192), (53), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Logo
	{&VUENGINE_LOGO_IM, {(192), (18), (LAYER_1)}, 0, NULL, NULL, NULL, false}, // VUEngine
	{&HERO_BANDANA_AG, {(192), (158), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Hero
	{&TITLE_SCREEN_STAGE_MAIN_FRONT_1_IM, {(192), (168), (LAYER_0_FOREGROUND)}, 0, NULL, NULL, NULL, false}, // Main Layer Front
	{&CLOUDS_IM, {(194), (130), (LAYER_4 - (LAYER_4 - LAYER_3) / 2 + 8)}, 0, NULL, NULL, NULL, false}, // Clouds
	{&MOUND_BG_BACK_IM, {(255), (67), (LAYER_5)}, 0, NULL, NULL, NULL, false}, // Mountains
	{&MOUND_BG_CASTLE_FLAG_AG, {(287 - 5), (84 + 8), (LAYER_4 + SORT_INCREMENT)}, 0, NULL, NULL, NULL, false}, // Castle Flag
	{&MOUND_BG_CASTLE_IM, {(317 - 16), (104 + 12), (LAYER_4 + SORT_INCREMENT)}, 0, NULL, NULL, NULL, false}, // Castle
	{&MOUND_BG_CASTLE_FLAG_AG, {(321 - 17), (95 + 9), (LAYER_4 + SORT_INCREMENT)}, 0, NULL, NULL, NULL, false}, // Castle Flag
	{&MOUND_BG_CASTLE_FLAG_AG, {(356 - 29), (84 + 8), (LAYER_4 + SORT_INCREMENT)}, 0, NULL, NULL, NULL, false}, // Castle Flag
	{&STAR_AG, {(362), (-18), (LAYER_5 - SORT_INCREMENT)}, 0, NULL, NULL, NULL, false}, // Star
	{&BUSH_AG, {(368), (148), (LAYER_0)}, 0, NULL, NULL, NULL, false}, // Bush

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TITLE_SCREEN_STAGE_ST_UI_ENTITIES[] =
{

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const TITLE_SCREEN_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

TextureDefinition* const TITLE_SCREEN_STAGE_ST_TEXTURES[] =
{
	&LOGO_L_TX,
	&LOGO_R_TX,
	&LOGO_OUTLINE_L_TX,
	&LOGO_OUTLINE_R_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TITLE_SCREEN_STAGE_ST =
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
			__F_TO_FIX10_6(__GRAVITY),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)TITLE_SCREEN_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)NULL,

		// textures to preload
		(TextureDefinition**)TITLE_SCREEN_STAGE_ST_TEXTURES,

		// background music
		(const u16 (*)[])KRISSE_BGM,
	},

	// entities
	{
		// ui
		{
			TITLE_SCREEN_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		TITLE_SCREEN_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};
