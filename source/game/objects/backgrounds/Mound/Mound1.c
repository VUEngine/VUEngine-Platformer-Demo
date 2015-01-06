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

#include <Image.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Mound1Tiles[];
extern BYTE Mound1Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef MOUND_1_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        14,

        // allocation type
        __NO_ANIMATED,

        // char definition
        Mound1Tiles,
    },

    // bgmap definition
    Mound1Map,

    // cols (max 48)
    6,

    // rows (max 28)
    9,

    // palette number
    0,
};

SpriteROMDef MOUND_1_IM_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&MOUND_1_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
	{NULL, NULL, 0, 0, 0}
};

ImageROMDef MOUND_1_IM =
{
	__TYPE(Image),
	MOUND_1_IM_SPRITES,
};