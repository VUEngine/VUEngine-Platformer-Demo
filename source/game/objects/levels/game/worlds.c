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
/*---------------------------------ASSETS----------------------------------*/
/* If the world structure is altered, there are GameWorld's methods
 * which asume certain indexes for some attributes so check for those!
 */

StageROMDef TITLE_ST = {
		
		// size
		{
			// x
			384,
			// y
			192,
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
		{
			NULL
		},

		//entities
		{			
			{&MARIO_TITLE_RIGHT_IM, {384/2, 192/2 + 8, LAYER_0}, NULL},
			{&MARIO_TITLE_LEFT_IM, {384/2, 192/2 + 8, LAYER_0}, NULL},
			{NULL,{0,0,0}, NULL},
		},
};

#define LAYER_0_FLOOR	208
#define LAYER_1_FLOOR	208 - 16
#define LAYER_2_FLOOR	208 - 32
#define LAYER_3_FLOOR	208 - 64

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
		{
			&HERO1_TX,
			&HERO0_TX,
			&FLOOR0_TX,
			&PIPE0_TX,
			&PIRANHA_PLANT_V_TX,
			&WALL0_TX,
			&FLOOR1_TX,
			&MOUNTS0_TX,
			&FLOOR2_TX,
			&GOAL0_TX,
			&BACKMOUNT01_TX,
			&BACKMOUNT02_TX,
			&JAPANARC_TX,
			
			NULL
		},
		//entities
		{			
			{&HERO_MC, {60, 0, PLAYABLE_LAYER_0}, NULL},
			{&BACKMOUNT0_SB, {112, 176, LAYER_4}, NULL},
			{&MOUNTS0_IM, {112, 176, LAYER_2}, NULL},
			{&MOUNTS1_IM, {612, 208-80, LAYER_3}, NULL},
			{&FLOOR0_BG, {112, LAYER_0_FLOOR, LAYER_0}, NULL},
			{&FLOOR1_BG, {296, LAYER_0_FLOOR, LAYER_0}, NULL},
			{&FLOOR0_BG, {478, LAYER_0_FLOOR, LAYER_0}, NULL},
			{&JAPANARC_IM, {518, 160, BACKGROUND_LAYER_0}, NULL},
			{&FLOOR0_BG, {592, LAYER_2_FLOOR, LAYER_2}, NULL},
			{&WALL0_BG, {628, 224, LAYER_0}, NULL},			
			{&WALL0_BG, {628 + 4 * 8, 224, LAYER_0}, NULL},			
			{&WALL0_BG, {628 + 4 * 8 * 2 + 24, 224, LAYER_0}, NULL},			
			{&FLOOR1_BG, {728, LAYER_1_FLOOR, LAYER_1}, NULL},
			{&FLOOR0_BG, {868, LAYER_0_FLOOR, LAYER_0}, NULL},
			{&PIPE0_BG, {866, 186, PLAYABLE_LAYER_0 + 1}, NULL},			
			{&PIRANHA_PLANT_V_MC, {865, 178, PLAYABLE_LAYER_0 + 2}, NULL},
			{&WALL0_BG, {900, 160, PLAYABLE_LAYER_1}, NULL},			
			{&FLOOR2_BG, {928, LAYER_2_FLOOR, LAYER_2}, NULL},
			{&FLOOR0_BG, {1130, LAYER_0_FLOOR, LAYER_0}, NULL},
			{&FLOOR0_BG, {1410, LAYER_0_FLOOR, LAYER_0}, NULL},
			{&PIPE1_BG, {1304, 160, PLAYABLE_LAYER_1}, NULL},			
			{&PIPE0_BG, {1376, 184, PLAYABLE_LAYER_1}, NULL},			
			{&FLOOR1_BG, {1448, LAYER_1_FLOOR, LAYER_1}, NULL},
			{&FLOOR0_BG, {1624, LAYER_1_FLOOR, LAYER_1}, NULL},

			{&POLE0_BG, {1484, 124, BACKGROUND_LAYER_1}, NULL},
			{&GOAL0_IM, {1572, 64, BACKGROUND_LAYER_1}, NULL},
			{&GATE0_IM, {112, 96, PLAYABLE_LAYER_0 + 1}, NULL},
//			{&HERO_MC, {60, 70, PLAYABLE_LAYER_0}, NULL},


			{NULL, {0,0,0}, NULL},
		},
};


