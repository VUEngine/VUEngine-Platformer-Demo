/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
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

extern EntityDefinition ADJUSTMENT_SCREEN_NINTENDO_ICON_IM_L;
extern EntityDefinition ADJUSTMENT_SCREEN_NINTENDO_ICON_IM_R;
extern EntityDefinition ADJUSTMENT_SCREEN_PVB_BG_IM;
extern EntityDefinition ADJUSTMENT_SCREEN_PVB_LOGO_IM;



//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef ADJUSTMENT_SCREEN_ST_ENTITIES[] =
{
	{&ADJUSTMENT_SCREEN_NINTENDO_ICON_IM_R, {FTOFIX19_13(8), FTOFIX19_13(216), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Icon Bottom Left (Right Eye)
	{&ADJUSTMENT_SCREEN_NINTENDO_ICON_IM_L, {FTOFIX19_13(8), FTOFIX19_13(8), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Icon Top Left (Left Eye)
	{&ADJUSTMENT_SCREEN_PVB_BG_IM, {FTOFIX19_13(192), FTOFIX19_13(112), FTOFIX19_13(64)}, 0, NULL, NULL, NULL, false}, // Background
	{&ADJUSTMENT_SCREEN_PVB_LOGO_IM, {FTOFIX19_13(192), FTOFIX19_13(110), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Logo
	{&ADJUSTMENT_SCREEN_NINTENDO_ICON_IM_R, {FTOFIX19_13(376), FTOFIX19_13(8), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Icon Top Right (Right Eye)
	{&ADJUSTMENT_SCREEN_NINTENDO_ICON_IM_L, {FTOFIX19_13(376), FTOFIX19_13(216), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, false}, // Icon Bottom Right (Left Eye)

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef ADJUSTMENT_SCREEN_ST_UI_ENTITIES[] =
{

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const ADJUSTMENT_SCREEN_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef ADJUSTMENT_SCREEN_ST =
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
		(FontDefinition**)ADJUSTMENT_SCREEN_ST_FONTS,

		// char sets to preload
		(CharSetDefinition**)NULL,

		// textures to preload
		(StageTextureEntryDefinition*)NULL,

		// background music
		(const u16 (*)[])NULL,
	},

	// entities
	{
		// ui
		{
			ADJUSTMENT_SCREEN_ST_UI_ENTITIES,
			__TYPE(UiContainer),
		},

		// children
		ADJUSTMENT_SCREEN_ST_ENTITIES,
	},
};
