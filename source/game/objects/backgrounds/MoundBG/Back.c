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

extern BYTE BackgroundMoundBackTiles[];
extern BYTE BackgroundMoundBackMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


TextureROMDef MOUND_BG_BACK_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        64,

        // allocation type
        __NO_ANIMATED,

        // char definition
        BackgroundMoundBackTiles,
    },

    // bgmap definition
    BackgroundMoundBackMap,

    // cols (max 48)
    48,

    // rows (max 28)
    16,

    // palette number
    0,
};

TextureROMDef* MOUND_BG_BACK_SB_TEXTURES[] = 
{
	(TextureDefinition*)&MOUND_BG_BACK_TX,
	NULL
};

MSpriteROMDef MOUND_BG_BACK_SB_SPRITE =
{
	{
		// sprite's type
		__TYPE(MSprite),

		// texture definition
		NULL,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
	
	(TextureDefinition**)MOUND_BG_BACK_SB_TEXTURES,
	
	// SCX/SCY
	WRLD_1x1,

	// x loop
	true,
	
	// y loop
	false
};

SpriteROMDef* MOUND_BG_BACK_SB_SPRITES[] =
{
	(SpriteROMDef*)&MOUND_BG_BACK_SB_SPRITE,
	NULL
};

MBackgroundROMDef MOUND_BG_BACK_SB =
{
	__TYPE(MBackground),
	MOUND_BG_BACK_SB_SPRITES,
};