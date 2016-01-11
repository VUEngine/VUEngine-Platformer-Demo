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


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BackgroundMoundCastleTiles[];
extern BYTE BackgroundMoundCastleMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef MOUND_BG_CASTLE_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    34,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    BackgroundMoundCastleTiles,
};

TextureROMDef MOUND_BG_CASTLE_TX =
{
    // charset definition
    (CharSetDefinition*)&MOUND_BG_CASTLE_CH,

    // bgmap definition
    BackgroundMoundCastleMap,

    // cols (max 64)
    11,

    // rows (max 64)
    6,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef MOUND_BG_CASTLE_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&MOUND_BG_CASTLE_TX,

	// displacement vector
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const MOUND_BG_CASTLE_IM_SPRITES[] =
{
	&MOUND_BG_CASTLE_IM_SPRITE,
	NULL
};

ImageROMDef MOUND_BG_CASTLE_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)MOUND_BG_CASTLE_IM_SPRITES,
};