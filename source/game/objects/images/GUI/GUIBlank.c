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

extern BYTE GUIBlankTiles[];
extern BYTE GUIBlankMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef GUI_BLANK_TX =
{
    {
        // number of chars
        1,

        // allocation type
        __NO_ANIMATED,

        // char definition
        GUIBlankTiles,
    },

    // bgmap definition
    GUIBlankMap,

    // cols (max 48)
    48,

    // rows (max 28)
    2,

    // palette number
    1,
};

SpriteROMDef GUI_BLANK_IM_SPRITES[] =
{
	{
		// texture definition
		(TextureDefinition*)&GUI_BLANK_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
};

ImageROMDef GUI_BLANK_IM =
{
	__TYPE(Image),
	__SPRITE_ARRAY(GUI_BLANK_IM_SPRITES),
};