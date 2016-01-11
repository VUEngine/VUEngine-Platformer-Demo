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

#include <Image.h>
#include <BgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Mound1Tiles[];
extern BYTE Mound1Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef MOUND_1_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    14,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    Mound1Tiles,
};

TextureROMDef MOUND_1_TX =
{
    // charset definition
    (CharSetDefinition*)&MOUND_1_CH,

    // bgmap definition
    Mound1Map,

    // cols (max 64)
    6,

    // rows (max 64)
    9,

    // number of frames
    1,

    // palette number
    0,
};

BgmapSpriteROMDef MOUND_1_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&MOUND_1_TX,

	// displacement vector
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const MOUND_1_IM_SPRITES[] =
{
	&MOUND_1_IM_SPRITE,
	NULL
};

ImageROMDef MOUND_1_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)MOUND_1_IM_SPRITES,
};