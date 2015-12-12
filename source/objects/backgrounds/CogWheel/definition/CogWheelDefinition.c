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
#include <InAnimatedInGameEntity.h>
#include <macros.h>
#include <CogWheel.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CogWheelTiles[];
extern BYTE CogWheelMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef COG_WHEEL_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        367,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        CogWheelTiles,
    },

    // bgmap definition
    CogWheelMap,

    // cols (max 64)
    42,

    // rows (max 64)
    42,

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef COG_WHEEL_BG_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&COG_WHEEL_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, -2},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const COG_WHEEL_BG_SPRITES[] =
{
	&COG_WHEEL_BG_SPRITE,
	NULL
};

InanimatedInGameEntityROMDef COG_WHEEL_IG =
{
    {
        {
            __TYPE(CogWheel),
            (SpriteROMDef**)COG_WHEEL_BG_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {0, 0, 0, 0},

        // in game type
        kNotSolid,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

        // depth
        1
    },

    // friction FTOFIX19_13
    FTOFIX19_13(0.0f),

    // elasticity FTOFIX19_13
    FTOFIX19_13(0.0f),

    // register shape
    false,
};