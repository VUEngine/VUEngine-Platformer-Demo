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

#include <BgmapSprite.h>
#include <MovingEntity.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE MovingPlatform4Tiles[];
extern BYTE MovingPlatform4Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef MOVING_PLATFORM_MOVE_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Move",
};

// an animation definition
AnimationDescriptionROMDef MOVING_PLATFORM_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&MOVING_PLATFORM_MOVE_ANIM,
		NULL,
	}
};

CharSetROMDef MOVING_PLATFORM_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    4,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SINGLE,

    // char definition
    MovingPlatform4Tiles,
};

TextureROMDef MOVING_PLATFORM_TX =
{
    // charset definition
    (CharSetDefinition*)&MOVING_PLATFORM_CH,

    // bgmap definition
    MovingPlatform4Map,

    // cols (max 64)
    4,

    // rows (max 64)
    1,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef MOVING_PLATFORM_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&MOVING_PLATFORM_TX,

        // displacement
        {0, ITOFIX19_13(-4), 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const MOVING_PLATFORM_SPRITES[] =
{
	&MOVING_PLATFORM_SPRITE,
	NULL
};

MovingEntityROMDef MOVING_PLATFORM_V6_AC =
{
	{
	    {
	        {
	            {
	                __TYPE(MovingEntity),
	                (SpriteROMDef**)MOVING_PLATFORM_SPRITES,
	            },

	            // collision detection gap (up, down, left, right)
	            {1, 1, 1, 1},

	            // in game type
	            kMovingPlatform,

	            // width
	            4 * 8,

	            // height
	            2 * 8,

	            // depth
	            4
	        },

	        // pointer to the animation definition for the character
	        (AnimationDescription*)&MOVING_PLATFORM_ANIM,

	        // initial animation
	        "Move"
	    },

		// friction for physics
		FTOFIX19_13(FLOOR_FRICTION),

		// elasticity for physics
		FTOFIX19_13(FLOOR_ELASTICITY),

		// mass
		ITOFIX19_13(10)
	},

	// velocity
	ITOFIX19_13(48),

	// maximum deviation from initial position
	ITOFIX19_13(48),

	// time to rest idle
	1000,

    // axis
    __YAXIS,

    // direction
    __DOWN
};
