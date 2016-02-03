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
#include <VPUManager.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

//extern TextureDefinition VBJAENGINE_BG_TX;
//extern TextureDefinition VBJAENGINE_LOGO_3D_TX;
//extern TextureDefinition VBJAENGINE_LOGO_OUTLINE_TX;

extern EntityDefinition VBJAENGINE_BG_IM;
extern EntityDefinition VBJAENGINE_LOGO_3D_IM;


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef VBJAENGINE_SCREEN_ST_UI_CHILDREN[] =
{
	{&VBJAENGINE_LOGO_3D_IM, 		{FTOFIX19_13((__SCREEN_WIDTH >> 1) - 6), 	FTOFIX19_13((__SCREEN_HEIGHT >> 1) - 4), 	FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{NULL,{0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef VBJAENGINE_SCREEN_ST_CHILDREN[] =
{
	{&VBJAENGINE_BG_IM, {FTOFIX19_13(0), FTOFIX19_13(__SCREEN_HEIGHT >> 1), FTOFIX19_13(64)}, NULL, NULL, NULL, true},
	{NULL,{0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef VBJAENGINE_SCREEN_ST =
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
            1
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
		
		// maximum number of texture's rows to write each time the 
		// texture writing is active
		64,
		
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
        	ITOFIX19_13(0), 
    		ITOFIX19_13(0), 
    		ITOFIX19_13(0), 
    		ITOFIX19_13(0)
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

    //physics
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
        NULL,

        // textures to preload
        NULL,
        
        // background music
        NULL,
    },

    // entities
    {
        // UI
        {
            VBJAENGINE_SCREEN_ST_UI_CHILDREN,
            __TYPE(UI),
        },

        // children
        VBJAENGINE_SCREEN_ST_CHILDREN,
    }		
};