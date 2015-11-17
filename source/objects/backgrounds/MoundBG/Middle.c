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
#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BackgroundMoundMiddleTiles[];
extern BYTE BackgroundMoundMiddleMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


TextureROMDef MOUND_BG_MIDDLE_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        87,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        BackgroundMoundMiddleTiles,
    },

    // bgmap definition
    BackgroundMoundMiddleMap,

    // cols (max 64)
    64,

    // rows (max 64)
    16,

    // number of frames
    1,

    // palette number
    0,
};

TextureROMDef* MOUND_BG_MIDDLE_SB_TEXTURES[] = 
{
	(TextureDefinition*)&MOUND_BG_MIDDLE_TX,
	NULL
};

MBgmapSpriteROMDef MOUND_BG_MIDDLE_SB_SPRITE =
{
	{
		// sprite's type
		__TYPE(MBgmapSprite),

		// texture definition
		NULL,

        // displacement (x, y, z) (in pixels)
        {0, 0, 0},
		
		// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
		WRLD_BGMAP,
		
		// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
		WRLD_ON,
	},
	
	(TextureDefinition**)MOUND_BG_MIDDLE_SB_TEXTURES,
	
	// SCX/SCY
	WRLD_1x1,

	// x loop
	true,
	
	// y loop
	false
};

BgmapSpriteROMDef* const MOUND_BG_MIDDLE_SB_SPRITES[] =
{
	(BgmapSpriteROMDef*)&MOUND_BG_MIDDLE_SB_SPRITE,
	NULL
};

ImageROMDef MOUND_BG_MIDDLE_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)MOUND_BG_MIDDLE_SB_SPRITES,
};