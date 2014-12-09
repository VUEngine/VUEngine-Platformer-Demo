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


/*---------------------------------INCLUDES--------------------------------*/
#include <Stage.h>
#include <objects.h>
#include <macros.h>
#include "textures.h"

/*---------------------------------ASSETS----------------------------------*/
/* Don't forget to place the NULL markers at the end of each array.
 * It's the only way the engine has to know that it must stop reading 
 * the stage's/ui's textures ante enties
 */

PositionedEntityROMDef TITLE_ST_UI_ENTITIES[] = {

	{&VBJAENGINE_IM, 	{__SCREEN_WIDTH >> 1, 	 	62, 	LAYER_0			}, NULL},			
	{&SUPER_AWESOME_IM, {__SCREEN_WIDTH >> 1, 	 	80, 	LAYER_0 - 16	}, NULL},			
	{&LOGO_IM, 			{__SCREEN_WIDTH >> 1, 		104, 	LAYER_0			}, NULL},			
	{&HERO_IM, 			{__SCREEN_WIDTH >> 1, 		172, 	LAYER_0 - 1		}, NULL},
	{&FLOOR_16x8_BG, 	{__SCREEN_WIDTH >> 1,		214, 	LAYER_0			}, NULL},
	{NULL,{0,0,0}, NULL},
};

PositionedEntityROMDef TITLE_ST_ENTITIES[] = {

	{&VBJAENGINE_BG_SB, {0, __SCREEN_HEIGHT >> 1, LAYER_0 + 32}, NULL},
	{NULL,{0,0,0}, NULL},
};

StageROMDef TITLE_ST = {
		
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
		//background music		
		NULL,
		//textures to preload
		NULL,
		//UI entities
		{
			// type
			__TYPE(UI),
			// entities
			TITLE_ST_UI_ENTITIES
		},
		//entities
		TITLE_ST_ENTITIES
};

#define LAYER_0_FLOOR	196
#define LAYER_1_FLOOR	196 - 16
#define LAYER_2_FLOOR	196 - 32
#define LAYER_3_FLOOR	196 - 64

TextureROMDef* LEVEL_0_0_0_ST_TEXTURES[] = {
		
	&COIN_TX, 
	&SAW_BLADE_TX,
	&SAW_BLADE_LANE_V_6_TX,
	&GUI_TX,
	&CLOUDS_TX,
	&TREE_BG_FRONT_TX,
	&TREE_BG_BACK_TX,
	&FLOOR_4x10_L_TX,
	&FLOOR_4x10_R_TX,
	&FLOOR_16x8_L_TX,
	&FLOOR_16x8_R_TX,
	&FLOOR_4x3_FLOAT_L_TX,
	&FLOOR_4x3_FLOAT_R_TX,
	&DOOR_TX,
	&MOUND_1_TX,
	&MOUND_2_TX,
	NULL
};

PositionedEntityROMDef LEVEL_0_0_0_ST_UI_ENTITIES[] = {
		
	{&GUI_IM, 				{__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT - 8, -4}, NULL},
	{NULL, {0,0,0}, NULL}
};

#define LEVEL_X_SIZE 	3000
#define LEVEL_Y_SIZE 	2000
#define LEVEL_Z_SIZE 	2000

#define SCREEN_X_POSITION 		0
#define SCREEN_Y_POSITION 		LEVEL_Y_SIZE - __SCREEN_HEIGHT
#define SCREEN_Z_POSITION 		0

PositionedEntityROMDef LEVEL_0_0_0_ST_ENTITIES[] = {

	{&TREE_BG_BACK_SB,	 	{0, SCREEN_Y_POSITION + 102, LAYER_4}, NULL},
	{&TREE_BG_FRONT_SB, 	{0, SCREEN_Y_POSITION + 168, LAYER_3}, NULL},
	{&CLOUDS_SB, 			{0, SCREEN_Y_POSITION - 16, LAYER_2}, NULL}, 
	{&FLOOR_16x8_BG,		{72, SCREEN_Y_POSITION + LAYER_0_FLOOR, PLAYABLE_LAYER_0 + 2}, NULL},
	{&MOUND_1_IM,			{96, SCREEN_Y_POSITION + LAYER_0_FLOOR - 32, LAYER_1}, NULL},
	{&FLOOR_4x10_BG,		{155, SCREEN_Y_POSITION + LAYER_0_FLOOR - 8, PLAYABLE_LAYER_0 + 2}, NULL},
	{&HERO_MC, 				{60, SCREEN_Y_POSITION + 60, PLAYABLE_LAYER_0}, NULL},
	{&COIN_MC, 				{146, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 1}, NULL},
	{&COIN_MC, 				{162, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 1}, NULL},
//	{&SAW_BLADE_LANE_V_6_IM,{198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 62, PLAYABLE_LAYER_0 + 1}, NULL},
//	{&SAW_BLADE_MC, 		{198, SCREEN_Y_POSITION + LAYER_0_FLOOR - 40, PLAYABLE_LAYER_0}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{236, SCREEN_Y_POSITION + LAYER_0_FLOOR - 56, PLAYABLE_LAYER_0 + 2}, NULL},
	{&DOOR_MC,				{238, SCREEN_Y_POSITION + LAYER_0_FLOOR - 86, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR_16x8_BG,		{368, SCREEN_Y_POSITION + LAYER_0_FLOOR - 8, PLAYABLE_LAYER_0 + 2}, NULL},
//	{&DOOR_MC,				{312, SCREEN_Y_POSITION + LAYER_0_FLOOR - 102, PLAYABLE_LAYER_2 + 1}, NULL},
//	{&FLOOR_4x10_BG,		{312, SCREEN_Y_POSITION + LAYER_0_FLOOR - 32, PLAYABLE_LAYER_2 + 1}, NULL},
	{&MOUND_2_IM,			{376, SCREEN_Y_POSITION + LAYER_0_FLOOR - 32, LAYER_1}, NULL},
	{&FLOOR_2x2_BLOCK_BG,	{496, SCREEN_Y_POSITION + LAYER_0_FLOOR - 76, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{492, SCREEN_Y_POSITION + LAYER_0_FLOOR - 88, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_2x2_BLOCK_BG,	{560, SCREEN_Y_POSITION + LAYER_0_FLOOR - 114, PLAYABLE_LAYER_0 + 2}, NULL},
	{&COIN_MC,				{556, SCREEN_Y_POSITION + LAYER_0_FLOOR - 126, PLAYABLE_LAYER_0 + 2}, NULL},
	{&FLOOR_4x3_FLOAT_BG,	{632, SCREEN_Y_POSITION + LAYER_0_FLOOR - 146, PLAYABLE_LAYER_0 + 2}, NULL},

	{NULL, {0,0,0}, NULL},
};

StageROMDef LEVEL_0_0_0_ST = {
		
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
			ITOFIX19_13(SCREEN_Z_POSITION),
			// y
			ITOFIX19_13(SCREEN_Y_POSITION),
			// z
			ITOFIX19_13(SCREEN_Z_POSITION)
		},
		//background music		
		NULL,
		//(const u16 (*)[])WORLD_0_0_0_BGM,
		//textures to preload
		(TextureDefinition**)LEVEL_0_0_0_ST_TEXTURES,
		//UI 
		{
			// type
			__TYPE(UI),
			// entities
			LEVEL_0_0_0_ST_UI_ENTITIES
		},
		//entities
		LEVEL_0_0_0_ST_ENTITIES
};


