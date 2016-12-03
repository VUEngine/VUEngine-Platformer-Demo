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
//                                                 INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>
#include <macros.h>
#include <PlatformerLevelState.h>
#include <Languages.h>
#include <VIPManager.h>
#include <Fonts.h>

#include <objects.h>


//---------------------------------------------------------------------------------------------------------
//                                                 PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_MAIN_HOUSE_EP;
extern u16 KRISSE_BGM[][2];

extern VBVec3D collision_2_28_1;
extern VBVec3D collision_3_2_1;
extern VBVec3D collision_48_2_1;


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_HOUSE_ST_CHILDREN[] =
{
    // since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,				{FTOFIX19_13(0),    FTOFIX19_13(80), 	FTOFIX19_13(LAYER_5)},            	0, NULL, NULL, NULL, true},
	{&CLOUDS_IM,					{FTOFIX19_13(0),    FTOFIX19_13(144), 	FTOFIX19_13(LAYER_4)},            	0, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,			{FTOFIX19_13(18),   FTOFIX19_13(138), 	FTOFIX19_13(LAYER_3)},            	0, NULL, NULL, NULL, true},

    {&LEVEL_1_HOUSE_MAIN_IM,    	{FTOFIX19_13(192), 	FTOFIX19_13(112), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, 	0, NULL, NULL, NULL, true},

    {&COLLISION_CL,             	{FTOFIX19_13(192), 	FTOFIX19_13(90), 	FTOFIX19_13(LAYER_0)}, 				0, NULL, NULL, (void*)&collision_48_2_1, true}, // top ceiling
    {&COLLISION_CL,             	{FTOFIX19_13(192), 	FTOFIX19_13(168), 	FTOFIX19_13(LAYER_0)}, 				0, NULL, NULL, (void*)&collision_48_2_1, true}, // bottom floor
    {&COLLISION_CL,             	{FTOFIX19_13(120), 	FTOFIX19_13(80), 	FTOFIX19_13(LAYER_0)}, 				0, NULL, NULL, (void*)&collision_2_28_1, true}, // left wall
    {&COLLISION_CL,             	{FTOFIX19_13(264), 	FTOFIX19_13(80), 	FTOFIX19_13(LAYER_0)}, 				0, NULL, NULL, (void*)&collision_2_28_1, true}, // right wall
    {&COLLISION_TOP_CL,       		{FTOFIX19_13(240),  FTOFIX19_13(148),   FTOFIX19_13(LAYER_0)},    			0, NULL, NULL, (void*)&collision_3_2_1, true}, // fireplace

	{&LEVEL_1_HOUSE_LIGHT_IM,		{FTOFIX19_13(196),  FTOFIX19_13(140), 	FTOFIX19_13(LAYER_0_ITEMS - 1)},    0, NULL, NULL, NULL, true},

	{&COIN_AG,						{FTOFIX19_13(204),  FTOFIX19_13(148), 	FTOFIX19_13(LAYER_0_ITEMS)},       26, NULL, NULL, NULL, true},

    {&HERO_AC,                      {FTOFIX19_13(148),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0)}, 				0, HERO_NAME, NULL, NULL, true},

	{&CLOCK_AG,						{FTOFIX19_13(180), 	FTOFIX19_13(128),   FTOFIX19_13(LAYER_0 + 24)},   		0, NULL, NULL, NULL, true},

    {&KEY_DOOR_AG,                  {FTOFIX19_13(148),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_DOORS)}, 		0, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_HOUSE_EP, true},

	{&FIRE_SMALL_AG,				{FTOFIX19_13(240),  FTOFIX19_13(154), 	FTOFIX19_13(LAYER_0_FOREGROUND)},   0, NULL, NULL, NULL, true},

    {NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_HOUSE_ST_UI_CHILDREN[] =
{
    {&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(215), FTOFIX19_13(-4)}, 0, NULL, NULL, NULL, true},

    {NULL, {0,0,0}, 0, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

FontROMDef* const LEVEL_1_HOUSE_ST_FONTS[] =
{
	&PLATFORMER_DEFAULT_FONT,
	&PLATFORMER_GUI_FONT,

	NULL
};

CharSetROMDef* const LEVEL_1_HOUSE_ST_CHARSETS[] =
{
	&LEVEL_1_HOUSE_MAIN_CH,

	NULL
};


//---------------------------------------------------------------------------------------------------------
//                                             STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_HOUSE_ST =
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
        (FontDefinition**)LEVEL_1_HOUSE_ST_FONTS,

        // char sets to preload
        (CharSetDefinition**)LEVEL_1_HOUSE_ST_CHARSETS,

        // textures to preload
        (StageTextureEntryDefinition*)NULL,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // entities
    {
        // ui
        {
            LEVEL_1_HOUSE_ST_UI_CHILDREN,
            __TYPE(UiContainer),
        },

        // children
        LEVEL_1_HOUSE_ST_CHILDREN,
    },
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_HOUSE_MAIN_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_HOUSE_ST,

	// name of the entity to start at
    "EntryDoor",

    // offset from entry point (x, y, z)
    {FTOFIX19_13(14), 0, FTOFIX19_13(-SORT_INCREMENT)},
}};