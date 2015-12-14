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
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef EMPTY_ST_ENTITIES[] =
{
	{NULL, {0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef EMPTY_ST_UI_ENTITIES[] =
{
	{NULL, {0,0,0}, NULL, NULL, NULL, false}
};

TextureROMDef* EMPTY_ST_TEXTURES[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef EMPTY_ST =
{
    // size
    {
        // x
        __SCREEN_WIDTH,
        // y
        __SCREEN_HEIGHT,
        // z
        0,
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
	    ITOFIX19_13(0),
	    ITOFIX19_13(0)
    },

    // friction
    ITOFIX19_13(0),

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
    
    // OBJs segments z coordinates (SPT0 to SPT3)
    {
    	ITOFIX19_13(0),
		ITOFIX19_13(0),
		ITOFIX19_13(0),
		ITOFIX19_13(0)
    },

    // initial screen position
    {
        // x
        ITOFIX19_13(0),
        // y
        ITOFIX19_13(0),
        // z
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
		// horizontal View point center
		ITOFIX19_13(__HORIZONTAL_VIEW_POINT_CENTER),
		// vertical View point center
		ITOFIX19_13(__VERTICAL_VIEW_POINT_CENTER),
    },
    
    // char sets to preload
    (CharSetDefinition**)NULL,

    // textures to preload
    (TextureDefinition**)EMPTY_ST_TEXTURES,

    // UI
    {
        EMPTY_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    // entities
    EMPTY_ST_ENTITIES,

    // background music
    NULL,
};