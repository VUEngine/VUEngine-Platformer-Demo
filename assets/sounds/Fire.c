/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */

 //---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SoundManager.h>


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


const u16 FIRE_SND[] =
{
		
//songlength
		10,
//stdwait
		0x01,
//stdSxLRV
		0xFF,
//stdSxEV0
		0xF1,
//stdSxEV1
		0x01,
//stdSxRAM
		0x00,
//stdS5SWP
		//0x00,
//song's notes
		
		A_2,
		GS2,
		G_2,
		GS2,
		0x12,
		0x0F,
		//0x00,
		//0x00,
		0x3C,
		0x3C,
		0x3C,
		0x3C,
		0x3C,
		0x3C,
		0x3C,
		0x3C,
		0x3C,
		0x31,
		0x31,
		0x31,
};


