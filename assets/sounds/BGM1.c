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

const u16 WORLD_0_0_0_BGM[][2] =
{
	{
        //songlength
		68,
        //stdwait
		0x0C,
	},
	{
        //stdSxLRV
		0x33,
        //stdSxEV0
		0x80,
	},
	{
        //stdSxEV1
		0x01,
        //stdSxRAM
		0x00,
	},
    //stdS5SWP
    //0x00,
    //song's notes
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,NONE,},
    {F_4,F_5,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,D_4,},
    {NONE,F_6,},
    {NONE,NONE,},
    {NONE,E_3,},
    {NONE,F_5,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,F_6,},
    {NONE,NONE,},
    {C_4,F_5,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE,},
    {F_4,F_5,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,D_4,},
    {NONE,F_6,},
    {NONE,NONE,},
    {NONE,E_4,},
    {NONE,F_5,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,F_6,},
    {NONE,NONE,},
    {C_4,F_5,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE,},
    {F_4,F_6,},
    {NONE,F_5,},
    {NONE,NONE,},
    {NONE,D_4,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,E_4,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE,},
    {NONE,F_4,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,D_4,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,E_4,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE,},
    {NONE,C_4,},
    {NONE,NONE},
};
