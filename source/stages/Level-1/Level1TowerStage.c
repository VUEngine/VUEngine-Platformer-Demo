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
#include <Languages.h>
#include <VIPManager.h>

#include <objects.h>
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
// 											    DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageEntryPointROMDef LEVEL_1_MAIN_TOWER_EP;
extern BrightnessRepeatROMDef EDGE_FADE_OUT_BRIGHTNESS_REPEAT;
extern EntityDefinition MANAGED_ENTITY;
extern EntityDefinition COLLISIONS_CONTAINER_ENTITY;


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_1_TOWER_HEIGHT 	1024
#define SCREEN_Y_POSITION 		LEVEL_1_TOWER_HEIGHT - __SCREEN_HEIGHT


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LAVA_CHILD_ENTITIES[] =
{
	{&LAVA_TOP_AG, 					{FTOFIX19_13(0), 	FTOFIX19_13(-114), 	FTOFIX19_13(-1)}, NULL, NULL, NULL, false},
    {NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_1_ENTITIES[] =
{
    {&LEVEL_1_TOWER_MAIN_1_IM,      {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},
//	{&DOOR_AG,	            		{FTOFIX19_13(-144), FTOFIX19_13(159), 	FTOFIX19_13(0)}, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_TOWER_EP, false},
	{&DOOR_AG,	            		{FTOFIX19_13(-144), FTOFIX19_13(159), 	FTOFIX19_13(0)}, "EntryDoor", NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(-107), FTOFIX19_13(136), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(12), 	FTOFIX19_13(136), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_1_COLLISIONS_1[] =
{
	{&COLLISION_2x64x1,	    		{FTOFIX19_13(-184), FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // outer left wall
	{&COLLISION_2x64x1,	    		{FTOFIX19_13(184),  FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // outer right wall
	{&COLLISION_48x28x1,			{FTOFIX19_13(-128), FTOFIX19_13(288), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // bottom left floor
	{&COLLISION_48x28x1,			{FTOFIX19_13(302),  FTOFIX19_13(256), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // bottom right floor
	{&COLLISION_4x8x1,				{FTOFIX19_13(160),  FTOFIX19_13(144), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // step stone bottom right
	{&COLLISION_4x2x1,				{FTOFIX19_13(80),   FTOFIX19_13(72), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floating stone

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_1_COLLISIONS_2[] =
{
	{&COLLISION_48x4x1,				{FTOFIX19_13(-172), FTOFIX19_13(32), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // 2nd level floor left
	{&COLLISION_32x4x1,				{FTOFIX19_13(32),   FTOFIX19_13(-96),   FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // 3rd level floor right
	{&COLLISION_16x2x1,				{FTOFIX19_13(160),  FTOFIX19_13(-40), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // small stone right under 3rd
	{&COLLISION_48x4x1,				{FTOFIX19_13(-80),  FTOFIX19_13(-176),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // 4th level floor left
	{&COLLISION_48x2x1,				{FTOFIX19_13(-82),  FTOFIX19_13(-248),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floor below spikes
	{&COLLISION_14x6x1,				{FTOFIX19_13(-136), FTOFIX19_13(-216),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // left wall below spikes

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_2_COLLISIONS_1[] =
{
	{&COLLISION_2x64x1,	    		{FTOFIX19_13(-184), FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // outer left wall
	{&COLLISION_2x64x1,	    		{FTOFIX19_13(184),  FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // outer right wall
	{&COLLISION_6x4x1,	    		{FTOFIX19_13(-104), FTOFIX19_13(256), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // block between spikes left
	{&COLLISION_4x4x1,	    		{FTOFIX19_13(-16),  FTOFIX19_13(256), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // block between spikes middle
	{&COLLISION_8x4x1,	    		{FTOFIX19_13(78),   FTOFIX19_13(256), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // block between spikes right
	{&HIT_COLLISION_20x2x1,         {FTOFIX19_13(-104), FTOFIX19_13(256),   FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // spikes
	{&HIT_COLLISION_20x2x1,         {FTOFIX19_13(-16),  FTOFIX19_13(256),   FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // spikes

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_2_COLLISIONS_2[] =
{
	{&COLLISION_4x2x1,				{FTOFIX19_13(-176), FTOFIX19_13(200), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // stepstone left
	{&COLLISION_4x2x1,				{FTOFIX19_13(-96),  FTOFIX19_13(168), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floating stone 1
	{&COLLISION_4x2x1,				{FTOFIX19_13(-16),  FTOFIX19_13(136),   FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floating stone 2
	{&COLLISION_4x2x1,				{FTOFIX19_13(64),   FTOFIX19_13(104), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floating stone 3
	{&COLLISION_16x2x1,				{FTOFIX19_13(192),  FTOFIX19_13(72), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // stepstone right
	{&COLLISION_48x4x1,				{FTOFIX19_13(-80),  FTOFIX19_13(-16),   FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floor above floating platforms

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_2_COLLISIONS_3[] =
{
	{&COLLISION_ONEWAY_7x7x1,		{FTOFIX19_13(-80),  FTOFIX19_13(-132),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top room one way
	{&COLLISION_48x4x1,				{FTOFIX19_13(144),  FTOFIX19_13(-144),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top room right floor
	{&COLLISION_8x20x1,				{FTOFIX19_13(-144), FTOFIX19_13(-80),   FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top room left floor
	{&COLLISION_48x2x1,				{FTOFIX19_13(0),    FTOFIX19_13(-232),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top room ceiling
	{&COLLISION_4x8x1,				{FTOFIX19_13(80),   FTOFIX19_13(-192),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // top room right wall

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											ENTITY LISTS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef LEVEL_1_TOWER_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&LEVEL_1_TOWER_MAIN_BACK_IM,  	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT), 	        FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	{&HERO_AC, 						{FTOFIX19_13(72), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 128), 	FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, true},
    {&LAVA_IG,		        		{FTOFIX19_13(190), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT + 80), 	FTOFIX19_13(LAYER_0)}, "Lava", (struct PositionedEntity*)LAVA_CHILD_ENTITIES, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

    // part 1
    {&MANAGED_ENTITY,               {FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 256),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 257),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_1, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 257),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_2, NULL, false},

	{&LAVA_TRIGGER_IG,  			{FTOFIX19_13(174),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 130), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COG_WHEEL_IM,	        		{FTOFIX19_13(350),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 208), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(132),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 48", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(148),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 49", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(164), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 50", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(180), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 51", NULL, NULL, false},

	{&GRASS_AG, 					{FTOFIX19_13(324), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 121), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(264), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 204), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 52", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(280), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 204), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 53", NULL, NULL, false},

	{&SNAIL_8_AC, 					{FTOFIX19_13(132),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 248), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(60),  	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 296), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    {&BANDANA_AG, 					{FTOFIX19_13(296), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 317), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(312),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 317), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 54", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(328),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 317), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 55", NULL, NULL, false},

	{&SAW_BLADE_H8_AC, 				{FTOFIX19_13(200),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 370), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_H8_AC, 				{FTOFIX19_13(224),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 450), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(120),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 464), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 56", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(136),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 464), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 57", NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(336),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 424), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    // part 2
    {&LEVEL_1_TOWER_MAIN_2_IM,      {FTOFIX19_13(192), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 768), 	FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, NULL, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 769),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_1, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 769),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_2, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(88),   FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 623), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 58", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(104), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 623), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 59", NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(168),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 655), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 60", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(184), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 655), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 61", NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(248),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 687), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 62", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(264), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 687), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 63", NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(336),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 751),    FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

	{&SNAIL_8_AC, 					{FTOFIX19_13(210),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 808), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(112),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 844),    FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(40), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 942), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 64", NULL, NULL, false},
	{&GOAL_DOOR_AG, 				{FTOFIX19_13(208), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 944), 	FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(176), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 952), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(240), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 952), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},

    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 770),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_3, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(215), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											PRELOAD LISTS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef* const LEVEL_1_TOWER_ST_CHARSETS[] =
{
	&LEVEL_1_TOWER_BACK_1_CH,
	&LEVEL_1_TOWER_MAIN_BACK_CH,
	&LEVEL_1_TOWER_MAIN_CH,
	NULL
};

StageTextureEntryROMDef LEVEL_1_TOWER_ST_TEXTURES[] =
{
	{&COG_WHEEL_TX, false},
	{&LEVEL_1_TOWER_BACK_1_TX, false},
	{&LEVEL_1_TOWER_MAIN_BACK_1_TX, true},
	{&LEVEL_1_TOWER_MAIN_1_TX, true},
	{&LEVEL_1_TOWER_MAIN_1_TX, false},
	{&LEVEL_1_TOWER_MAIN_BACK_1_TX, false},
	{&DOOR_TX, false},
	{&GUI_TX, false},
	{&LAVA_TX, false},
	{&LAVA_TOP_TX, false},
	{NULL, false}
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_TOWER_ST =
{
    // level
    {
        // size
        {
            // x
            __SCREEN_WIDTH,
            // y
            LEVEL_1_TOWER_HEIGHT,
            // z
            __SCREEN_DEPTH,
        },

        // screen's initial position inside the game world
        {
            // x
            ITOFIX19_13(0),
            // y
            ITOFIX19_13(SCREEN_Y_POSITION - __SCREEN_HEIGHT / 2),
            // z
            ITOFIX19_13(0)
        },
    },

    // streaming
    {
        // load padding
        120,
        // unload padding
        32,
        // streaming amplitude
        28,
		// particle removel delay cycles
		0,
    },

    // rendering
    {
        // number of cycles the texture writing is idle
        __TARGET_FPS / 10,

        // maximum number of texture's rows to write each time the texture writing is active
        16,

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
        2,

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
            // horizontal View point center
            ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
            // vertical View point center
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
        (CharSetDefinition**)LEVEL_1_TOWER_ST_CHARSETS,

        // textures to preload
        (StageTextureEntryDefinition*)LEVEL_1_TOWER_ST_TEXTURES,

        // background music
        (const u16 (*)[])KRISSE_BGM,
    },

    // entities
    {
        // ui
        {
            LEVEL_1_TOWER_ST_UI_CHILDREN,
            __TYPE(UI),
        },

        // children
        LEVEL_1_TOWER_ST_CHILDREN,
    },
};


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

StageEntryPointROMDef LEVEL_1_TOWER_MAIN_EP[] =
{{
	// the stage to load
    (StageDefinition*)&LEVEL_1_TOWER_ST,

	// name of the entity to start at
    "EntryDoor",

    // offset from entry point (x, y, z)
    {FTOFIX19_13(0), FTOFIX19_13(-10), FTOFIX19_13(-SORT_INCREMENT)},
}};
