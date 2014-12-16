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

extern BYTE CloudsATiles[];
extern BYTE CloudsBTiles[];
extern BYTE CloudsAMap[];
extern BYTE CloudsBMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef CLOUDS_A_TX =
{
    {
        // number of chars
        22,

        // allocation type
        __NO_ANIMATED,

        // char definition
        CloudsATiles,
    },

    // bgmap definition
    CloudsAMap,

    // cols (max 48)
    48,

    // rows (max 28)
    7,

    // palette number
    0,
};

TextureROMDef CLOUDS_B_TX =
{
    {
        // number of chars
        27,

        // allocation type
        __NO_ANIMATED,

        // char definition
        CloudsBTiles,
    },

    // bgmap definition
    CloudsBMap,

    // cols (max 48)
    48,

    // rows (max 28)
    7,

    // palette number
    0,
};

SpriteROMDef CLOUDS_SB_SPRITES[] =
{
	{
		// texture definition
		(TextureDefinition*)&CLOUDS_A_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,

	},
	{
		// texture definition
		(TextureDefinition*)&CLOUDS_B_TX,

		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,

		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
};

ScrollBackgroundROMDef CLOUDS_SB =
{
	__TYPE(ScrollBackground),
	__SPRITE_ARRAY(CLOUDS_SB_SPRITES),
};