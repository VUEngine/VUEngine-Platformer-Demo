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

#include <ScrollBackground.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CloudsATiles[];
extern BYTE CloudsBTiles[];
extern BYTE CloudsAMap[];
extern BYTE CloudsBMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef CLOUDS_A_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    28,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    CloudsATiles,
};

CharSetROMDef CLOUDS_B_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    27,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    CloudsBTiles,
};

TextureROMDef CLOUDS_A_TX =
{
    // charset definition
    (CharSetDefinition*)&CLOUDS_A_CH,

    // bgmap definition
    CloudsAMap,

    // cols (max 64)
    48,

    // rows (max 64)
    7,

    // number of frames
    1,

    // palette number
    0,
};

TextureROMDef CLOUDS_B_TX =
{
    // charset definition
    (CharSetDefinition*)&CLOUDS_A_CH,

    // bgmap definition
    CloudsBMap,

    // cols (max 64)
    48,

    // rows (max 64)
    7,

    // number of frames
    1,

    // palette number
    0,
};

BgmapSpriteROMDef CLOUDS_SB_SPRITE_1 =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&CLOUDS_A_TX,

	// displacement vector
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef CLOUDS_SB_SPRITE_2 =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&CLOUDS_B_TX,

	// displacement vector
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const CLOUDS_SB_SPRITES[] =
{
	&CLOUDS_SB_SPRITE_1,
	&CLOUDS_SB_SPRITE_2,
	NULL
};

ScrollBackgroundROMDef CLOUDS_SB =
{
	__TYPE(ScrollBackground),
	(SpriteROMDef**)CLOUDS_SB_SPRITES,
};