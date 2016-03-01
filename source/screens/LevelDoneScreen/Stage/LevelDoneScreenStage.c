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
#include <objects.h>
#include <macros.h>
#include <LevelDoneScreenState.h>
#include <screens.h>
#include <VPUManager.h>


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
//---------------------------------------------------------------------------------------------------------

// Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
// know that it must stop reading the stage's/ui's textures and entities.

PositionedEntityROMDef LEVEL_DONE_SCREEN_ST_CHILDREN[] =
{
    {&COIN_AG,      {FTOFIX19_13(164),  FTOFIX19_13(108),   FTOFIX19_13(LAYER_0_ITEMS)},    NULL, NULL, NULL, true},
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef LEVEL_DONE_SCREEN_ST_UI_CHILDREN[] =
{
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_DONE_SCREEN_ST =
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
        // number of segments reserved for dynamically allocated textures when preloading
        1,

    	// OBJs segments sizes (must total 1024)
        {
            // SPT0
        	__AVAILABLE_CHAR_OBJECTS / 4,
            // SPT1
        	__AVAILABLE_CHAR_OBJECTS / 4,
            // SPT2
        	__AVAILABLE_CHAR_OBJECTS / 4,
            // SPT3
        	__AVAILABLE_CHAR_OBJECTS / 4,
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
    	    ITOFIX19_13(0),
    	    ITOFIX19_13(0)
        },

        // friction
        FTOFIX19_13(0),
    },

    // assets
    {
        // char sets to preload
        (CharSetDefinition**)NULL,

        // textures to preload
        (StageTextureEntryDefinition*)NULL,

        // background music
        NULL,
    },

    // entities
    {
        // UI
        {
        	LEVEL_DONE_SCREEN_ST_UI_CHILDREN,
            __TYPE(UI),
        },

        // children
        LEVEL_DONE_SCREEN_ST_CHILDREN,
    }
};
