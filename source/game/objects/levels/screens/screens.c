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

/*---------------------------------ASSETS----------------------------------*/


StageROMDef PVB_ST = {
		
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
		{
			NULL
		},
		//UI entities
		{
			{NULL, {0,0,0}, NULL},
		},
		//entities
		{			
			{&PVB_LEFT_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
			{&PVB_RIGHT_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};

StageROMDef PRECAUTION_ST = {
		
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
		{
			NULL
		},
		//UI entities
		{
			{NULL, {0,0,0}, NULL},
		},
		//entities
		{			
			{&PRECAUTION_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};


StageROMDef PVBCC_ST = {
		
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
		{
			NULL
		},
		//UI entities
		{
			{NULL, {0,0,0}, NULL},
		},
		//entities
		{			
			{&PVBCC_LEFT_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
			{&PVBCC_RIGHT_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};


StageROMDef VBJAE_ST = {
		
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
		{
			NULL
		},
		//UI entities
		{
			{NULL, {0,0,0}, NULL},
		},
		//entities
		{			
			{&VBJAE_LEFT_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
			{&VBJAE_RIGHT_IM, {__SCREEN_WIDTH >> 1, __SCREEN_HEIGHT >> 1, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};




