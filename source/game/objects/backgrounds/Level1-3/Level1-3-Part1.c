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

extern BYTE Level1_3_Part1_LTiles[];
extern BYTE Level1_3_Part1_LMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LEVEL1_3_PART1_L_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        17,

        // allocation type
        __NO_ANIMATED,

        // char definition
        Level1_3_Part1_LTiles,
    },

    // bgmap definition
    Level1_3_Part1_LMap,

    // cols (max 48)
    48,

    // rows (max 28)
    28,

    // palette number
    1,
};

SpriteROMDef LEVEL1_3_PART1_IM_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&LEVEL1_3_PART1_L_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		-1,
	},
	{NULL, NULL, 0, 0, 0}
};

ImageROMDef LEVEL1_3_PART1_IM =
{
	__TYPE(Image),
	LEVEL1_3_PART1_IM_SPRITES,
};