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
/*---------------------------------ASSETS----------------------------------*/
/* If the world structure is altered, there are GameWorld's methods
 * which asume certain indexes for some attributes so check for those!
 */


StageROMDef PVB_ST = {
		
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

		//entities
		{			
			{&PVB_LEFT_IM, {384/2, 192/2 + 16, LAYER_0}, NULL},
			{&PVB_RIGHT_IM, {384/2, 192/2 + 16, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};

StageROMDef PRECAUTION_ST = {
		
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
		//NULL,

		//entities
		{			
			{&PRECAUTION_IM, {384/2, 192/2 + 16, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};


StageROMDef PVBCC_ST = {
		
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

		//entities
		{			
			{&PVBCC_LEFT_IM, {384/2, 192/2 + 16, LAYER_0}, NULL},
			{&PVBCC_RIGHT_IM, {384/2, 192/2 + 16, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};


StageROMDef VBJAE_ST = {
		
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
		//NULL,

		//entities
		{			
			{&VBJAE_LEFT_IM, {384/2, 192/2 + 16, LAYER_0}, NULL},
			{&VBJAE_RIGHT_IM, {384/2, 192/2 + 16, LAYER_0}, NULL},
			
			{NULL,{0,0,0}, NULL},
		},
};




