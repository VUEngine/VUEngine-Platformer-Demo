/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <BgmapSprite.h>
#include <MovingEntity.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE MovingPlatform4Tiles[];
extern BYTE MovingPlatform4Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
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

		// transparent
		false,

		// displacement
		{0, ITOFIX19_13(-4), 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
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
