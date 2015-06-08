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

extern BYTE Floor16x8LTiles[];
extern BYTE Floor16x8LMap[];
extern BYTE Floor16x8RTiles[];
extern BYTE Floor16x8RMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef FLOOR_16x8_L_TX =
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
        Floor16x8LTiles,
    },

    // bgmap definition
    Floor16x8LMap,

    // cols (max 64)
    16 + 1,

    // rows (max 64)
    8 + 1,

    // number of frames
    1,

    // palette number
    1,
};

TextureROMDef FLOOR_16x8_R_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        14,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        Floor16x8RTiles,
    },

    // bgmap definition
    Floor16x8RMap,

    // cols (max 64)
    16 + 1,

    // rows (max 64)
    8 + 1,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef FLOOR_16x8_BG_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_16x8_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

/*
BgmapSpriteROMDef FLOOR_16x8_BG_SPRITE_LEFT =
{
	// texture definition
	(TextureDefinition*)&FLOOR_16x8_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, -1},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_LON,
};

BgmapSpriteROMDef FLOOR_16x8_BG_SPRITE_RIGHT =
{
	// texture definition
	(TextureDefinition*)&FLOOR_16x8_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, -1},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_RON,
};
*/

BgmapSpriteROMDef* const FLOOR_16x8_BG_SPRITES[] =
{
	&FLOOR_16x8_BG_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef FLOOR_16x8_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)FLOOR_16x8_BG_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 4, 8},

        // in game type
        kSolid,

        // width
        // if 0, width and height will be inferred from the texture's size
        0,
        
        // height
        // if 0, width and height will be inferred from the texture's size
        0,
        
        // depth
        20
    },

    // friction FTOFIX19_13
    FTOFIX19_13(40),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};


BgmapSpriteROMDef AFFINE_FLOOR_16x8_BG_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_16x8_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_AFFINE,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const AFFINE_FLOOR_16x8_BG_SPRITES[] =
{
	&AFFINE_FLOOR_16x8_BG_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef AFFINE_FLOOR_16x8_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)AFFINE_FLOOR_16x8_BG_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 4, 8},

        // in game type
        kSolid,

        // width
        // if 0, width and height will be inferred from the texture's size
        0,
        
        // height
        // if 0, width and height will be inferred from the texture's size
        0,
        
        // depth
        20
    },

    // friction FTOFIX19_13
    FTOFIX19_13(0.5f),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};