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

#include <ScrollBackground.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BackgroundMoundFrontTiles[];
extern BYTE BackgroundMoundFrontMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


TextureROMDef MOUND_BG_FRONT_TX =
{
    {
        // number of chars
        18,

        // allocation type
        __NO_ANIMATED,

        // char definition
        BackgroundMoundFrontTiles,
    },

    // bgmap definition
    BackgroundMoundFrontMap,

    // cols (max 48)
    48,

    // rows (max 28)
    16,

    // palette number
    2,
};

SpriteROMDef MOUND_BG_FRONT_SB_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&MOUND_BG_FRONT_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,

	},
	{
		// sprite's type
		__TYPE(Sprite),

		// texture definition
		(TextureDefinition*)&MOUND_BG_FRONT_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
	{NULL, NULL, 0, 0, 0}
};

ScrollBackgroundROMDef MOUND_BG_FRONT_SB =
{
	__TYPE(ScrollBackground),
	MOUND_BG_FRONT_SB_SPRITES,
};