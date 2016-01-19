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
// 											    PROTOTYPES
//---------------------------------------------------------------------------------------------------------

extern PlatformerStageEntryPointROMDef LEVEL_1_MAIN_TOWER_EP;


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_1_TOWER_HEIGHT 	5000
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
	{&DOOR_AG,	            		{FTOFIX19_13(-144), FTOFIX19_13(158), 	FTOFIX19_13(0)}, "EntryDoor", NULL, (void*)&LEVEL_1_MAIN_TOWER_EP, false},
    {&TORCH_AG,                     {FTOFIX19_13(-107), FTOFIX19_13(136), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},
    {&TORCH_AG,                     {FTOFIX19_13(12), 	FTOFIX19_13(136), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_MAIN_1_COLLISIONS[] =
{
	{&COLLISION_2x64x1,	    		{FTOFIX19_13(-184), FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // outer left wall
	{&COLLISION_48x28x1,			{FTOFIX19_13(302),  FTOFIX19_13(256), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // bottom right floor
	{&COLLISION_2x64x1,	    		{FTOFIX19_13(184),  FTOFIX19_13(0), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // outer right wall
	{&COLLISION_48x28x1,			{FTOFIX19_13(-128), FTOFIX19_13(288), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // bottom left floor
	{&COLLISION_4x2x1,				{FTOFIX19_13(88),   FTOFIX19_13(71), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // floating stone bottom right
	{&COLLISION_4x8x1,				{FTOFIX19_13(176),  FTOFIX19_13(144), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // step stone bottom right
	{&COLLISION_48x3x1,				{FTOFIX19_13(-172), FTOFIX19_13(28), 	FTOFIX19_13(0)}, NULL, NULL, NULL, false}, // 2nd level floor left

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition

	{&HERO_AC, 						{FTOFIX19_13(72), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 128), 	FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, true},
    {&LAVA_IG,		        		{FTOFIX19_13(190), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT + 64), 	FTOFIX19_13(LAYER_0)}, "Lava", (struct PositionedEntity*)LAVA_CHILD_ENTITIES, NULL, false},

	// the following entities must be placed in logical (spatial) order, according to the level's disposition,
	// for the streaming to work properly. beware of edge case scenarios!

    // part 1
    {(ManagedEntityDefinition*)&MANAGED_ENTITY, {FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 256),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_ENTITIES, NULL, false},
    {(EntityDefinition*)&ENTITY,                {FTOFIX19_13(192),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 256),   FTOFIX19_13(LAYER_0_FOREGROUND)}, NULL, (struct PositionedEntity*)LEVEL_1_TOWER_MAIN_1_COLLISIONS, NULL, false},

    {&MOVING_PLATFORM_V6_AC,        {FTOFIX19_13(60),  	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 288), 	FTOFIX19_13(LAYER_0_ENEMIES)}, NULL, NULL, NULL, false},

	{&LAVA_TRIGGER_IG,  			{FTOFIX19_13(174),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 130), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, false},
	{&COG_WHEEL_IG,	        		{FTOFIX19_13(384),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 224), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(132),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 030", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(148),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 031", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(164), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 032", NULL, NULL, false},
	{&COIN_AG, 						{FTOFIX19_13(180), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 92), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 033", NULL, NULL, false},

	{&GRASS_AG, 					{FTOFIX19_13(332), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 121), 	FTOFIX19_13(LAYER_0_BACKGROUND)}, NULL, NULL, NULL, false},

	{&COIN_AG, 						{FTOFIX19_13(280), 	FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 204), 	FTOFIX19_13(LAYER_0_ITEMS)}, "Coin 034", NULL, NULL, false},

	{&SNAIL_8_AC, 					{FTOFIX19_13(132),  FTOFIX19_13(LEVEL_1_TOWER_HEIGHT - 248), 	FTOFIX19_13(LAYER_0_ITEMS)}, NULL, NULL, NULL, false},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_1_TOWER_ST_UI_ENTITIES[] =
{
	{&GUI_AG, {FTOFIX19_13(192), FTOFIX19_13(216), FTOFIX19_13(-4)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

TextureROMDef* LEVEL_1_TOWER_ST_TEXTURES[] =
{
	//&COIN_TX,
	&DOOR_TX,
	&GUI_TX,
	&LAVA_TX,
	&LAVA_TOP_TX,
	&LEVEL_1_TOWER_MAIN_1_TX,
	&LEVEL_1_TOWER_MAIN_BACK_1_TX,
	&COG_WHEEL_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

PlatformerStageROMDef LEVEL_1_TOWER_ST =
{
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

        // streaming
    	{
    		// delay per cycle
    		8,
    		// load padding
    		64,
    		// unload padding
    		16,
    		// streaming amplitude
    		16,
    	},

    	// gravity
        {
            ITOFIX19_13(0),
            ITOFIX19_13(__GRAVITY),
            ITOFIX19_13(0)
        },

        // friction
        FTOFIX19_13(0.1f),

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
        1,

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

        // initial screen position
        {
            // x
            ITOFIX19_13(0),
            // y
            ITOFIX19_13(SCREEN_Y_POSITION - __SCREEN_HEIGHT / 2),
            // z
            ITOFIX19_13(0)
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

        // char sets to preload
        (CharSetDefinition**)NULL,

        // textures to preload
        (TextureDefinition**)LEVEL_1_TOWER_ST_TEXTURES,

        // UI
        {
            LEVEL_1_TOWER_ST_UI_ENTITIES,
            __TYPE(UI),
        },

        // entities
        LEVEL_1_TOWER_ST_ENTITIES,

        // background music
        NULL,
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
    "EntryDoor",

    // offset from entry point (x, y, z)
    {FTOFIX19_13(16), 0, FTOFIX19_13(-SORT_INCREMENT)},

	// does a level start at this entry point?
	false,
}};