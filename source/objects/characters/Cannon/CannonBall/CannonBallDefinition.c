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

AnimationFunction CANNON_BALL_FLY_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{0},
	
	// number of cycles a frame of animation is displayed
	8 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Fly",
};

// an animation definition
AnimationDescription CANNON_BALL_ANIM =
{
	// animation functions
	{
		&CANNON_BALL_FLY_ANIM,
		NULL,
	}
};

CharSetROMDef CANNON_BALL_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    10,

    // allocation type
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

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef CANNON_BALL_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&CANNON_BALL_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
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
			{0, 0, 0, 0},

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
		&CANNON_BALL_ANIM,

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