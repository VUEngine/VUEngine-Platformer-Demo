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

extern BYTE Floor22TopTiles[];
extern BYTE Floor22TopMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef FLOOR_22x12_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    16,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    Floor22x12Tiles,
};

TextureROMDef FLOOR_22x12_TX =
{
    // charset definition
    (CharSetDefinition*)&FLOOR_22x12_CH,

    // bgmap definition
    Floor22x12Map,

    // cols (max 64)
    22 + 2,

    // rows (max 64)
    12,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef FLOOR_22x12_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&FLOOR_22x12_TX,

        // displacement
        {0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

CharSetROMDef FLOOR_22_TOP_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    7,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    Floor22TopTiles,
};

TextureROMDef FLOOR_22_TOP_TX =
{
    // charset definition
    (CharSetDefinition*)&FLOOR_22_TOP_CH,

    // bgmap definition
    Floor22TopMap,

    // cols (max 64)
    22 + 2,

    // rows (max 64)
    2,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef FLOOR_22x12_TOP_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&FLOOR_22_TOP_TX,

        // displacement
        {0, FTOFIX19_13(-40), FTOFIX19_13(-1)},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const FLOOR_22x12_SPRITES[] =
{
	&FLOOR_22x12_SPRITE,
//	&FLOOR_22x12_TOP_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef FLOOR_22x12_IG =
{
    {
        {
            __TYPE(InanimatedInGameEntity),
            (SpriteROMDef**)FLOOR_22x12_SPRITES,
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
