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

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Floor22x8LTiles[];
extern BYTE Floor22x8LMap[];
extern BYTE Floor22x8RTiles[];
extern BYTE Floor22x8RMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef FLOOR_22x8_L_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        13,

        // allocation type
        __NO_ANIMATED,

        // char definition
        Floor22x8LTiles,
    },

    // bgmap definition
    Floor22x8LMap,

    // cols (max 48)
    22 + 1,

    // rows (max 28)
    8 + 1,

    // number of frames
    1,

    // palette number
    1,
};

TextureROMDef FLOOR_22x8_R_TX =
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
        Floor22x8RTiles,
    },

    // bgmap definition
    Floor22x8RMap,

    // cols (max 48)
    22 + 1,

    // rows (max 28)
    8 + 1,

    // number of frames
    1,

    // palette number
    1,
};

SpriteROMDef FLOOR_22x8_BG_SPRITE =
{
	// sprite's type
	__TYPE(Sprite),

	// texture definition
	(TextureDefinition*)&FLOOR_22x8_L_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_AFFINE,
	
	// display mode
	WRLD_ON,
	
	// parallax displacement
	0		
};

SpriteROMDef FLOOR_22x8_BG_SPRITE_LEFT =
{
	// texture definition
	(TextureDefinition*)&FLOOR_22x8_L_TX,

	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,

	// display mode
	WRLD_LON,

	// parallax displacement
	-1	
};

SpriteROMDef FLOOR_22x8_BG_SPRITE_RIGHT =
{
	// sprite's type
	__TYPE(Sprite),

	// texture definition
	(TextureDefinition*)&FLOOR_22x8_R_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode
	WRLD_RON,

	// parallax displacement
	-1};

SpriteROMDef* FLOOR_22x8_BG_SPRITES[] =
{
	&FLOOR_22x8_BG_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef FLOOR_22x8_BG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            FLOOR_22x8_BG_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 4, 8},

        // in game type
        kSolid,

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
    FTOFIX19_13(0.5f),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};