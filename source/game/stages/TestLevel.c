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
#include <PlatformerLevelState.h>
#include <I18n.h>
#include <text.h>

#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 											    PROTOTYPES
//---------------------------------------------------------------------------------------------------------

StageROMDef TEST_LEVEL_ST;


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LAYER_0_FLOOR	196
#define LAYER_1_FLOOR	196 - 16
#define LAYER_2_FLOOR	196 - 32
#define LAYER_3_FLOOR	196 - 64

#define LEVEL_X_SIZE 	3000
#define LEVEL_Y_SIZE 	2000
#define LEVEL_Z_SIZE 	2000

#define SCREEN_X_POSITION 		0
#define SCREEN_Y_POSITION 		LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 		0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

PositionedEntityROMDef TEST_LEVEL_ST_ENTITIES[] = {

	// since these are always visible
	// it doesn't matter that they are not logically
	// placed in this definition
	//{&TREE_BG_BACK_SB,	 	{SCREEN_X_POSITION, SCREEN_Y_POSITION + 102, LAYER_4}, NULL},
	//{&TREE_BG_FRONT_SB, 	{SCREEN_X_POSITION, SCREEN_Y_POSITION + 168, LAYER_3}, NULL},
	{&TEST_BG,		{SCREEN_X_POSITION + 72, SCREEN_Y_POSITION + LAYER_0_FLOOR, PLAYABLE_LAYER_0 + 2}, NULL, NULL},
	{NULL, {0,0,0}, NULL, NULL},
};

PositionedEntityROMDef TEST_LEVEL_ST_UI_ENTITIES[] =
{
	{NULL, {0,0,0}, NULL, NULL}
};

TextureROMDef* TEST_LEVEL_ST_TEXTURES[] =
{
	//&TREE_BG_FRONT_TX,
	//&TREE_BG_BACK_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TEST_LEVEL_ST =
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

    //initial screen position
    {
        // x
        ITOFIX19_13(SCREEN_X_POSITION),
        // y
        ITOFIX19_13(SCREEN_Y_POSITION),
        // z
        ITOFIX19_13(SCREEN_Z_POSITION)
    },

    //textures to preload
    (TextureDefinition**)TEST_LEVEL_ST_TEXTURES,

    //UI
    {
        TEST_LEVEL_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    //entities
    TEST_LEVEL_ST_ENTITIES,

    //background music
    NULL,
    //(const u16 (*)[])WORLD_0_0_0_BGM,

    //identifier
    "0-0",

    //name
    "Test Level",
};