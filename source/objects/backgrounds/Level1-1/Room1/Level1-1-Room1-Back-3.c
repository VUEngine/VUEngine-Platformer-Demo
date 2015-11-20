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

extern BYTE Level1_1_Back_3Tiles[];
extern BYTE Level1_1_Back_3Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LEVEL1_1_BACK_3_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        45,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        Level1_1_Back_3Tiles,
    },

    // bgmap definition
    Level1_1_Back_3Map,

    // cols (max 64)
    37,

    // rows (max 64)
    8,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef LEVEL1_1_BACK_3_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&LEVEL1_1_BACK_3_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 1},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const LEVEL1_1_BACK_3_IM_SPRITES[] =
{
	&LEVEL1_1_BACK_3_IM_SPRITE,
	NULL
};

ImageROMDef LEVEL1_1_BACK_3_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)LEVEL1_1_BACK_3_IM_SPRITES,
};