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
#include <objects.h>
#include <macros.h>
#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

PositionedEntityROMDef TITLE_ST_UI_ENTITIES[] =
{

	{&VBJAENGINE_IM, 	{__SCREEN_WIDTH >> 1, 	 	62, 	LAYER_0			}, NULL},			
	{&SUPER_AWESOME_IM, {__SCREEN_WIDTH >> 1, 	 	80, 	LAYER_0 - 16	}, NULL},			
	{&LOGO_IM, 			{__SCREEN_WIDTH >> 1, 		104, 	LAYER_0			}, NULL},			
	{&HERO_IM, 			{__SCREEN_WIDTH >> 1, 		172, 	LAYER_0 - 1		}, NULL},
	{&FLOOR_16x8_BG, 	{__SCREEN_WIDTH >> 1,		214, 	LAYER_0			}, NULL},
	{NULL,{0,0,0}, NULL},
};

PositionedEntityROMDef TITLE_ST_ENTITIES[] =
{

	{&VBJAENGINE_BG_SB, {0, __SCREEN_HEIGHT >> 1, LAYER_0 + 32}, NULL},
	{NULL,{0,0,0}, NULL},
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TITLE_ST =
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
    //initial screen position
    {
        // x
        ITOFIX19_13(0),
        // y
        ITOFIX19_13(0),
        //z
        ITOFIX19_13(__ZZERO)
    },
    //textures to preload
    NULL,
    //UI entities
    {
        TITLE_ST_UI_ENTITIES,
        __TYPE(UI),
    },
    //entities
    TITLE_ST_ENTITIES,

    //background music
    NULL,

    //identifier
    NULL,

    //name
    NULL,
};