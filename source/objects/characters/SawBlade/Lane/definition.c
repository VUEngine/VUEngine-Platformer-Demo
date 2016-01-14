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

extern BYTE SAW_BLADE_LANE_CH[];
extern BYTE SAW_BLADE_LANE_V_6_MP[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef SAW_BLADE_LANE_V_6_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    2,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    SAW_BLADE_LANE_CH,
};

TextureROMDef SAW_BLADE_LANE_V_6_TX =
{
    // charset definition
    (CharSetDefinition*)&SAW_BLADE_LANE_V_6_CH,

    // bgmap definition
    SAW_BLADE_LANE_V_6_MP,

    // cols (max 64)
    1,

    // rows (max 64)
    6,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef SAW_BLADE_LANE_V_6_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&SAW_BLADE_LANE_V_6_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, FTOFIX19_13(2)},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const SAW_BLADE_LANE_V_6_IM_SPRITES[] =
{
	&SAW_BLADE_LANE_V_6_IM_SPRITE,
	NULL
};

ImageROMDef SAW_BLADE_LANE_V_6_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)SAW_BLADE_LANE_V_6_IM_SPRITES,
};