/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Stage.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern EntityDefinition ADJUSTMENT_SCREEN_LOGO_IM;
extern EntityDefinition ADJUSTMENT_SCREEN_BG_IM;
extern EntityDefinition ADJUSTMENT_SCREEN_ICON_IM_L;
extern EntityDefinition ADJUSTMENT_SCREEN_ICON_IM_R;


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
//---------------------------------------------------------------------------------------------------------

PositionedEntityROMDef ADJUSTMENT_SCREEN_ST_ENTITIES[] =
{
	{&ADJUSTMENT_SCREEN_BG_IM, 		{ FTOFIX19_13(__SCREEN_WIDTH >> 1),   FTOFIX19_13(__SCREEN_HEIGHT >> 1), 	FTOFIX19_13(64)}, NULL, NULL, NULL},
	{&ADJUSTMENT_SCREEN_LOGO_IM,	{ FTOFIX19_13(__SCREEN_WIDTH >> 1),   				  FTOFIX19_13(104), 	FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&ADJUSTMENT_SCREEN_ICON_IM_L,	{					FTOFIX19_13(8),						FTOFIX19_13(8), 	FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&ADJUSTMENT_SCREEN_ICON_IM_L,	{   FTOFIX19_13(__SCREEN_WIDTH -8),	  FTOFIX19_13(__SCREEN_HEIGHT - 8), 	FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&ADJUSTMENT_SCREEN_ICON_IM_R,	{   FTOFIX19_13(__SCREEN_WIDTH -8),						FTOFIX19_13(8), 	FTOFIX19_13(0)}, NULL, NULL, NULL},
	{&ADJUSTMENT_SCREEN_ICON_IM_R,	{					FTOFIX19_13(8),	  FTOFIX19_13(__SCREEN_HEIGHT - 8), 	FTOFIX19_13(0)}, NULL, NULL, NULL},
	{NULL,{0,0,0}, NULL, NULL, NULL},
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef ADJUSTMENT_SCREEN_ST =
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
		// distance of the eyes to the screen
    	ITOFIX19_13(__DISTANCE_EYE_SCREEN),
		// maximum view distance into the horizont
		ITOFIX19_13(__MAXIMUM_VIEW_DISTANCE),
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
        NULL,
        NULL
    },

    // entities
    ADJUSTMENT_SCREEN_ST_ENTITIES,

    // background music
    NULL
};