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
#include <text.h>

#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LAYER_0_FLOOR	196
#define LAYER_1_FLOOR	196 - 16
#define LAYER_2_FLOOR	196 - 32
#define LAYER_3_FLOOR	196 - 64

#define LEVEL_X_SIZE 	384
#define LEVEL_Y_SIZE 	2000
#define LEVEL_Z_SIZE 	64

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 	0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

PositionedEntityROMDef LAVA_CHILD_ENTITIES[] =
{
	{&LAVA_TOP_MC, {48, -120, LAYER_1 - 16}, NULL, NULL},
	{&LAVA_TOP_MC, {0, -118, -1}, NULL, NULL},
    {NULL, {0,0,0}, NULL, NULL},
};

PositionedEntityROMDef LEVEL_1_3_PART_1_ENTITIES[] =
{
	{&COLLISION_48x2x48,	{0, 46, 0}, NULL, NULL},
	{&COLLISION_2x28x48,	{-186, 0, 0}, NULL, NULL},
	{&COLLISION_2x28x48,	{190, 0, 0}, NULL, NULL},
	{&DOOR_MC,	{-144, 20, 0}, NULL, NULL},
	{NULL, {0,0,0}, NULL, NULL},
};

PositionedEntityROMDef LEVEL_1_3_ROOM_1_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&HERO_MC, 				{SCREEN_X_POSITION + (__SCREEN_WIDTH >> 1), SCREEN_Y_POSITION + 20, PLAYABLE_LAYER_0}, NULL, NULL},
	{&STONE_BG_SB,	        {192, SCREEN_Y_POSITION - 24 + (__SCREEN_HEIGHT >> 1), LAYER_1 + 2}, NULL, NULL},
	{&LAVA_BG,		        {192, SCREEN_Y_POSITION + LAYER_0_FLOOR + 112, PLAYABLE_LAYER_0 - 2}, LAVA_CHILD_ENTITIES, NULL},

	// the following entities must be placed in logical (spatial) order,
	// according to the level's disposition, for the streaming to work properly
	// beware of edge case scenarios!
	{&LEVEL1_3_PART1_IM,    {192, SCREEN_Y_POSITION + (__SCREEN_HEIGHT >> 1), PLAYABLE_LAYER_0 + 2}, LEVEL_1_3_PART_1_ENTITIES, NULL},
	{NULL, {0,0,0}, NULL, NULL},
};

PositionedEntityROMDef LEVEL_1_3_ROOM_1_ST_UI_ENTITIES[] =
{
	{&GUI_IM, 				{__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT - 8, -4}, NULL, NULL},
	{NULL, {0,0,0}, NULL, NULL},
};

TextureROMDef* LEVEL_1_3_ROOM_1_ST_TEXTURES[] =
{
	&DOOR_TX,
	&GUI_TX,
	&FLOOR_16x8_L_TX,
	&FLOOR_16x8_R_TX,
	&LAVA_TX,
	&LAVA_TOP_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_3_ROOM_1_ST =
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
    (TextureDefinition**)LEVEL_1_3_ROOM_1_ST_TEXTURES,

    //UI
    {
        LEVEL_1_3_ROOM_1_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    //entities
    LEVEL_1_3_ROOM_1_ST_ENTITIES,

    //background music
    NULL,

    //identifier
    "1-3",

    //name
    (void*)STR_LEVEL_1_3_NAME,
};