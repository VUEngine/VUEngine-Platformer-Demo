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
#include <TitleScreenState.h>
#include "stages/textures.h"


//---------------------------------------------------------------------------------------------------------
// 											    PROTOTYPES
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_1_ROOM_1_ST;
StageROMDef LEVEL_1_2_ROOM_1_ST;
StageROMDef LEVEL_1_3_ROOM_1_ST;


//---------------------------------------------------------------------------------------------------------
// 												DEFINES
//---------------------------------------------------------------------------------------------------------

#define LEVEL_X_SIZE 	    __SCREEN_WIDTH
#define LEVEL_Y_SIZE 	    __SCREEN_HEIGHT
#define LEVEL_Z_SIZE 	    __SCREEN_WIDTH

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 	0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

PositionedEntityROMDef TITLE_SCREEN_ST_ENTITIES[] =
{
	// since these are always visible it doesn't matter that they are not logically placed in this definition
	{&MOUND_BG_BACK_SB,	 	{0, 16, LAYER_5}, NULL, NULL, NULL},
	{&MOUND_BG_MIDDLE_SB, 	{0, 96, LAYER_4}, NULL, NULL, NULL},
	{&MOUND_BG_FRONT_SB, 	{0, 184, LAYER_3 + 1}, NULL, NULL, NULL},

	{&VBJAENGINE_IM, 	    {__SCREEN_WIDTH >> 1, 24, LAYER_0 + 32  }, NULL, NULL, NULL},
	{&SUPER_AWESOME_IM,     {__SCREEN_WIDTH >> 1, 42, LAYER_0 + 16	}, NULL, NULL, NULL},
	{&LOGO_IM, 			    {__SCREEN_WIDTH >> 1, 88, LAYER_0   	}, NULL, NULL, NULL},

	{&MOUND_1_IM,			{-14, 174, LAYER_1}, NULL, NULL, NULL},
	{&MOUND_1_IM,			{138, 182, LAYER_1}, NULL, NULL, NULL},
	{&MOUND_2_IM,			{228, 182, LAYER_1}, NULL, NULL, NULL},
	{&MOUND_2_IM,			{384, 192, LAYER_1}, NULL, NULL, NULL},

	{&FLOOR_4x10_BG,		{16, 216, 2}, NULL, NULL, NULL},
	{&FLOOR_4x10_BG,		{64, 208, 2}, NULL, NULL, NULL},
	{&FLOOR_22x8_BG,		{__SCREEN_WIDTH >> 1, 216, 2}, NULL, NULL, NULL},
	{&FLOOR_16x8_BG,		{372, 208, 2}, NULL, NULL, NULL},

	{&HERO_MC, 				{168, 164, 0}, HERO_NAME, NULL, NULL},

	{&COLLISION_2x28x48, 	{88,__SCREEN_HEIGHT >> 1, 0}, NULL, NULL, NULL},
	{&COLLISION_2x28x48, 	{__SCREEN_WIDTH - 92, __SCREEN_HEIGHT >> 1, 0}, NULL, NULL, NULL},

	{&DOOR_MC,				{(__SCREEN_WIDTH >> 1) - 48,   164,    1}, NULL, NULL, (void*)&LEVEL_1_1_ROOM_1_ST},
	{&DOOR_MC,				{__SCREEN_WIDTH >> 1,          164,    1}, NULL, NULL, (void*)&LEVEL_1_2_ROOM_1_ST},
	{&DOOR_MC,				{(__SCREEN_WIDTH >> 1) + 48,   164,    1}, NULL, NULL, (void*)&LEVEL_1_3_ROOM_1_ST},

/*
	{&FLOOR_16x8_BG,		{-32, 174, PLAYABLE_LAYER_2 + 2}, NULL, NULL, NULL},
	{&FLOOR_16x8_BG,		{142, 182, PLAYABLE_LAYER_2 + 2}, NULL, NULL, NULL},
	{&FLOOR_22x8_BG,		{398, 182, PLAYABLE_LAYER_2 + 2}, NULL, NULL, NULL},
*/

	{NULL, {0,0,0}, NULL, NULL, NULL},
};

PositionedEntityROMDef TITLE_SCREEN_ST_UI_ENTITIES[] =
{
	{&GUI_BLANK_IM,			{__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT - 8, 0}, NULL, NULL, NULL},
	{NULL, {0,0,0}, NULL, NULL, NULL},
};

TextureROMDef* TITLE_SCREEN_ST_TEXTURES[] =
{
	&MOUND_BG_BACK_TX,
	&MOUND_BG_MIDDLE_TX,
	&MOUND_BG_FRONT_TX,
	&SUPER_AWESOME_TX,
	&VBJAENGINE_TX,
	&LOGO_LEFT_TX,
	&LOGO_RIGHT_TX,
	&MOUND_1_TX,
	&MOUND_2_TX,
	&GUI_BLANK_TX,
	&HERO_TX,
	&DOOR_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef TITLE_SCREEN_ST =
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
    (TextureDefinition**)TITLE_SCREEN_ST_TEXTURES,

    //UI
    {
        TITLE_SCREEN_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    //entities
    TITLE_SCREEN_ST_ENTITIES,

    //background music
    NULL,
    //(const u16 (*)[])WORLD_0_0_0_BGM,

    //identifier
    "",

    //name
    "",
};