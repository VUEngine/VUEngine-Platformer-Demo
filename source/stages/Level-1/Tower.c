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
#include <VPUManager.h>

#include <objects.h>
#include <sound.h>


//---------------------------------------------------------------------------------------------------------
// 											    DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern PlatformerStageEntryPointROMDef LEVEL_1_MAIN_TOWER_EP;

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
    {&LEVEL_1_TOWER_MAIN_1_IM,      {FTOFIX19_13(1), 	FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},
	{&DOOR_AG,	            		{FTOFIX19_13(-144), FTOFIX19_13(159), 	FTOFIX19_13(0)}, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_TOWER_EP, false},
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
	{&COLLISION_32x4x1,				{FTOFIX19_13(32),   FTOFIX19_13(-97),   FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // 3rd level floor right
	{&COLLISION_48x4x1,				{FTOFIX19_13(-80),  FTOFIX19_13(-177),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // 4th level floor left
	{&COLLISION_48x2x1,				{FTOFIX19_13(-82),  FTOFIX19_13(-247),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floor below spikes
	{&COLLISION_14x6x1,				{FTOFIX19_13(-136), FTOFIX19_13(-216),  FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // left wall below spikes

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_2_ENTITIES[] =
{
    {&LEVEL_1_TOWER_MAIN_2_IM,      {FTOFIX19_13(0), 	FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},

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

PositionedEntityROMDef LEVEL_1_TOWER_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&LEVEL_1_TOWER_MAIN_BACK_IM,  	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	{&HERO_AC, 						{FTOFIX19_13(72), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 128), 	FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, true},
    {&LAVA_IG,		        		{FTOFIX19_13(190), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT + 80), 	FTOFIX19_13(LAYER_0)}, "Lava", (struct PositionedEntity*)LAVA_CHILD_ENTITIES, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

    // part 1
    {&MANAGED_ENTITY,               {FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 256),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 256),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_1, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 256),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS_2, NULL, false},

	{&COLLISION_16x2x1,				{FTOFIX19_13(352),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 296), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // small stone right under 3rd

	{&LAVA_TRIGGER_IG,  			{FTOFIX19_13(174),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 130), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COG_WHEEL_IM,	        		{FTOFIX19_13(384),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 224), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(132),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 47", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(148),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 48", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(164), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 49", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(180), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 50", NULL, NULL, false},

	{&GRASS_AG, 					{FTOFIX19_13(324), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 121), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(264), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 204), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 51", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(280), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 204), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 52", NULL, NULL, false},

	{&SNAIL_8_AC, 					{FTOFIX19_13(132),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 248), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(60),  	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 296), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    {&BANDANA_AG, 					{FTOFIX19_13(296), 	    FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 318), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 53", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(296 + 16), FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 318), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 54", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(296 + 32), FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 318), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 55", NULL, NULL, false},

	{&SAW_BLADE_H8_AC, 				{FTOFIX19_13(200),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 370), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},
	{&SAW_BLADE_H8_AC, 				{FTOFIX19_13(224),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 450), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(120),   FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 464), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 57", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(136),   FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 464), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 56", NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(336),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 424), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    // part 2
    {&MANAGED_ENTITY,               {FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 768),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_ENTITIES, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 768),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_1, NULL, false},
    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 768),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_2, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(192 - 24 - 80), FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 600 -56+32), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 58", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(192 - 8 - 80), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 600 -56+32), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 59", NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(192 - 24), FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 600 -56), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 60", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(192 - 8), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 600 -56), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 61", NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(192 - 24 + 80), FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 600 -56-32), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 62", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(192 - 8 + 80), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 600 -56-32), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 63", NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(336),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 752),    FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(112),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 848),    FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(40), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 944), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 64", NULL, NULL, false},
	{&GOAL_DOOR_AG, 				{FTOFIX19_13(208), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 946), 	FTOFIX19_13(LAYER_0_DOORS)}, NULL, NULL, NULL, false},

    {&COLLISIONS_CONTAINER_ENTITY,	{FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 768),    FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_2_COLLISIONS_3, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_ST_UI_CHILDREN[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(216), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

CharSetROMDef* LEVEL_1_TOWER_ST_CHARSETS[] =
{
	&LEVEL_1_TOWER_BACK_1_CH,
	&LEVEL_1_TOWER_MAIN_BACK_CH,
	&LEVEL_1_TOWER_MAIN_CH,
	NULL
};

StageTextureEntryROMDef LEVEL_1_TOWER_ST_TEXTURES[] =
{
	{&LEVEL_1_TOWER_BACK_1_TX, true},
	{&LEVEL_1_TOWER_MAIN_BACK_1_TX, true},
	{&LEVEL_1_TOWER_MAIN_1_TX, true},
	{&LEVEL_1_TOWER_MAIN_1_TX, false},
	{&LEVEL_1_TOWER_MAIN_BACK_1_TX, false},
	{&DOOR_TX, false},
	{&GUI_TX, false},
	{&LAVA_TX, false},
	{&LAVA_TOP_TX, false},
	{&COG_WHEEL_TX, false},
	{NULL, false}
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_TOWER_ST =
{
    {
    	// level
		{
	        // size
	        {
	            // x
	            384,
	            // y
	            LEVEL_1_TOWER_HEIGHT,
	            // z
	            256
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
    		// delay per cycle
    		15,
    		// load padding
    		40,
    		// unload padding
    		16,
    		// streaming amplitude
    		24,
    	},
    	
    	// rendering
    	{
    		// number of cycles the texture writing is idle
    		__TARGET_FPS / 10,
    		
    		// maximum number of texture's rows to write each time the 
    		// texture writing is active
    		12,
    		
            // Palette's config
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
            // number of segments reserved for dynamically allocated textures when preloading
            6,

        	// OBJs segments sizes (must total 1024)
            {
                // SPT0
            	__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
                // SPT1
            	__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
                // SPT2
            	__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
                // SPT3
            	__AVAILABLE_CHAR_OBJECTS / __TOTAL_OBJECT_SEGMENTS,
            },
            
            // OBJs segments z coordinates
            // Note that each SPT's z coordinate much be larger than or equal to the previous one's,
            // since the VIP renders OBJ Worlds in reverse order (SPT3 to SPT0)
            {
                // SPT0
                FTOFIX19_13(LAYER_0_PARTICLES),
                // SPT1
                FTOFIX19_13(LAYER_0_PARTICLES),
                // SPT2
                FTOFIX19_13(LAYER_0_PARTICLES),
                // SPT3
                FTOFIX19_13(20),
            },

            // optical configuration values
            {
        		// maximum view distance's power into the horizon
        		__MAXIMUM_VIEW_DISTANCE_POWER + 1,
                // distance of the eyes to the screen
                ITOFIX19_13(__DISTANCE_EYE_SCREEN),
                // distance from left to right eye (depth sensation)
                ITOFIX19_13(__BASE_FACTOR),
                // horizontal View point center
                ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
                // vertical View point center
                ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER + __VERTICAL_VIEW_POINT_CENTER/2),
            },            
    	},

        //physics
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
	        // UI
	        {
	            LEVEL_1_TOWER_ST_UI_CHILDREN,
	            __TYPE(UI),
	        },
	
	        // children
	        LEVEL_1_TOWER_ST_CHILDREN,
        }
    },

    // identifier
    "1-1",

    // name
    NULL,
};	


//---------------------------------------------------------------------------------------------------------
// 												ENTRY POINTS
//---------------------------------------------------------------------------------------------------------

PlatformerStageEntryPointROMDef LEVEL_1_TOWER_MAIN_EP[] =
{{
	// the stage to load
    (PlatformerStageDefinition*)&LEVEL_1_TOWER_ST,

	// name of the entity to start at
    //"EntryDoor",
    "Coin 64",

    // offset from entry point (x, y, z)
    {FTOFIX19_13(16), FTOFIX19_13(-10), FTOFIX19_13(-SORT_INCREMENT)},

	// does a level start at this entry point?
	false,
}};