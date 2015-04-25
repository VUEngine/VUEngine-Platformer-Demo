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
#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE StoneBGTiles[];
extern BYTE StoneBGMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


TextureROMDef STONE_BG_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        13,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        StoneBGTiles,
    },

    // bgmap definition
    StoneBGMap,

    // cols (max 64)
    64,

    // rows (max 64)
    64,

    // number of frames
    1,

    // palette number
    1,
};

TextureROMDef* STONE_BG_SB_TEXTURES[] = 
{
	(TextureDefinition*)&STONE_BG_TX,
	NULL
};


MBgmapSpriteROMDef STONE_BG_SB_SPRITE =
{
	{
		// sprite's type
		__TYPE(MBgmapSprite),

		// texture definition
		NULL,
		
		// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
	
	(TextureDefinition**)STONE_BG_SB_TEXTURES,
	
	// SCX/SCY
	WRLD_1x1,

	// x loop
	true,
	
	// y loop
	true
};

BgmapSpriteROMDef* const STONE_BG_SB_SPRITES[] =
{
	(BgmapSpriteROMDef*)&STONE_BG_SB_SPRITE,
	NULL
};

ImageROMDef STONE_BG_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)STONE_BG_SB_SPRITES,
};
