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
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE LANE_CH[];
extern BYTE LANE_V_6_MP[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef LANE_V_6_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    2,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    LANE_CH,
};

TextureROMDef LANE_V_6_TX =
{
    // charset definition
    (CharSetDefinition*)&LANE_V_6_CH,

    // bgmap definition
    LANE_V_6_MP,

    // cols (max 64)
    1,

    // rows (max 64)
    6,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef LANE_V_6_IM_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&LANE_V_6_TX,

        // displacement
        {0, 0, FTOFIX19_13(2)},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const LANE_V_6_IM_SPRITES[] =
{
	&LANE_V_6_IM_SPRITE,
	NULL
};

ImageROMDef LANE_V_6_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)LANE_V_6_IM_SPRITES,
};