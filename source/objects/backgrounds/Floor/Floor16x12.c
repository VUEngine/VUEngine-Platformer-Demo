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

#include <InanimatedInGameEntity.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Floor16x12Tiles[];
extern BYTE Floor16x12Map[];

extern BYTE Floor16TopTiles[];
extern BYTE Floor16TopMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef FLOOR_16x12_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    16,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    Floor16x12Tiles,
};

TextureROMDef FLOOR_16x12_TX =
{
    // charset definition
    (CharSetDefinition*)&FLOOR_16x12_CH,

    // bgmap definition
    Floor16x12Map,

    // cols (max 64)
    16 + 2,

    // rows (max 64)
    12,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef FLOOR_16x12_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_16x12_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

CharSetROMDef FLOOR_16_TOP_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    7,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    Floor16TopTiles,
};

TextureROMDef FLOOR_16_TOP_TX =
{
    // charset definition
    (CharSetDefinition*)&FLOOR_16_TOP_CH,

    // bgmap definition
    Floor16TopMap,

    // cols (max 64)
    16 + 2,

    // rows (max 64)
    2,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef FLOOR_16x12_TOP_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_16_TOP_TX,

	// displacement (x, y, z) (in pixels)
	{0, FTOFIX19_13(-40), FTOFIX19_13(-1)},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const FLOOR_16x12_SPRITES[] =
{
	&FLOOR_16x12_SPRITE,
	&FLOOR_16x12_TOP_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef FLOOR_16x12_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)FLOOR_16x12_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {1, 0, 8, 8},

        // in game type
        kTopSolid,

        // width
        // if 0, width and height will be inferred from the texture's size
        0,
        
        // height
        // if 0, width and height will be inferred from the texture's size
        0,
        
        // depth
        16
    },

    // friction
    FTOFIX19_13(FLOOR_FRICTION),

    // elasticity
    FTOFIX19_13(FLOOR_ELASTICITY),

    // register shape
    true,
};