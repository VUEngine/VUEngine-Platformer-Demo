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

extern BYTE Floor22x12Tiles[];
extern BYTE Floor22x12Map[];

extern TextureROMDef FLOOR_22_TOP_TX;


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef FLOOR_22x5_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    16,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    Floor22x12Tiles,
};

TextureROMDef FLOOR_22x5_TX =
{
    // charset definition
    (CharSetDefinition*)&FLOOR_22x5_CH,

    // bgmap definition
    Floor22x12Map,

    // cols (max 64)
    22 + 2,

    // rows (max 64)
    5,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef FLOOR_22x5_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_22x5_TX,

	// displacement vector
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef FLOOR_22x5_TOP_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_22_TOP_TX,

	// displacement vector
	{0, FTOFIX19_13(-12), FTOFIX19_13(-1)},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const FLOOR_22x5_SPRITES[] =
{
	&FLOOR_22x5_SPRITE,
	&FLOOR_22x5_TOP_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef FLOOR_22x5_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)FLOOR_22x5_SPRITES,
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