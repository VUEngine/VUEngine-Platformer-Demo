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
#include "CannonBall.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CannonBallTiles[];
extern BYTE CannonBallMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef CANNON_BALL_FLY_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Fly",
};

// an animation definition
AnimationDescriptionROMDef CANNON_BALL_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&CANNON_BALL_FLY_ANIM,
		NULL,
	}
};

CharSetROMDef CANNON_BALL_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    10,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_MULTI,

    // char definition
    CannonBallTiles,
};

TextureROMDef CANNON_BALL_TX =
{
    // charset definition
    (CharSetDefinition*)&CANNON_BALL_CH,

    // bgmap definition
    CannonBallMap,

    // cols (max 64)
    3,

    // rows (max 64)
    3,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef CANNON_BALL_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&CANNON_BALL_TX,

        // displacement
        {0, 0, 0},
    },

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_AFFINE,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const CANNON_BALL_SPRITES[] =
{
	&CANNON_BALL_SPRITE,
	NULL
};

ActorROMDef CANNON_BALL_AC =
{
	{
		{
			{
				__TYPE(CannonBall),
				(SpriteROMDef**)CANNON_BALL_SPRITES,
			},

			// collision detection gap (up, down, left, right)
			{1, 1, 1, 1},

			// in game type
			kCannonBall,

			// width
			0,

			// height
			0,

			// depth
			1
		},

		// pointer to the animation definition for the character
		(AnimationDescription*)&CANNON_BALL_ANIM,

		// initial animation
		NULL
	},

	// friction for physics
	ITOFIX19_13(0),

	// elasticity for physics
	ITOFIX19_13(0),

	// mass
	ITOFIX19_13(10)
};
