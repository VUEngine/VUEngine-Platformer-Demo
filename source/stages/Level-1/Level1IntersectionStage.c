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
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
//                                                 PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition COLLISIONS_CONTAINER_ENTITY;


//---------------------------------------------------------------------------------------------------------
//                                                 ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_INTERSECTION_MAIN_ENTITIES[] =
{
    {&LEVEL_1_INTERSECTION_MAIN_IM,   {FTOFIX19_13(0), 	FTOFIX19_13(-16), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_INTERSECTION_MAIN_COLLISIONS[] =
{
    // bottom floor
    {&COLLISION_48x2x1,             {FTOFIX19_13(0),    FTOFIX19_13(72),    FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // top ceiling
    {&COLLISION_48x2x1,             {FTOFIX19_13(0),    FTOFIX19_13(-104),  FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // right ceiling/floor
    {&COLLISION_14x18x1,            {FTOFIX19_13(136),  FTOFIX19_13(24),     FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // top left wall
    {&COLLISION_28x8x1,             {FTOFIX19_13(-144), FTOFIX19_13(-72),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // left ceiling/floor
    {&COLLISION_28x8x1,             {FTOFIX19_13(-80),  FTOFIX19_13(-16),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // top one way floor
    {&COLLISION_ONEWAY_7x7x1,       {FTOFIX19_13(56),   FTOFIX19_13(-40),   FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // bottom one way floor
    {&COLLISION_ONEWAY_7x7x1,       {FTOFIX19_13(56),   FTOFIX19_13(16),    FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // outermost left wall
    {&COLLISION_2x28x1,             {FTOFIX19_13(-184), FTOFIX19_13(0),     FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    // outermost right wall
    {&COLLISION_2x28x1,             {FTOFIX19_13(184),  FTOFIX19_13(0),     FTOFIX19_13(0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_INTERSECTION_ST_CHILDREN[] =
{
    // since these are always visible it doesn't matter that they are not logically placed in this definition

    {&MANAGED_ENTITY,               {FTOFIX19_13(192),  FTOFIX19_13(112),   FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LEVEL_1_INTERSECTION_MAIN_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(111),   FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LEVEL_1_INTERSECTION_MAIN_COLLISIONS, NULL, false},

    {&HERO_AC,                      {FTOFIX19_13(32),   FTOFIX19_13(159),   FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, false},

    {&DOOR_AG,                      {FTOFIX19_13(176),  FTOFIX19_13(47),    FTOFIX19_13(LAYER_0_DOORS)}, "UpperEntryDoor", NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(200),  FTOFIX19_13(44),    FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

    {&DOOR_AG,                      {FTOFIX19_13(32),   FTOFIX19_13(159),   FTOFIX19_13(LAYER_0_DOORS)}, "LowerEntryDoor", NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(56),   FTOFIX19_13(156),   FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

    {&SAW_BLADE_H8_AC,              {FTOFIX19_13(130),  FTOFIX19_13(174),   FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    {&TORCH_AG,                     {FTOFIX19_13(200),  FTOFIX19_13(156),   FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

    {&COIN_AG,                      {FTOFIX19_13(240),  FTOFIX19_13(104),    FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, (void*)46, false},
    {&COIN_AG,                      {FTOFIX19_13(256),  FTOFIX19_13(104),    FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, (void*)47, false},

    {&TORCH_AG,                     {FTOFIX19_13(328),  FTOFIX19_13(44),    FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
    {&DOOR_AG,                      {FTOFIX19_13(352),  FTOFIX19_13(47),    FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, (void*)&LEVEL_1_MAIN_INTERSECTION_EXIT_DOOR_EP, false},

    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_INTERSECTION_ST_UI_CHILDREN[] =
{
    {&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(215), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},

    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef* const LEVEL_1_INTERSECTION_ST_CHARSETS[] =
{
	&PLATFORMER_DEFAULT_FONT_CH,
	&PLATFORMER_GUI_FONT_CH,

	&LEVEL_1_INTERSECTION_BACK_CH,
	&LEVEL_1_INTERSECTION_MAIN_BACK_CH,
	&LEVEL_1_INTERSECTION_MAIN_CH,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//                                             STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------



StageROMDef LEVEL_1_INTERSECTION_ST =
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
                2,
                // medium red
                4,
                // bright red
                8,
            },

            // brightness repeat
            (BrightnessRepeatDefinition*)&EDGE_FADE_OUT_BRIGHTNESS_REPEAT,
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
        // char sets to preload
        (CharSetDefinition**)LEVEL_1_INTERSECTION_ST_CHARSETS,

        // textures to preload
        (StageTextureEntryDefinition*)NULL,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // entities
    {
        // ui
        {
            LEVEL_1_INTERSECTION_ST_UI_CHILDREN,
            __TYPE(UI),
        },

        // children
        LEVEL_1_INTERSECTION_ST_CHILDREN,
    },
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_INTERSECTION_MAIN_EP[] =
{{
    // the stage to load
    (StageDefinition*)&LEVEL_1_INTERSECTION_ST,

    // name of the entity to start at
    "UpperEntryDoor",

    // offset from entry point (x, y, z)
    {0, 0, FTOFIX19_13(-SORT_INCREMENT)},
}};

StageEntryPointROMDef LEVEL_1_INTERSECTION_LOWER_EP[] =
{{
    // the stage to load
    (StageDefinition*)&LEVEL_1_INTERSECTION_ST,

    // name of the entity to start at
    "LowerEntryDoor",

    // offset from entry point (x, y, z)
    {0, 0, FTOFIX19_13(-SORT_INCREMENT)},
}};
