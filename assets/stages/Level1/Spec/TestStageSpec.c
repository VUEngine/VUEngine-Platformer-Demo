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

extern StageEntryPointROMSpec LEVEL1_HOUSE_STAGE_MAIN_EP;
extern StageEntryPointROMSpec LEVEL1_COIN_ROOM_STAGE_MAIN_EP;
extern StageEntryPointROMSpec LEVEL1_INTERSECTION_STAGE_UPPER_EP;
extern StageEntryPointROMSpec LEVEL1_INTERSECTION_STAGE_EXIT_EP;
extern StageEntryPointROMSpec LEVEL1_TOWER_STAGE_MAIN_EP;
extern u16 WORLD_0_0_0_BGM[][2];

StageEntryPointROMSpec TEST_LS_BACK_EP;
StageEntryPointROMSpec TEST_LS_FRONT_EP;

extern EntitySpec BANDANA_AG;
extern EntitySpec BUSH_AG;
extern EntitySpec CANNON_AC;
extern EntitySpec CLOUD_A_IM;
extern EntitySpec CLOUDS_IM;
extern EntitySpec COIN_AG;
extern EntitySpec COIN_BACK_AG;
extern EntitySpec COLLISION_CL;
extern EntitySpec COLLISION_HIT_CL;
extern EntitySpec COLLISION_TOP_CL;
extern EntitySpec MANAGED_ENTITY;
extern EntitySpec DOOR_AG;
extern EntitySpec DOUBLE_JUMP_SIGN_IM;
extern EntitySpec GRASS_AG;
extern EntitySpec GUI_AG;
extern EntitySpec HERO_AC;
extern EntitySpec COG_WHEEL_IM;
extern EntitySpec HIDE_LAYER_10x7_AG;
extern EntitySpec JUMP_SIGN_IM;
extern EntitySpec KEY_AG;
extern EntitySpec KEY_DOOR_AG;
extern EntitySpec LAYER_SWITCH_DOOR_AG;
extern EntitySpec LAYER_SWITCH_DOOR_BACK_AG;
extern EntitySpec LEVEL_1_HOUSE_IM;
extern EntitySpec TEST_1_BACK_1_IM;
extern EntitySpec TEST_1_BACK_5_IM;
extern EntitySpec TEST_1_MAIN_1_IM;
extern EntitySpec TEST_1_MAIN_2_IM;
extern EntitySpec TEST_1_MAIN_3_A_IM;
extern EntitySpec TEST_1_MAIN_3_B_IM;
extern EntitySpec TEST_1_MAIN_4_IM;
extern EntitySpec TEST_1_MAIN_5_IM;
extern EntitySpec TEST_1_MAIN_6_IM;
extern EntitySpec LEVEL_1_TOWER_IM;
extern EntitySpec MANAGED_ENTITY;
extern EntitySpec MOUND_1_IM;
extern EntitySpec MOUND_2_IM;
extern EntitySpec MOUND_BG_BACK_IM;
extern EntitySpec MOUND_BG_FRONT_IM;
extern EntitySpec RUN_SIGN_IM;
extern EntitySpec SAW_BLADE_H3_AC;
extern EntitySpec SAW_BLADE_H8_AC;
extern EntitySpec SAW_BLADE_V3_AC;
extern EntitySpec SMOKE_PS;
extern EntitySpec TORCH_SMOKE_PS;
extern EntitySpec SNAIL_3_AC;
extern EntitySpec STAR_AG;
extern EntitySpec WATER_SPLASH_PS;
extern EntitySpec WATERFALL_STREAM_2x16_AG;
extern EntitySpec WATERFALL_STREAM_2x28_AG;
extern EntitySpec WATERFALL_TOP_AG;
extern EntitySpec WATER_POND_EN;
extern EntitySpec TEST_1_PS;
extern EntitySpec TEST_2_PS;
extern EntitySpec MOVING_PLATFORM_V6_AC;


//---------------------------------------------------------------------------------------------------------
//												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.


//---------------------------------------------------------------------------------------------------------
//											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

const Size collision_48_5_2 = 	{48 * 8, 8 * 8, 1 * 8};

