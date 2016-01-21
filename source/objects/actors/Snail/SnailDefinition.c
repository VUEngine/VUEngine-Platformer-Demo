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

#include <BgmapAnimatedSprite.h>
#include "MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE SnailTiles[];
extern BYTE SnailMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunction SNAIL_MOVE_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{0, 1},
	
	// number of cycles a frame of animation is displayed
	16,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Move",
};

// an animation definition
AnimationDescription SNAIL_ANIM =
{
	// animation functions
	{
		&SNAIL_MOVE_ANIM,
		NULL,
	}
};

CharSetROMDef SNAIL_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    18,

    // allocation type
    __ANIMATED_MULTI,

    // char definition
    SnailTiles,
};

TextureROMDef SNAIL_TX =
{
    // charset definition
    (CharSetDefinition*)&SNAIL_CH,

    // bgmap definition
    SnailMap,

    // cols (max 64)
    3,

    // rows (max 64)
    2,

    // number of frames
    3,

    // palette number
    1,
};

BgmapSpriteROMDef SNAIL_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&SNAIL_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_AFFINE,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const SNAIL_SPRITES[] =
{
	&SNAIL_SPRITE,
	NULL
};

MovingEntityROMDef SNAIL_4_AC =
{
	{
	    {
	        {
	            {
	                __TYPE(MovingEntity),
	                (SpriteROMDef**)SNAIL_SPRITES,
	            },
	
	            // collision detection gap (up, down, left, right)
	            {8, 0, 4, 4},

	            // in game type
	            kSnail,
	
	            // width
	            0,
	            
	            // height
	            0,
	            
	            // depth
	            8,
	        },
	
	        // pointer to the animation definition for the character
	        &SNAIL_ANIM,
	
	        // initial animation
	        "Move"
	    },
	    
		// friction for physics
		ITOFIX19_13(0),

		// elasticity for physics
		ITOFIX19_13(0),
		
		// mass
		ITOFIX19_13(10)
	},
	
	// velocity
	ITOFIX19_13(20),

	// maximum deviation from initial position
	ITOFIX19_13(3 * 8),

	// time to rest idle
	3000,

    // axis
    __XAXIS,

    // direction
    __LEFT

};

MovingEntityROMDef SNAIL_8_AC =
{
	{
	    {
	        {
	            {
	                __TYPE(MovingEntity),
	                (SpriteROMDef**)SNAIL_SPRITES,
	            },

	            // collision detection gap (up, down, left, right)
	            {8, 0, 4, 4},

	            // in game type
	            kSnail,

	            // width
	            0,

	            // height
	            0,

	            // depth
	            8,
	        },

	        // pointer to the animation definition for the character
	        &SNAIL_ANIM,

	        // initial animation
	        "Move"
	    },

		// friction for physics
		ITOFIX19_13(0),

		// elasticity for physics
		ITOFIX19_13(0),

		// mass
		ITOFIX19_13(10)
	},

	// velocity
	ITOFIX19_13(20),

	// maximum deviation from initial position
	ITOFIX19_13(64),

	// time to rest idle
	3000,

    // axis
    __XAXIS,

    // direction
    __LEFT
};