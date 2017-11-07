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
#include <PostProcessingEffects.h>



//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL1_HOUSE_STAGE_MAIN_EP;
extern StageEntryPointROMDef LEVEL1_COIN_ROOM_STAGE_MAIN_EP;
extern StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_UPPER_EP;
extern StageEntryPointROMDef LEVEL1_INTERSECTION_STAGE_EXIT_EP;
extern StageEntryPointROMDef LEVEL1_TOWER_STAGE_MAIN_EP;
extern u16 WORLD_0_0_0_BGM[][2];

StageEntryPointROMDef TEST_LEVEL_LS_BACK_EP;
StageEntryPointROMDef TEST_LEVEL_LS_FRONT_EP;

extern EntityDefinition BANDANA_AG;
extern EntityDefinition BUSH_AG;
extern EntityDefinition CANNON_AC;
extern EntityDefinition CLOUD_A_IM;
extern EntityDefinition CLOUDS_IM;
extern EntityDefinition COIN_AG;
extern EntityDefinition COIN_BACK_AG;
extern EntityDefinition COLLISION_CL;
extern EntityDefinition COLLISION_HIT_CL;
extern EntityDefinition COLLISION_TOP_CL;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition DOOR_AG;
extern EntityDefinition DOUBLE_JUMP_SIGN_IM;
extern EntityDefinition GRASS_AG;
extern EntityDefinition GUI_AG;
extern EntityDefinition HERO_AC;
extern EntityDefinition COG_WHEEL_IM;

extern EntityDefinition HIDE_LAYER_10x7_AG;
extern EntityDefinition JUMP_SIGN_IM;
extern EntityDefinition KEY_AG;
extern EntityDefinition KEY_DOOR_AG;
extern EntityDefinition LAYER_SWITCH_DOOR_AG;
extern EntityDefinition LAYER_SWITCH_DOOR_BACK_AG;
extern EntityDefinition LEVEL_1_HOUSE_IM;
extern EntityDefinition TEST_LEVEL_1_BACK_1_IM;
extern EntityDefinition TEST_LEVEL_1_BACK_5_IM;
extern EntityDefinition TEST_LEVEL_1_MAIN_1_IM;
extern EntityDefinition TEST_LEVEL_1_MAIN_2_IM;
extern EntityDefinition TEST_LEVEL_1_MAIN_3_A_IM;
extern EntityDefinition TEST_LEVEL_1_MAIN_3_B_IM;
extern EntityDefinition TEST_LEVEL_1_MAIN_4_IM;
extern EntityDefinition TEST_LEVEL_1_MAIN_5_IM;
extern EntityDefinition TEST_LEVEL_1_MAIN_6_IM;
extern EntityDefinition LEVEL_1_TOWER_IM;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition MOUND_1_IM;
extern EntityDefinition MOUND_2_IM;
extern EntityDefinition MOUND_BG_BACK_IM;
extern EntityDefinition MOUND_BG_FRONT_IM;
extern EntityDefinition RUN_SIGN_IM;
extern EntityDefinition SAW_BLADE_H3_AC;
extern EntityDefinition SAW_BLADE_H8_AC;
extern EntityDefinition SAW_BLADE_V3_AC;
extern EntityDefinition SMOKE_PS;
extern EntityDefinition SNAIL_3_AC;
extern EntityDefinition STAR_AG;
extern EntityDefinition WATER_SPLASH_PS;
extern EntityDefinition WATERFALL_STREAM_2x16_AG;
extern EntityDefinition WATERFALL_STREAM_2x28_AG;
extern EntityDefinition WATERFALL_TOP_AG;
extern EntityDefinition WATER_POND_EN;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

const Size collision_48_5_2 = 	{48 * 8, 5 * 8, 2 * 8};

PositionedEntityROMDef TEST_LEVEL_STAGE_ST_CHILDREN[] =
{
	{&COLLISION_CL,					{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(224/2+60), 	__F_TO_FIX19_13(0)},					0, NULL, NULL, (void*)&collision_48_5_2, false},
	{&COG_WHEEL_IM,					{__F_TO_FIX19_13(192),	__F_TO_FIX19_13(224/2), __F_TO_FIX19_13(0)},	0, "EntryPoint", NULL, NULL, false}, // right floor
	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TEST_LEVEL_STAGE_ST_UI_CHILDREN[] =
{
	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const TEST_LEVEL_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMDef* const TEST_LEVEL_STAGE_ST_CHARSETS[] =
{
	NULL
};

TextureDefinition* const TEST_LEVEL_STAGE_ST_TEXTURES[] =
{
	NULL
};

const PostProcessingEffect TEST_LEVEL_STAGE_ST_POST_PROCESSING_EFFECTS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TEST_LEVEL_STAGE_ST =
{
	// level
	{
		// size
		{
			// x
			384,
			// y
			224,
			// z
			384,
		},

		// screen's initial position inside the game world
		{
			// x
			__I_TO_FIX19_13(0),
			// y
			__I_TO_FIX19_13(0),
			// z
			__I_TO_FIX19_13(0)
		},
	},

	// streaming
	{
		// load padding
		96,
		// unload padding
		24,
		// streaming amplitude
		14,
		// particle removal delay cycles
		4,
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		0,

		// maximum number of texture's rows to write each time the texture writing is active
		5,

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
			0,
			// __spt1
			0,
			// __spt2
			64,
			// __spt3
			64,
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
			__F_TO_FIX19_13(24),
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_VIEW_DISTANCE_POWER,
			// distance of the eyes to the screen
			__I_TO_FIX19_13(__DISTANCE_EYE_SCREEN),
			// distance from left to right eye (depth sensation)
			__I_TO_FIX19_13(__BASE_FACTOR),
			// horizontal view point center
			__I_TO_FIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
			// vertical view point center
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
		(FontDefinition**)TEST_LEVEL_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)TEST_LEVEL_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureDefinition**)TEST_LEVEL_STAGE_ST_TEXTURES,

		// background music
		(const u16 (*)[])WORLD_0_0_0_BGM,
	},

	// entities
	{
		// ui
		{
			TEST_LEVEL_STAGE_ST_UI_CHILDREN,
			__TYPE(UiContainer),
		},

		// children
		TEST_LEVEL_STAGE_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)TEST_LEVEL_STAGE_ST_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef TEST_LEVEL_EP =
{
	// the stage to load
	(StageDefinition*)&TEST_LEVEL_STAGE_ST,

	// name of the entity to start at
	"EntryPoint",

	// offset from entry point (x, y, z)
	{
		__F_TO_FIX19_13(-90),
		__F_TO_FIX19_13(0),
		__F_TO_FIX19_13(0),
	},

	// whether this entry point acts as a checkpoint
	false,
};
