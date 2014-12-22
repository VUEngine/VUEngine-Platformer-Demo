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

const u16 JUMP_SND[] =
{
//songlength
		1,
//stdwait
		0x0A,
//stdSxLRV
		0xFF,
//stdSxEV0
		0xF1,
//stdSxEV1
		0x01,
//stdSxRAM
		0x03,
//stdS5SWP
		//0x00,
//song's notes
		0x5A0,
};

const u16 FIRE_SND[] =
{
//songlength
		2,
//stdwait
		0x15,
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
		F_4,
		F_5,
		NONE,
		NONE,
		NONE,
		C_3,
		D_3,
		NONE,
		NONE,
		NONE,
		C_3,
		D_3,
		NONE,
		NONE,
		NONE,
		C_3,
		D_3,
		NONE,
		NONE,
		NONE,
		C_3,
		D_3,
		NONE,
		NONE,
		NONE,

};


const u16 FIRE1_SND[] =
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


