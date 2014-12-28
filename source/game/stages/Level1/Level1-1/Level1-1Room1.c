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

StageROMDef LEVEL_1_1_ROOM_2_ST;


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

#define SCREEN_X_POSITION 	0
#define SCREEN_Y_POSITION 	LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 	0


//---------------------------------------------------------------------------------------------------------
// 												ASSETS
// ---------------------------------------------------------------------------------------------------------
/* Don't forget to place the NULL markers at the end of each array. It's the only way the engine has to
 * know that it must stop reading the stage's/ui's textures ante enties.
 */

PositionedEntityROMDef LEVEL_1_1_ROOM_1_ST_ENTITIES[] =
{
	// since these are always visible
	// it doesn't matter that they are not logically
	// placed in this definition
	{&TREE_BG_BACK_SB,	 	{SCREEN_X_POSITION, SCREEN_Y_POSITION + 102, LAYER_4}, NULL},
	{&TREE_BG_FRONT_SB, 	{SCREEN_X_POSITION, SCREEN_Y_POSITION + 168, LAYER_3}, NULL},
	{&CLOUDS_SB, 			{SCREEN_X_POSITION, SCREEN_Y_POSITION - 16, LAYER_2}, NULL}, 
	{&HERO_MC, 				{SCREEN_X_POSITION + 32, SCREEN_Y_POSITION + 60, PLAYABLE_LAYER_0}, NULL},

	// the following entities must be placed in logical (spatial) order,
	// according to the level's disposition, for the streaming to work properly
	// beware of edge case scenarios!
	{&COLLISION_2x28x48, 	{-12, SCREEN_Y_POSITION + 116, PLAYABLE_LAYER_0}, NULL},
	{&FLOOR_16x8_BG,		{60, SCREEN_Y_POSITION + LAYER_0_FLOOR + 16, PLAYABLE_LAYER_0 + 2}, NULL},
	{&MOUND_1_IM,			{84, SCREEN_Y_POSITION + LAYER_0_FLOOR - 16, LAYER_1}, NULL},
	{&FLOOR_4x10_BG,		{140, SCREEN_Y_POSITION + LAYER_0_FLOOR + 8, PLAYABLE_LAYER_0 + 2 - 0.01f}, NULL},
	{&COIN_MC, 				{132, SCREEN_Y_POSITION + LAYER_0_FLOOR - 40, PLAYABLE_LAYER_0 + 1}, NULL},
	{&COIN_MC, 				{148, SCREEN_Y_POSITION + LAYER_0_FLOOR - 40, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_LANE_V_6_IM,{198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 36, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_MC, 		{198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 16, PLAYABLE_LAYER_0}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{236, SCREEN_Y_POSITION + LAYER_0_FLOOR - 40, PLAYABLE_LAYER_0 + 2}, NULL},
	{&DOOR_MC,				{238, SCREEN_Y_POSITION + LAYER_0_FLOOR - 70, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_22x8_BG,		{384, SCREEN_Y_POSITION + LAYER_0_FLOOR + 8, PLAYABLE_LAYER_0 + 2}, NULL},
	{&MOUND_2_IM,			{392, SCREEN_Y_POSITION + LAYER_0_FLOOR - 16, LAYER_1}, NULL},

	{&FLOOR_4x10_BG,		{10, SCREEN_Y_POSITION + LAYER_0_FLOOR - 16, PLAYABLE_LAYER_2 + 2 - 0.01f}, NULL},
	{&FLOOR_22x8_BG,		{382, SCREEN_Y_POSITION + LAYER_0_FLOOR - 28, PLAYABLE_LAYER_2 + 2}, NULL},
	{&DOOR_MC,				{314, SCREEN_Y_POSITION + LAYER_0_FLOOR - 78, PLAYABLE_LAYER_2 + 1}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{520, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_2 + 2}, NULL},

	{&FLOOR_2x2_BLOCK_BG,	{512, SCREEN_Y_POSITION + LAYER_0_FLOOR - 60, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{508, SCREEN_Y_POSITION + LAYER_0_FLOOR - 72, PLAYABLE_LAYER_0 + 1}, NULL},

	{&FLOOR_16x8_BG,		{626, SCREEN_Y_POSITION + LAYER_0_FLOOR - 28, PLAYABLE_LAYER_2 + 2}, NULL},

	{&FLOOR_2x2_BLOCK_BG,	{576, SCREEN_Y_POSITION + LAYER_0_FLOOR - 98, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{572, SCREEN_Y_POSITION + LAYER_0_FLOOR - 110, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{648, SCREEN_Y_POSITION + LAYER_0_FLOOR - 130, PLAYABLE_LAYER_0 + 2}, NULL},
	{&KEY_MC,	            {648, SCREEN_Y_POSITION + LAYER_0_FLOOR - 152, PLAYABLE_LAYER_0 + 1}, NULL},


	{&FLOOR_16x8_BG,		{770, SCREEN_Y_POSITION + LAYER_0_FLOOR - 126, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_16x8_BG,		{880, SCREEN_Y_POSITION + LAYER_0_FLOOR - 90, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_16x8_BG,		{1000, SCREEN_Y_POSITION + LAYER_0_FLOOR - 50, PLAYABLE_LAYER_0 + 2}, NULL},

	{&FLOOR_16x8_BG,		{1072, SCREEN_Y_POSITION + LAYER_0_FLOOR, PLAYABLE_LAYER_0 + 2}, NULL},
	{&MOUND_1_IM,			{1096, SCREEN_Y_POSITION + LAYER_0_FLOOR - 32, LAYER_1}, NULL},
	{&FLOOR_4x10_BG,		{1155, SCREEN_Y_POSITION + LAYER_0_FLOOR - 8, PLAYABLE_LAYER_0 + 2 - 0.01f}, NULL},
	{&COIN_MC, 				{1146, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 1}, NULL},
	{&COIN_MC, 				{1162, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_LANE_V_6_IM,{1198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 62, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_MC, 		{1198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 40, PLAYABLE_LAYER_0}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{1236, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 2}, NULL},
	{&DOOR_MC,				{1238, SCREEN_Y_POSITION + LAYER_0_FLOOR - 86, PLAYABLE_LAYER_0 + 1}, &LEVEL_1_1_ROOM_2_ST},
	{&FLOOR_16x8_BG,		{1368, SCREEN_Y_POSITION + LAYER_0_FLOOR - 8, PLAYABLE_LAYER_0 + 2}, NULL},
	{&MOUND_2_IM,			{1376, SCREEN_Y_POSITION + LAYER_0_FLOOR - 32, LAYER_1}, NULL},
	{&FLOOR_2x2_BLOCK_BG,	{1496, SCREEN_Y_POSITION + LAYER_0_FLOOR - 76, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{1492, SCREEN_Y_POSITION + LAYER_0_FLOOR - 88, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_2x2_BLOCK_BG,	{1560, SCREEN_Y_POSITION + LAYER_0_FLOOR - 114, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{1556, SCREEN_Y_POSITION + LAYER_0_FLOOR - 126, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{1632, SCREEN_Y_POSITION + LAYER_0_FLOOR - 146, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_4x10_BG,		{1698, SCREEN_Y_POSITION + LAYER_0_FLOOR - 146, PLAYABLE_LAYER_0 + 1 + 0.5f}, NULL},
	{&FLOOR_16x8_BG,		{1800, SCREEN_Y_POSITION + LAYER_0_FLOOR - 126, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_16x8_BG,		{1900, SCREEN_Y_POSITION + LAYER_0_FLOOR - 90, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_16x8_BG,		{2000, SCREEN_Y_POSITION + LAYER_0_FLOOR - 50, PLAYABLE_LAYER_0 + 2}, NULL},

	{&FLOOR_16x8_BG,		{2072, SCREEN_Y_POSITION + LAYER_0_FLOOR, PLAYABLE_LAYER_0 + 2}, NULL},
	{&MOUND_1_IM,			{2096, SCREEN_Y_POSITION + LAYER_0_FLOOR - 32, LAYER_1}, NULL},
	{&FLOOR_4x10_BG,		{2155, SCREEN_Y_POSITION + LAYER_0_FLOOR - 8, PLAYABLE_LAYER_0 + 2 - 0.01f}, NULL},
	{&COIN_MC, 				{2146, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 1}, NULL},
	{&COIN_MC, 				{2162, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_LANE_V_6_IM,{2198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 62, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_MC, 		{2198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 40, PLAYABLE_LAYER_0}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{2236, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 2}, NULL},
	{&DOOR_MC,				{2238, SCREEN_Y_POSITION + LAYER_0_FLOOR - 86, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_16x8_BG,		{2368, SCREEN_Y_POSITION + LAYER_0_FLOOR - 8, PLAYABLE_LAYER_0 + 2}, NULL},
	{&MOUND_2_IM,			{2376, SCREEN_Y_POSITION + LAYER_0_FLOOR - 32, LAYER_1}, NULL},
	{&FLOOR_2x2_BLOCK_BG,	{2496, SCREEN_Y_POSITION + LAYER_0_FLOOR - 76, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{2492, SCREEN_Y_POSITION + LAYER_0_FLOOR - 88, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_2x2_BLOCK_BG,	{2560, SCREEN_Y_POSITION + LAYER_0_FLOOR - 114, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{2556, SCREEN_Y_POSITION + LAYER_0_FLOOR - 126, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{2632, SCREEN_Y_POSITION + LAYER_0_FLOOR - 146, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_4x10_BG,		{2698, SCREEN_Y_POSITION + LAYER_0_FLOOR - 146, PLAYABLE_LAYER_0 + 1 + 0.5f}, NULL},
	{&FLOOR_16x8_BG,		{2800, SCREEN_Y_POSITION + LAYER_0_FLOOR - 126, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_16x8_BG,		{2900, SCREEN_Y_POSITION + LAYER_0_FLOOR - 90, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_16x8_BG,		{3000, SCREEN_Y_POSITION + LAYER_0_FLOOR - 50, PLAYABLE_LAYER_0 + 2}, NULL},
	{NULL, {0,0,0}, NULL},
};

PositionedEntityROMDef LEVEL_1_1_ROOM_1_ST_UI_ENTITIES[] =
{
	{&GUI_IM, 				{__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT - 8, -4}, NULL},
	{NULL, {0,0,0}, NULL}
};

TextureROMDef* LEVEL_1_1_ROOM_1_ST_TEXTURES[] =
{
	&CLOUDS_A_TX,
	&CLOUDS_B_TX,
	&TREE_BG_FRONT_TX,
	&TREE_BG_BACK_TX,
	&COIN_TX,
	&SAW_BLADE_TX,
	&SAW_BLADE_LANE_V_6_TX,
	&GUI_TX,
	&FLOOR_4x10_L_TX,
	&FLOOR_4x10_R_TX,
	&FLOOR_16x8_L_TX,
	&FLOOR_16x8_R_TX,
	&FLOOR_4x3_FLOAT_L_TX,
	&FLOOR_4x3_FLOAT_R_TX,
	&DOOR_TX,
	&MOUND_1_TX,
	&MOUND_2_TX,
	&KEY_TX,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											STAGE DEFINITION
//---------------------------------------------------------------------------------------------------------

StageROMDef LEVEL_1_1_ROOM_1_ST =
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
    (TextureDefinition**)LEVEL_1_1_ROOM_1_ST_TEXTURES,

    //UI
    {
        LEVEL_1_1_ROOM_1_ST_UI_ENTITIES,
        __TYPE(UI),
    },

    //entities
    LEVEL_1_1_ROOM_1_ST_ENTITIES,

    //background music
    NULL,
    //(const u16 (*)[])WORLD_0_0_0_BGM,

    //identifier
    "1-1",

    //name
    // TODO: use translated string
    // I18n_getText(I18n_getInstance(), STR_LEVEL_1_1_NAME)),
    "Woohoo Hills",
};