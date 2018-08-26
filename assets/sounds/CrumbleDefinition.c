/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <SoundManager.h>


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

const u16 CRUMBLE_SND[] =
{
	//songlength
	64,
	//stdwait
	0x05,
	//stdSxLRV
	0x55,
	//stdSxEV0
	0xD1,
	//stdSxEV1
	0x01,
	//stdSxRAM
	0x03,
	//stdS5SWP
	//0x00,
	//song's notes
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	D_2,
	F_2,
	E_1,
	C_3,
	D_3,
	E_2,
	A_3,
	A_1,
	NONE,
};
