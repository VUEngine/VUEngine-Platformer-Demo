/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>
#include <VPUManager.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern TextureDefinition VBJAENGINE_BG_TX;
extern TextureDefinition VBJAENGINE_LOGO_3D_TX;
extern TextureDefinition VBJAENGINE_LOGO_OUTLINE_TX;

extern EntityDefinition VBJAENGINE_BG_SB;
extern EntityDefinition VBJAENGINE_LOGO_3D_IM;
extern EntityDefinition VBJAENGINE_LOGO_OUTLINE_IM;


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef VBJAENGINE_SCREEN_ST_UI_ENTITIES[] =
{
	{&VBJAENGINE_LOGO_3D_IM, 		{FTOFIX19_13((__SCREEN_WIDTH >> 1) - 6), 	FTOFIX19_13((__SCREEN_HEIGHT >> 1) - 4), 	FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{&VBJAENGINE_LOGO_OUTLINE_IM, 	{FTOFIX19_13((__SCREEN_WIDTH >> 1) + 5), 	FTOFIX19_13(__SCREEN_HEIGHT >> 1), 			FTOFIX19_13(0)}, NULL, NULL, NULL, true},
	{NULL,{0,0,0}, NULL, NULL, NULL, false},
};

PositionedEntityROMDef VBJAENGINE_SCREEN_ST_ENTITIES[] =
{
	{&VBJAENGINE_BG_SB, {FTOFIX19_13(0), FTOFIX19_13(__SCREEN_HEIGHT >> 1), FTOFIX19_13(64)}, NULL, NULL, NULL, true},
	{NULL,{0,0,0}, NULL, NULL, NULL, false},
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef VBJAENGINE_SCREEN_ST =
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
    		0xE4,
    		0xE0,
    		0xD0,
    		0xE0,
    	},
    	{
    		0xE4,
    		0xE0,
    		0xD0,
    		0xE0,
    	} 
    },

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
        //z
        ITOFIX19_13(__ZZERO)
    },

    // optical configuration values
    {
		// maximum view distance's power into the horizont
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
    
    // textures
    NULL,

    // UI entities
    {
        VBJAENGINE_SCREEN_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    // entities
    VBJAENGINE_SCREEN_ST_ENTITIES,

    // background music
    NULL,
};