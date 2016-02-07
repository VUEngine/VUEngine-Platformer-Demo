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
#include <VPUManager.h>

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
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(-30),  FTOFIX19_13(-23), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // left
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(5),    FTOFIX19_13(-12), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // middle
	{&MOUND_BG_CASTLE_FLAG_AG, 	{FTOFIX19_13(40),   FTOFIX19_13(-23), FTOFIX19_13(0)}, NULL, NULL, NULL, true}, // right
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TITLE_SCREEN_ST_CHILDREN[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_IM,		{FTOFIX19_13(0),    FTOFIX19_13(-24), 	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},
	{&CLOUDS_IM,			{FTOFIX19_13(0),    FTOFIX19_13(104), 	FTOFIX19_13(LAYER_4)}, NULL, NULL, NULL, true},
	{&MOUND_BG_FRONT_IM,	{FTOFIX19_13(0),    FTOFIX19_13(136), 	FTOFIX19_13(LAYER_3)}, NULL, NULL, NULL, true},

	{&MOUND_BG_CASTLE_IM, 	{FTOFIX19_13(338),  FTOFIX19_13(77), 	FTOFIX19_13(LAYER_3)}, NULL, (struct PositionedEntity*)CASTLE_CHILD_ENTITIES, NULL, true},

	{&STAR_AG, 	            {FTOFIX19_13(344),  FTOFIX19_13(-80), 	FTOFIX19_13(LAYER_5)}, NULL, NULL, NULL, true},

	{&FLOOR_16x12_IG,		{FTOFIX19_13(-16),  FTOFIX19_13(208), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&FLOOR_4x12_IG,		{FTOFIX19_13(64),   FTOFIX19_13(192), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&FLOOR_22x5_IG,		{FTOFIX19_13(192),  FTOFIX19_13(188), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&FLOOR_16x12_IG,		{FTOFIX19_13(360),  FTOFIX19_13(200), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	{&COLLISION_2x28x1, 	{FTOFIX19_13(92),   FTOFIX19_13(112), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&COLLISION_2x28x1, 	{FTOFIX19_13(292),  FTOFIX19_13(112), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	{&HERO_AC, 				{FTOFIX19_13(192),  FTOFIX19_13(157), 	FTOFIX19_13(LAYER_0)}, HERO_NAME, NULL, NULL, true},

	{&GRASS_AG,      	    {FTOFIX19_13(34),   FTOFIX19_13(153), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&BUSH_AG,      	    {FTOFIX19_13(366),  FTOFIX19_13(148), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&FENCE_IM,      	    {FTOFIX19_13(322),  FTOFIX19_13(145), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&FENCE_IM,      	    {FTOFIX19_13(339),  FTOFIX19_13(145), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	{&COIN_AG, 		        {FTOFIX19_13(57),   FTOFIX19_13(134), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},
	{&COIN_AG, 		        {FTOFIX19_13(71),   FTOFIX19_13(134), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	{&VBJAENGINE_IM,        {FTOFIX19_13(192),  FTOFIX19_13(10), 	FTOFIX19_13(LAYER_1)}, NULL, NULL, NULL, true},
	{&LOGO_IM, 			    {FTOFIX19_13(192),  FTOFIX19_13(64), 	FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL, true},

	// samples of ignored entities
	{&COIN_AG, 		        {FTOFIX19_13(57), 	FTOFIX19_13(108), 	FTOFIX19_13(0)}, "IgnoreMeCoin", NULL, NULL, true},
	{&DOOR_AG,				{FTOFIX19_13(192), 	FTOFIX19_13(152), 	FTOFIX19_13(0)}, "IgnoreMeDoor", NULL, NULL, true},

	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef TITLE_SCREEN_ST_UI_CHILDREN[] =
{
	{&GUI_BLANK_IM,			{FTOFIX19_13(192), 	FTOFIX19_13(208), 	FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&GUI_BLANK_IM,			{FTOFIX19_13(192), 	FTOFIX19_13(216), 	FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
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
		0,
		
		// maximum number of texture's rows to write each time the texture writing is active
		64,
		
		// maximum number of rows to compute on each call to the affine functions
		16,

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
        	__AVAILABLE_CHAR_OBJECTS,
            // SPT1
        	0,
            // SPT2
        	0,
            // SPT3
        	0,
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
        NULL,

        // textures to preload
        (StageTextureEntryDefinition*)TITLE_SCREEN_ST_TEXTURES,
        
        // background music
        (const u16 (*)[])WORLD_0_0_0_BGM,
    },

    // entities
    {
        // UI
        {
        	TITLE_SCREEN_ST_UI_CHILDREN,
            __TYPE(UI),
        },

        // children
        TITLE_SCREEN_ST_CHILDREN,
    },
};