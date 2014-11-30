/* VbJaEngine: bitmap graphics engine for the Nintendo Virtual Boy 
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
#include <objects.h>
#include <macros.h>
#include "textures.h"

/*---------------------------------ASSETS----------------------------------*/
/* Don't forget to place the NULL markers at the end of each array.
 * It's the only way the engine has to know that it must stop reading 
 * the stage's/ui's textures ante enties
 */

PositionedEntityROMDef TITLE_ST_ENTITIES[] = {

	{&HERO_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
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
		//textures 
		NULL,
		//UI entities
		{
			NULL,
			NULL,
		},
		//entities
		TITLE_ST_ENTITIES
};

#define LAYER_0_FLOOR	196
#define LAYER_1_FLOOR	196 - 16
#define LAYER_2_FLOOR	196 - 32
#define LAYER_3_FLOOR	196 - 64

TextureROMDef* LEVEL_0_0_0_ST_TEXTURES[] = {
		
	&HERO0_TX,
	&COIN0_TX,
	&FLOOR0_TX,
	&PIPE0_TX,
	&PIRANHA_PLANT_V_TX,
	&SAW_BLADE_TX,
	&WALL0_TX,
	&FLOOR1_TX,
	&MOUNTS0_TX,
	&MOUNTS1_TX,
	&FLOOR2_TX,
	&GOAL0_TX,
	&BACKMOUNT01_TX,
	&BACKMOUNT02_TX,
	&JAPANARC_TX,
	&SAW_BLADE_LANE_V_6_TX,
	&GUI_TX,
	NULL
};

PositionedEntityROMDef LEVEL_0_0_0_ST_UI_ENTITIES[] = {
		
	{&GUI_IM, 				{__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT - 8, 0}, NULL},
	{NULL, {0,0,0}, NULL}
};

PositionedEntityROMDef LEVEL_0_0_0_ST_ENTITIES[] = {

	{&HERO_MC, 				{60, 0, PLAYABLE_LAYER_0}, NULL},
	{&COIN_MC, 				{140, LAYER_0_FLOOR - 24, PLAYABLE_LAYER_0 + 1}, NULL},
	{&COIN_MC, 				{156, LAYER_0_FLOOR - 24, PLAYABLE_LAYER_0 + 1}, NULL},
	{&COIN_MC, 				{172, LAYER_0_FLOOR - 24, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_LANE_V_6_IM,{237, LAYER_0_FLOOR - 30, PLAYABLE_LAYER_0 + 1}, NULL},
	{&SAW_BLADE_MC, 		{238, LAYER_0_FLOOR - 8, PLAYABLE_LAYER_0}, NULL},
	{&BACKMOUNT0_SB, 		{112, 160, LAYER_4}, NULL},
	{&MOUNTS1_IM, 			{112, 112, LAYER_3}, NULL},
	{&FLOOR0_BG, 			{88, LAYER_0_FLOOR, LAYER_0}, NULL},
	{&FLOOR1_BG, 			{296, LAYER_0_FLOOR, LAYER_0}, NULL},   
	{&FLOOR0_BG, 			{478, LAYER_0_FLOOR, LAYER_0}, NULL},// 5
	{&FLOOR0_BG, 			{592, LAYER_2_FLOOR, LAYER_2}, NULL},
	{&WALL0_BG, 			{628 + 1 * 8, 208, LAYER_0 + 1}, NULL},			
	{&WALL0_BG, 			{628 + 3 * 8 * 2 + 24, 208, LAYER_0 + 1}, NULL},   		
	{&MOUNTS0_IM, 			{812, 176, LAYER_2}, NULL},// 10
	//{&PIRANHA_PLANT_V_MC, 	{865, 181, PLAYABLE_LAYER_0 + 2}, NULL},
	{&PIPE0_BG, 			{866, 186, PLAYABLE_LAYER_0 + 1}, NULL},
	{&FLOOR0_BG, 			{868, LAYER_0_FLOOR, LAYER_0}, NULL},
	{&WALL0_BG, 			{900, 160, PLAYABLE_LAYER_1}, NULL},			
	//{&FLOOR2_BG, 			{928, LAYER_2_FLOOR, LAYER_2}, NULL},//15
	{&PIPE1_BG, 			{1104, 160, PLAYABLE_LAYER_1}, NULL},// 15			
	{&FLOOR0_BG, 			{1130, LAYER_0_FLOOR, LAYER_0}, NULL},
	//{&PIRANHA_PLANT_V_MC, 	{1347, 181 - 20, LAYER_1 + 2}, NULL},
	{&PIPE0_BG, 			{1348, 186 - 20, LAYER_1 + 1}, NULL},
	{&FLOOR1_BG, 			{1348, LAYER_1_FLOOR, LAYER_1}, NULL},
	{&FLOOR0_BG, 			{1410, LAYER_0_FLOOR, LAYER_0}, NULL},// 20
	{&POLE0_BG, 			{1504, 124, BACKGROUND_LAYER_1}, NULL},
	{&GOAL0_IM, 			{1592, 64, BACKGROUND_LAYER_1 + 1}, NULL},
	{&FLOOR0_BG, 			{1604, LAYER_1_FLOOR, LAYER_1}, NULL},
	//{&GATE0_IM, {112, 96, PLAYABLE_LAYER_0 + 1}, NULL},


	{NULL, {0,0,0}, NULL},
};

StageROMDef LEVEL_0_0_0_ST = {
		
		// size
		{
			// x
			2800,
			// y
			228,
			// z
			LAYER_4
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
		(const u16 (*)[])WORLD_0_0_0_BGM,
		// textures
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