PositionedEntityROMSpec TEST_STAGE_ST_CHILDREN[] =
{
//	{&TORCH_SMOKE_PS,				{(192-64),	(224/2), 	(LAYER_0_FOREGROUND + 16), 0},	0, NULL, NULL, NULL, false},
//	{&SMOKE_PS,						{(192),	(224/2), 	(LAYER_0_FOREGROUND + 16), 0},	0, NULL, NULL, NULL, false},
//	{&SAW_BLADE_H8_AC,				{(192+64),	(112), 	(0), 0},			0, NULL, NULL, NULL, false},
//	{&SAW_BLADE_V3_AC,				{(192),	(112), 	(0), 0},			0, NULL, NULL, NULL, false},
//	{&SNAIL_3_AC,					{(192-64), (112), 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT},			0, NULL, NULL, NULL, false},
	{&TEST_1_PS,					{(192 + 20),	(8), 	(0), 0},0, NULL, NULL, NULL, false},
	{&TEST_2_PS,					{(2),	(112), 	(0), 0},0, NULL, NULL, NULL, false},
//	{&TEST_2_PS,					{(10),	(112/16), 	(0), 0},0, NULL, NULL, NULL, false},
	{&COLLISION_CL,					{(192),	(224/2+60), 	(0), 0},	0, "EntryPoint", NULL, (void*)&collision_48_5_2, false},
//	{&MOVING_PLATFORM_V6_AC,		{(192),	(112), 	LAYER_0_ENEMIES, LAYER_0_ENEMIES_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
//	{&TEST_COG_WHEEL_IM,			{(192),	(224/2), (0), 0},	0, "EntryPoint", NULL, NULL, false}, // right floor
//	{&HIDE_LAYER_10x7_AG,			{(192+100), (100),	(LAYER_0_FOREGROUND + -SORT_INCREMENT * 2), 0}, 0, NULL, NULL, NULL, false},
//	{&WATER_POND_EN,			{(192+100), (100),	(LAYER_0_FOREGROUND + -SORT_INCREMENT * 2), 0}, 0, NULL, NULL, NULL, false},
//	{&KEY_DOOR_AG,					{(44), 	(112-12), 	LAYER_0_DOORS, LAYER_0_DOORS_DISPLACEMENT}, 			0, "HouseEnt", NULL, (void*)&LEVEL1_HOUSE_STAGE_MAIN_EP, false},
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec TEST_STAGE_ST_UI_CHILDREN[] =
{
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
//											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const TEST_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&ASTONISH_FONT_SHADOW,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMSpec* const TEST_STAGE_ST_CHARSETS[] =
{
	NULL
};

TextureSpec* const TEST_STAGE_ST_TEXTURES[] =
{
	NULL
};

const PostProcessingEffect TEST_STAGE_ST_POST_PROCESSING_EFFECTS[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec TEST_STAGE_ST =
{
	// allocator
	__TYPE(Stage),

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

		// camera's frustum
        {
        	// x0
        	0,
        	// y0
			0,
			// z0
			-10,
        	// x1
        	__SCREEN_WIDTH,
        	// y1
        	__SCREEN_HEIGHT,
        	// z1
        	__SCREEN_WIDTH * 5
        }
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
		// deferred
		false
	},

	// rendering
	{
		// number of cycles the texture writing is idle
		0,

		// maximum number of texture's rows to write each time the texture writing is active
		5,

		// maximum number of rows to compute on each call to the affine functions
		56,

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
			(BrightnessRepeatSpec*)NULL,
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

		// object segments sizes (up to 1024 in total)
		// can impact performance, make sure to configure only as large as maximally needed
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
			LAYER_0_PARTICLES,
		},

		// optical configuration values
		{
			// maximum view distance's power into the horizon
			__MAXIMUM_X_VIEW_DISTANCE, __MAXIMUM_Y_VIEW_DISTANCE,
			// distance of the eyes to the screen
			__DISTANCE_EYE_SCREEN,
			// distance from left to right eye (depth sensation)
			__BASE_FACTOR,
			// horizontal view point center
			__HORIZONTAL_VIEW_POINT_CENTER,
			// vertical view point center
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
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)TEST_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)TEST_STAGE_ST_CHARSETS,

		// textures to preload
		(TextureSpec**)TEST_STAGE_ST_TEXTURES,

		// background music
		NULL,
//		(const u16 (*)[])WORLD_0_0_0_BGM,
	},

	// entities
	{
		// ui
		{
			TEST_STAGE_ST_UI_CHILDREN,
			__TYPE(UiContainer),
		},

		// children
		TEST_STAGE_ST_CHILDREN,
	},

	// post processing effects
	(PostProcessingEffect*)TEST_STAGE_ST_POST_PROCESSING_EFFECTS,
};


//---------------------------------------------------------------------------------------------------------
//												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMSpec TEST_STAGE_EP =
{
	// the stage to load
	(StageSpec*)&TEST_STAGE_ST,

	// name of the entity to start at
	"EntryPoint",

	// offset from entry point (x, y, z)
	{
		-100,
		-60,
		0,
		0
	},

	// facing direction of the hero
	__RIGHT,

	// whether this entry point acts as a checkpoint
	false,
};
