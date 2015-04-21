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

extern BYTE TitleScreenMiddleTiles[];
extern BYTE TitleScreenMiddleMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef TITLESCREEN_MIDDLE_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        24,

        // allocation type
        __NO_ANIMATED,

        // char definition
        TitleScreenMiddleTiles,
    },

    // bgmap definition
    TitleScreenMiddleMap,

    // cols (max 64)
    50,

    // rows (max 64)
    10,

    // number of frames
    1,

    // palette number
    1,
};

BSpriteROMDef TITLESCREEN_MIDDLE_IM_SPRITE =
{
	// sprite's type
	__TYPE(BSprite),

	// texture definition
	(TextureDefinition*)&TITLESCREEN_MIDDLE_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	0
};

BSpriteROMDef* const TITLESCREEN_MIDDLE_IM_SPRITES[] =
{
	&TITLESCREEN_MIDDLE_IM_SPRITE,
	NULL
};

ImageROMDef TITLESCREEN_MIDDLE_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)TITLESCREEN_MIDDLE_IM_SPRITES,
};