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

extern EntityDefinition ADJUSTMENT_SCREEN_VUENGINE_BG_IM;
extern EntityDefinition ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L;
extern EntityDefinition ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R;
extern EntityDefinition ADJUSTMENT_SCREEN_VUENGINE_LOGO_IM;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef ADJUSTMENT_SCREEN_STAGE_ST_ENTITIES[] =
{
	{&ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L, {__F_TO_FIX10_6(12), __F_TO_FIX10_6(12), __F_TO_FIX10_6(0)}, 0, NULL, NULL, NULL, false}, // Icon Top Left (Left Eye)
	{&ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R, {__F_TO_FIX10_6(12), __F_TO_FIX10_6(212), __F_TO_FIX10_6(0)}, 0, NULL, NULL, NULL, false}, // Icon Bottom Left (Right Eye)
	{&ADJUSTMENT_SCREEN_VUENGINE_BG_IM, {__F_TO_FIX10_6(192), __F_TO_FIX10_6(112), __F_TO_FIX10_6(16)}, 0, NULL, NULL, NULL, false}, // Background
	{&ADJUSTMENT_SCREEN_VUENGINE_LOGO_IM, {__F_TO_FIX10_6(192), __F_TO_FIX10_6(112), __F_TO_FIX10_6(0)}, 0, NULL, NULL, NULL, false}, // Logo
	{&ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_L, {__F_TO_FIX10_6(372), __F_TO_FIX10_6(212), __F_TO_FIX10_6(0)}, 0, NULL, NULL, NULL, false}, // Icon Bottom Right (Left Eye)
	{&ADJUSTMENT_SCREEN_VUENGINE_ICON_IM_R, {__F_TO_FIX10_6(372), __F_TO_FIX10_6(12), __F_TO_FIX10_6(0)}, 0, NULL, NULL, NULL, false}, // Icon Top Right (Right Eye)

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef ADJUSTMENT_SCREEN_STAGE_ST_UI_ENTITIES[] =
{

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const ADJUSTMENT_SCREEN_STAGE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef ADJUSTMENT_SCREEN_STAGE_ST =
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
				8,
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
			__F_TO_FIX10_6(LAYER_0_PARTICLES),
			// __spt1
			__F_TO_FIX10_6(LAYER_0_PARTICLES),
			// __spt2
			__F_TO_FIX10_6(LAYER_0_PARTICLES),
			// __spt3
			__F_TO_FIX10_6(LAYER_0_PARTICLES),
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
		__F_TO_FIX10_6(0.1f),
	},

	// assets
	{
		// fonts to preload
		(FontDefinition**)ADJUSTMENT_SCREEN_STAGE_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)NULL,

		// textures to preload
		(TextureDefinition**)NULL,

		// background music
		(const u16 (*)[])NULL,
	},

	// entities
	{
		// ui
		{
			ADJUSTMENT_SCREEN_STAGE_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		ADJUSTMENT_SCREEN_STAGE_ST_ENTITIES,
	},

	// post processing effects
	(PostProcessingEffect*)NULL,
};
