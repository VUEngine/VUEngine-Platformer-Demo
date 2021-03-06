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
//											DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntitySpec BUSH_EN;
extern EntitySpec CLOUDS_IM;
extern EntitySpec COIN_EN;
extern EntitySpec GRASS_EN;
extern EntitySpec HERO_BANDANA_EN;
extern EntitySpec LOGO_IM;
extern EntitySpec LOW_POWER_INDICATOR_LB;
extern EntitySpec MOUND_BG_BACK_IM;
extern EntitySpec MOUND_BG_CASTLE_FLAG_EN;
extern EntitySpec MOUND_BG_CASTLE_IM;
extern EntitySpec MOUND_BG_FRONT_IM;
extern EntitySpec STAR_EN;
extern EntitySpec TITLE_SCREEN_STAGE_MAIN_1_IM;
extern EntitySpec TITLE_SCREEN_STAGE_MAIN_FRONT_1_IM;
extern EntitySpec VUENGINE_LOGO_IM;
extern TextureSpec LOGO_L_TX;
extern TextureSpec LOGO_OUTLINE_L_TX;
extern TextureSpec LOGO_OUTLINE_R_TX;
extern TextureSpec LOGO_R_TX;
extern EntitySpec CLOUDS_BACKGROUND_EN;

//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMSpec TITLE_SCREEN_STAGE_ST_ENTITIES[] =
{
	{&LOW_POWER_INDICATOR_LB, 	{__LOW_POWER_ENTITY_X_POSITION, __LOW_POWER_ENTITY_Y_POSITION, __LOW_POWER_ENTITY_Z_POSITION, __LOW_POWER_ENTITY_Z_DISPLACEMENT}, 0, NULL, NULL, NULL, false},
//	{&CLOUDS_BACKGROUND_EN, 				{192, 112 - 112/2 - 12, LAYER_3, 0}, 		0, NULL, NULL, NULL, true}, // Front
	{&MOUND_BG_FRONT_IM, 					{  0, 136, LAYER_2, 0}, 		0, NULL, NULL, NULL, false}, // Front
	{&GRASS_EN, 							{ 32, 152, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Grass
	{&COIN_EN, 								{ 56, 134, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Coin
	{&COIN_EN, 								{ 72, 134, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Coin
	{&TITLE_SCREEN_STAGE_MAIN_1_IM, 		{192, 168, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Main Layer
	{&LOGO_IM, 								{192,  53, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Logo
	{&VUENGINE_LOGO_IM, 					{192,  18, LAYER_1, 0}, 		0, NULL, NULL, NULL, false}, // VUEngine
	{&HERO_BANDANA_EN, 						{192, 157, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Hero
	{&TITLE_SCREEN_STAGE_MAIN_FRONT_1_IM, 	{192, 168, LAYER_0, 0}, 		0, NULL, NULL, NULL, false}, // Main Layer Front
	{&CLOUDS_IM, 							{194, 128, LAYER_4, 0}, 		0, NULL, NULL, NULL, false}, // Clouds
	{&MOUND_BG_BACK_IM, 					{280,  72, LAYER_5, 0}, 		0, NULL, NULL, NULL, false}, // Mountains
	{&MOUND_BG_CASTLE_IM, 					{300, 104, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle
	{&MOUND_BG_CASTLE_FLAG_EN, 				{274,  85, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle Flag L
	{&MOUND_BG_CASTLE_FLAG_EN, 				{304,  95, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle Flag M
	{&MOUND_BG_CASTLE_FLAG_EN, 				{334,  85, LAYER_2 + 32, 0}, 	0, NULL, NULL, NULL, false}, // Castle Flag R
	{&STAR_EN, 								{392,  16, LAYER_5 - 1, 0},		0, NULL, NULL, NULL, false}, // Star
	{&BUSH_EN, 								{368, 148, LAYER_0, 0},			0, NULL, NULL, NULL, false}, // Bush

	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMSpec TITLE_SCREEN_STAGE_ST_UI_ENTITIES[] =
{
	{NULL, {0,0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMSpec* const TITLE_SCREEN_STAGE_ST_FONTS[] =
{
	NULL
};

TextureSpec* const TITLE_SCREEN_STAGE_ST_TEXTURES[] =
{
	NULL
};


extern Sound SOUNDTRACK_01;

SoundROM* const TITLE_SCREEN_STAGE_ST_SOUNDS[] =
{
	&SOUNDTRACK_01,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMSpec TITLE_SCREEN_STAGE_ST =
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
			__SCREEN_HEIGHT,
			// z
			__SCREEN_DEPTH,
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
		40,
		// unload padding
		16,
		// streaming amplitude
		24,
		// particle removal delay cycles
		0,
		// deferred
		false
	},

	// rendering
	{
		// maximum number of texture's rows to write each time the texture writing is active
		12,

		// maximum number of rows to compute on each call to the affine functions
		16 * 8,

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
		5,

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
			__F_TO_FIX10_6(0),
			__I_TO_FIX10_6(0)
		},

		// friction
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontSpec**)TITLE_SCREEN_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetSpec**)NULL,

		// textures to preload
		(TextureSpec**)TITLE_SCREEN_STAGE_ST_TEXTURES,

		// background sounds
		(Sound**)TITLE_SCREEN_STAGE_ST_SOUNDS,
	},

	// entities
	{
		// ui
		{
			(PositionedEntity*)TITLE_SCREEN_STAGE_ST_UI_ENTITIES,
			__TYPE(UIContainer),
		},

		// children
		(PositionedEntity*)TITLE_SCREEN_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};
