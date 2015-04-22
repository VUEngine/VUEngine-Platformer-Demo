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
#include <InAnimatedInGameEntity.h>
#include <macros.h>
#include <Lava.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE LavaTiles[];
extern BYTE LavaMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LAVA_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __NOT_ANIMATED: number of chars of whole image
        15,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        LavaTiles,
    },

    // bgmap definition
    LavaMap,

    // cols (max 64)
    48,

    // rows (max 64)
    28,

    // number of frames
    1,

    // palette number
    0,
};

BgmapSpriteROMDef LAVA_BG_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&LAVA_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	-2		
};

BgmapSpriteROMDef* const LAVA_BG_SPRITES[] =
{
	&LAVA_BG_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef LAVA_IG =
{
    {
        {
            __TYPE(Lava),
            (SpriteROMDef**)LAVA_BG_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {0, 0, 0, 0},

        // in game type
        kLava,

        // if 0, width and height will be inferred from
        // the texture's size
        // width
    	0,

    	// height
    	0,

        // deep
        20
    },

    // friction FTOFIX19_13
    FTOFIX19_13(0.0f),

    // elasticity FTOFIX19_13
    FTOFIX19_13(0.0f),

    // register shape
    true,
};