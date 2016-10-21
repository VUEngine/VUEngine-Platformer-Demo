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
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <TitleScreenState.h>
#include <VIPManager.h>
#include <Fonts.h>
#include <objects.h>
#include <screens.h>
#include <sound.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef CASTLE_CHILD_ENTITIES[] =
{
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(-30),  FTOFIX19_13(-23), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, true}, // left
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(5),    FTOFIX19_13(-12), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, true}, // middle
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(39),   FTOFIX19_13(-23), FTOFIX19_13(0)}, 0, NULL, NULL, NULL, true}, // right
	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TITLE_SCREEN_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,		{FTOFIX19_13(0),    FTOFIX19_13(22), 	FTOFIX19_13(LAYER_5)}, 0, NULL, NULL, NULL, true},
	{&CLOUDS_IM,			{FTOFIX19_13(0),    FTOFIX19_13(114), 	FTOFIX19_13(LAYER_4)}, 0, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,	{FTOFIX19_13(0),    FTOFIX19_13(132), 	FTOFIX19_13(LAYER_3)}, 0, NULL, NULL, NULL, true},

	{&MOUND_BG_CASTLE_IM, 	{FTOFIX19_13(338),  FTOFIX19_13(94), 	FTOFIX19_13(LAYER_3 + SORT_INCREMENT)}, 0, NULL, (struct PositionedEntity*)CASTLE_CHILD_ENTITIES, NULL, true},

	{&STAR_AG, 	            {FTOFIX19_13(344),  FTOFIX19_13(-8), 	FTOFIX19_13(LAYER_5)},  0, NULL, NULL, NULL, true},

	{&FLOOR_16x12_IG,		{FTOFIX19_13(-16),  FTOFIX19_13(208), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&FLOOR_4x12_IG,		{FTOFIX19_13(64),   FTOFIX19_13(192), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&FLOOR_22x5_IG,		{FTOFIX19_13(192),  FTOFIX19_13(188), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&FLOOR_16x12_IG,		{FTOFIX19_13(360),  FTOFIX19_13(200), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},

	{&COLLISION_2x28x1, 	{FTOFIX19_13(92),   FTOFIX19_13(112), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&COLLISION_2x28x1, 	{FTOFIX19_13(292),  FTOFIX19_13(112), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},

	{&HERO_BANDANA_AG, 		{FTOFIX19_13(192),  FTOFIX19_13(157), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},

	{&GRASS_AG,      	    {FTOFIX19_13(34),   FTOFIX19_13(152), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&BUSH_AG,      	    {FTOFIX19_13(366),  FTOFIX19_13(148), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&FENCE_IM,      	    {FTOFIX19_13(322),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&FENCE_IM,      	    {FTOFIX19_13(339),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},

	{&COIN_AG, 		        {FTOFIX19_13(57),   FTOFIX19_13(134), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},
	{&COIN_AG, 		        {FTOFIX19_13(71),   FTOFIX19_13(134), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},

	{&VBJAENGINE_IM,        {FTOFIX19_13(192),  FTOFIX19_13(18), 	FTOFIX19_13(LAYER_1)},  0, NULL, NULL, NULL, true},
	{&LOGO_IM, 			    {FTOFIX19_13(192),  FTOFIX19_13(54), 	FTOFIX19_13(LAYER_0)},  0, NULL, NULL, NULL, true},

	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TITLE_SCREEN_ST_UI_CHILDREN[] =
{
	{&GUI_BLANK_IM,			{FTOFIX19_13(192), 	FTOFIX19_13(208), 	FTOFIX19_13(0)}, 0, NULL, NULL, NULL, true},
	{&GUI_BLANK_IM,			{FTOFIX19_13(192), 	FTOFIX19_13(216), 	FTOFIX19_13(0)}, 0, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 												PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const TITLE_SCREEN_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

StageTextureEntryROMDef TITLE_SCREEN_ST_TEXTURES[] =
{
	{NULL, false}
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TITLE_SCREEN_ST =
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
            ITOFIX19_13(0)
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
		0,

		// maximum number of texture's rows to write each time the texture writing is active
		64,

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
        	__AVAILABLE_CHAR_OBJECTS,
            // __spt1
        	0,
            // __spt2
        	0,
            // __spt3
        	0,
        },

        // obj segments z coordinates
        // Note that each SPT's z coordinate much be larger than or equal to the previous one's,
        // since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
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
        (FontDefinition**)TITLE_SCREEN_ST_FONTS,

        // char sets to preload
        (CharSetDefinition**)NULL,

        // textures to preload
        (StageTextureEntryDefinition*)TITLE_SCREEN_ST_TEXTURES,

        // background music
        (const u16 (*)[])WORLD_0_0_0_BGM,
    },

    // entities
    {
        // ui
        {
        	TITLE_SCREEN_ST_UI_CHILDREN,
            __TYPE(UiContainer),
        },

        // children
        TITLE_SCREEN_ST_CHILDREN,
    },
};
