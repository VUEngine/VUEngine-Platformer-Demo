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
#include <PauseScreenState.h>
#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 											    PROTOTYPES
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_X_SIZE 	    __SCREEN_WIDTH
#define LEVEL_Y_SIZE 	    __SCREEN_HEIGHT
#define LEVEL_Z_SIZE 	    __SCREEN_WIDTH

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	0
#define SCREEN_Z_POSITION 	0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

PositionedEntityROMDef PAUSE_SCREEN_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&LOGO_IM, 			    {FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(88), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL},
	{&VBJAENGINE_IM, 	    {FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(40), FTOFIX19_13(LAYER_0)}, NULL, NULL, NULL},
	{&SUPER_AWESOME_IM,     {FTOFIX19_13(__SCREEN_WIDTH >> 1), FTOFIX19_13(72), FTOFIX19_13(LAYER_0 - 16)}, NULL, NULL, NULL},

	{NULL, {0,0,0}, NULL, NULL, NULL},
};

PositionedEntityROMDef PAUSE_SCREEN_ST_UI_ENTITIES[] =
{
	{NULL, {0,0,0}, NULL, NULL, NULL},
};

TextureROMDef* PAUSE_SCREEN_ST_TEXTURES[] =
{
	&SUPER_AWESOME_TX,
	&VBJAENGINE_TX,
	&LOGO_L_TX,
	&LOGO_R_TX,
	&LOGO_OUTLINE_L_TX,
	&LOGO_OUTLINE_R_TX,
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef PAUSE_SCREEN_ST =
{
    // size
    {
        // x
        LEVEL_X_SIZE,
        // y
        LEVEL_Y_SIZE,
        // z
        LEVEL_Z_SIZE
    },

	// OBJs segments z coordinates
	// Note that each SPT's z coordinate much be larger than or equal to the previous one's,
	// since the VIP renders OBJ Worlds in reverse order (SPT3 to SPT0)
    {
        // SPT0
		ITOFIX19_13(0),
        // SPT1
		ITOFIX19_13(0),
        // SPT2
		ITOFIX19_13(0),
        // SPT3
    	ITOFIX19_13(0),
    },

    // initial screen position
    {
        // x
        ITOFIX19_13(SCREEN_X_POSITION),
        // y
        ITOFIX19_13(SCREEN_Y_POSITION),
        // z
        ITOFIX19_13(SCREEN_Z_POSITION)
    },

    // textures to preload
    (TextureDefinition**)PAUSE_SCREEN_ST_TEXTURES,

    // UI
    {
        PAUSE_SCREEN_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    // entities
    PAUSE_SCREEN_ST_ENTITIES,

    // background music
    NULL,
    //(const u16 (*)[])WORLD_0_0_0_BGM,

    // identifier
    "",

    // name
    "",
};