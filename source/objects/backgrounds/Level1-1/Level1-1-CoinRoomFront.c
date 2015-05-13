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

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <MBackground.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level1_1_CoinRoomFrontTiles[];
extern BYTE Level1_1_CoinRoomFrontMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LEVEL1_1_COIN_ROOM_FRONT_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        19,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        Level1_1_CoinRoomFrontTiles,
    },

    // bgmap definition
    Level1_1_CoinRoomFrontMap,

    // cols (max 64)
    48,

    // rows (max 64)
    28,

    // number of frames
    1,

    // palette number
    0,
};

BgmapSpriteROMDef LEVEL1_1_COIN_ROOM_FRONT_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&LEVEL1_1_COIN_ROOM_FRONT_TX,
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	0
};

BgmapSpriteROMDef* const LEVEL1_1_COIN_ROOM_FRONT_IM_SPRITES[] =
{
	&LEVEL1_1_COIN_ROOM_FRONT_IM_SPRITE,
	NULL
};

MBackgroundROMDef LEVEL1_1_COIN_ROOM_FRONT_IM =
{
	__TYPE(MBackground),
	(SpriteROMDef**)LEVEL1_1_COIN_ROOM_FRONT_IM_SPRITES,
};