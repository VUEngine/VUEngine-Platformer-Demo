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
#include <LevelSelectorScreenState.h>
#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_X_SIZE 	    __SCREEN_WIDTH
#define LEVEL_Y_SIZE 	    __SCREEN_HEIGHT
#define LEVEL_Z_SIZE 	    __SCREEN_WIDTH

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 	0

#define START_LAYER			0
#define HERO_LAYER			START_LAYER + 32
#define DOORS_LAYER			HERO_LAYER	+ 32
#define END_LAYER			DOORS_LAYER + 16


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

PositionedEntityROMDef LEVEL_SELECTOR_ST_ENTITIES[] = {

	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&HERO_MC, 				{SCREEN_X_POSITION + __SCREEN_WIDTH / 2, SCREEN_Y_POSITION + 60, HERO_LAYER}, NULL},
	// bottom
	{&COLLISION_48x2x48, 	{SCREEN_X_POSITION + __SCREEN_WIDTH / 2, SCREEN_Y_POSITION + __SCREEN_HEIGHT - 2 * 8, START_LAYER}, NULL},
	// left
	{&COLLISION_2x28x48, 	{SCREEN_X_POSITION + 16, SCREEN_Y_POSITION + __SCREEN_HEIGHT / 2, START_LAYER}, NULL},
	// right
	{&COLLISION_2x28x48, 	{SCREEN_X_POSITION + __SCREEN_WIDTH - 16, SCREEN_Y_POSITION + __SCREEN_HEIGHT / 2, START_LAYER}, NULL},
	// front
	{&COLLISION_48x28x2, 	{SCREEN_X_POSITION + __SCREEN_WIDTH / 2, SCREEN_Y_POSITION + __SCREEN_HEIGHT - 2 * 8, START_LAYER}, NULL},
	// back
	{&COLLISION_48x28x2, 	{SCREEN_X_POSITION + __SCREEN_WIDTH / 2, SCREEN_Y_POSITION + __SCREEN_HEIGHT - 2 * 8, END_LAYER}, NULL},

	{&DOOR_MC,				{SCREEN_X_POSITION + __SCREEN_WIDTH / 2 - 64, SCREEN_Y_POSITION + __SCREEN_HEIGHT - 2 * 8 - 3 * 8, DOORS_LAYER}, LevelSelectorScreenState_goToLevel1_1},
	{&DOOR_MC,				{SCREEN_X_POSITION + __SCREEN_WIDTH / 2, SCREEN_Y_POSITION + __SCREEN_HEIGHT - 2 * 8  - 3 * 8, DOORS_LAYER}, LevelSelectorScreenState_goToLevel1_2},
	{&DOOR_MC,				{SCREEN_X_POSITION + __SCREEN_WIDTH / 2 + 64, SCREEN_Y_POSITION + __SCREEN_HEIGHT - 2 * 8  - 3 * 8, DOORS_LAYER}, LevelSelectorScreenState_goToLevel1_3},
	{NULL, {0,0,0}, NULL},
};

PositionedEntityROMDef LEVEL_SELECTOR_ST_UI_ENTITIES[] =
{
	{NULL, {0,0,0}, NULL}
};

TextureROMDef* LEVEL_SELECTOR_ST_TEXTURES[] =
{
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_SELECTOR_ST =
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
    (TextureDefinition**)LEVEL_SELECTOR_ST_TEXTURES,

    //UI
    {
        LEVEL_SELECTOR_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    //entities
    LEVEL_SELECTOR_ST_ENTITIES,

    //background music
    NULL,
    //(const u16 (*)[])WORLD_0_0_0_BGM,

    //identifier
    NULL,

    //name
    NULL,
};