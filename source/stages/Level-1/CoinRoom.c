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

#include <objects.h>
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
//                                                 PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_SMALL_ROOM_LOWER_EP;

extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition COLLISIONS_CONTAINER_ENTITY;


//---------------------------------------------------------------------------------------------------------
//                                                 ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_1_COIN_ROOM_MAIN_ENTITIES[] =
{
    {&LEVEL_1_COIN_ROOM_MAIN_IM,    {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_COIN_ROOM_MAIN_COLLISIONS[] =
{
    {&COLLISION_48x2x1,             {FTOFIX19_13(0), 	FTOFIX19_13(-110),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top ceiling
    {&COLLISION_48x2x1,             {FTOFIX19_13(0), 	FTOFIX19_13(88), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // bottom floor
    {&COLLISION_2x28x1,             {FTOFIX19_13(-184), FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // left wall
    {&COLLISION_2x28x1,             {FTOFIX19_13(184), 	FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // right wall
    {&COLLISION_12x12x1,            {FTOFIX19_13(-208), FTOFIX19_13(-112),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top left block
    {&COLLISION_12x12x1,            {FTOFIX19_13(208), 	FTOFIX19_13(-112),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top right block
    {&COLLISION_12x12x1,            {FTOFIX19_13(-160), FTOFIX19_13(96), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // bottom left block
    {&COLLISION_12x12x1,            {FTOFIX19_13(160), 	FTOFIX19_13(96), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top right block

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_COIN_ROOM_ST_CHILDREN[] =
{
    // since these are always visible it doesn't matter that they are not logically placed in this definition
    {&MANAGED_ENTITY,               {FTOFIX19_13(192),  FTOFIX19_13(112),   FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LEVEL_1_COIN_ROOM_MAIN_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(111),   FTOFIX19_13(LAYER_0)}, NULL, (struct PositionedEntity*)LEVEL_1_COIN_ROOM_MAIN_COLLISIONS, NULL, false},

    {&HERO_AC,                      {FTOFIX19_13(44),  	FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, false},

    {&DOOR_AG,                      {FTOFIX19_13(42),  	FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_DOORS)}, "EntryDoor", NULL, NULL, false},
    {&DOOR_AG,                      {FTOFIX19_13(347), 	FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, (void*)&LEVEL_1_SMALL_ROOM_LOWER_EP, false},

    {&TORCH_AG,                     {FTOFIX19_13(64),  	FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(320), 	FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

    {&COIN_AG,                      {FTOFIX19_13(144),  FTOFIX19_13(112),  	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 27", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(144),  FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 28", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(144),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 29", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(144),  FTOFIX19_13(160), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 30", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(176),  FTOFIX19_13(112),  	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 31", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(176),  FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 32", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(176),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 33", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(176),  FTOFIX19_13(160), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 34", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(160),  FTOFIX19_13(176), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 35", NULL, NULL, false},

    {&COIN_AG,                      {FTOFIX19_13(208),  FTOFIX19_13(112),  	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 36", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(208),  FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 37", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(208),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 38", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(208),  FTOFIX19_13(160), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 39", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(208),  FTOFIX19_13(176), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 40", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(224),  FTOFIX19_13(112),  	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 41", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(224),  FTOFIX19_13(144), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 42", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(224),  FTOFIX19_13(176), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 43", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(240),  FTOFIX19_13(128), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 44", NULL, NULL, false},
    {&COIN_AG,                      {FTOFIX19_13(240),  FTOFIX19_13(160), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 45", NULL, NULL, false},

    {&SAW_BLADE_H8_AC,              {FTOFIX19_13(192),  FTOFIX19_13(191),   FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_COIN_ROOM_ST_UI_CHILDREN[] =
{
    {&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(217), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},

    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef* const LEVEL_1_COIN_ROOM_ST_CHARSETS[] =
{
	&LEVEL_1_COIN_ROOM_BACK_CH,
	&LEVEL_1_COIN_ROOM_MAIN_BACK_CH,
	&LEVEL_1_COIN_ROOM_MAIN_CH,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//                                             STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_COIN_ROOM_ST =
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
        // delay per cycle
        15,
        // load padding
        40,
        // unload padding
        16,
        // streaming amplitude
        24,
		// particle removel delay cycles
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

        // column table
		NULL,

        // palette's config
        {
            // background color
            __COLOR_BLACK,

            {
                __BGMAP_PALETTE_0,
                __BGMAP_PALETTE_1,
                __BGMAP_PALETTE_2,
                __BGMAP_PALETTE_3,
            },
            {
                __OBJECT_PALETTE_0,
                __OBJECT_PALETTE_1,
                __OBJECT_PALETTE_2,
                __OBJECT_PALETTE_3,
            }
        },

        // BGMAP segments configuration
        // number of segments reserved for the param table
        1,

        // OBJs segments sizes (must total 1024)
        {
            // __SPT0
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
            // __SPT1
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
            // __SPT2
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
            // __SPT3
            __AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
        },

        // OBJs segments z coordinates
        // Note that each SPT's z coordinate much be larger than or equal to the previous one's,
        // since the VIP renders OBJ Worlds in reverse order (__SPT3 to __SPT0)
        {
            // __SPT0
            FTOFIX19_13(LAYER_0_PARTICLES),
            // __SPT1
            FTOFIX19_13(LAYER_0_PARTICLES),
            // __SPT2
            FTOFIX19_13(LAYER_0_PARTICLES),
            // __SPT3
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
        (CharSetDefinition**)LEVEL_1_COIN_ROOM_ST_CHARSETS,

        // textures to preload
        (StageTextureEntryDefinition*)NULL,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // entities
    {
        // UI
        {
            LEVEL_1_COIN_ROOM_ST_UI_CHILDREN,
            __TYPE(UI),
        },

        // children
        LEVEL_1_COIN_ROOM_ST_CHILDREN,
    },
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_COIN_ROOM_MAIN_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_COIN_ROOM_ST,

	// name of the entity to start at
    "EntryDoor",

    // offset from entry point (x, y, z)
    {0, 0, FTOFIX19_13(-SORT_INCREMENT)},
}};
