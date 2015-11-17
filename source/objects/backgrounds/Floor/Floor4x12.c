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

extern BYTE Floor4x12Tiles[];
extern BYTE Floor4x12Map[];

extern BYTE Floor4TopTiles[];
extern BYTE Floor4TopMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef FLOOR_4x12_TX =
{
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
        Floor4x12Tiles,
    },

    // bgmap definition
    Floor4x12Map,

    // cols (max 64)
    4 + 2,

    // rows (max 64)
    12,

    // number of frames
    1,

    // palette number
    1,
};

ObjectSpriteROMDef FLOOR_4x12_SPRITE =
{
	// sprite's type
	__TYPE(ObjectSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_4x12_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_OBJ,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};
TextureROMDef FLOOR_4_TOP_TX =
{
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
        Floor4TopTiles,
    },

    // bgmap definition
    Floor4TopMap,

    // cols (max 64)
    4 + 2,

    // rows (max 64)
    2,

    // number of frames
    1,

    // palette number
    1,
};

ObjectSpriteROMDef FLOOR_4x12_TOP_SPRITE =
{
	// sprite's type
	__TYPE(ObjectSprite),

	// texture definition
	(TextureDefinition*)&FLOOR_4_TOP_TX,

	// displacement (x, y, z) (in pixels)
	{0, -40, -1},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_OBJ,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const FLOOR_4x12_SPRITES[] =
{
	&FLOOR_4x12_SPRITE,
	&FLOOR_4x12_TOP_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef FLOOR_4x12_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)FLOOR_4x12_SPRITES,
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

    // friction FTOFIX19_13
    FTOFIX19_13(40),

    // elasticity FTOFIX19_13
    FTOFIX19_13(1.0f),

    // register shape
    true,
};