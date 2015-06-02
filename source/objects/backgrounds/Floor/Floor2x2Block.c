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

extern BYTE Floor2x2BlockLTiles[];
extern BYTE Floor2x2BlockLMap[];
extern BYTE Floor2x2BlockRTiles[];
extern BYTE Floor2x2BlockRMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef FLOOR_2x2_BLOCK_L_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        10,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        Floor2x2BlockLTiles,
    },

    // bgmap definition
    Floor2x2BlockLMap,

    // cols (max 64)
    2 + 1,

    // rows (max 64)
    2 + 1,

    // number of frames
    1,

    // palette number
    1,
};

TextureROMDef FLOOR_2x2_BLOCK_R_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        10,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        Floor2x2BlockRTiles,
    },

    // bgmap definition
    Floor2x2BlockRMap,

    // cols (max 64)
    2 + 1,

    // rows (max 64)
    2 + 1,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef FLOOR_2x2_BLOCK_BG_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_2x2_BLOCK_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,
};

BgmapSpriteROMDef FLOOR_2x2_BLOCK_BG_SPRITE_LEFT =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_2x2_BLOCK_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,

	// display mode
	WRLD_LON,
};

BgmapSpriteROMDef FLOOR_2x2_BLOCK_BG_SPRITE_RIGHT =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_2x2_BLOCK_R_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode
	WRLD_RON,
};

BgmapSpriteROMDef* const FLOOR_2x2_BLOCK_BG_SPRITES[] =
{
	&FLOOR_2x2_BLOCK_BG_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef FLOOR_2x2_BLOCK_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)FLOOR_2x2_BLOCK_BG_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {7, 0, 0, 8},

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
    FTOFIX19_13(50),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};


BgmapSpriteROMDef AFFINE_FLOOR_2x2_BLOCK_BG_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_2x2_BLOCK_L_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_AFFINE,
	
	// display mode
	WRLD_ON,
};



BgmapSpriteROMDef* const AFFINE_FLOOR_2x2_BLOCK_BG_SPRITES[] =
{
	&AFFINE_FLOOR_2x2_BLOCK_BG_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef AFFINE_FLOOR_2x2_BLOCK_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)AFFINE_FLOOR_2x2_BLOCK_BG_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {7, 0, 0, 8},

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
    FTOFIX19_13(1.0f),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};
