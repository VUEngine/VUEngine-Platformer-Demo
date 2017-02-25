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

#include <ObjectAnimatedSprite.h>
#include <BgmapAnimatedSprite.h>
#include "MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE SnailTiles[];
extern BYTE SnailMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef SNAIL_MOVE_ANIM =
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
AnimationDescriptionROMDef SNAIL_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&SNAIL_MOVE_ANIM,
		NULL,
	}
};

CharSetROMDef SNAIL_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	6,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED_COORDINATED,

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

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,
};

ObjectSpriteROMDef SNAIL_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&SNAIL_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const SNAIL_SPRITES[] =
{
	&SNAIL_SPRITE,
	NULL
};

MovingEntityROMDef SNAIL_3_AC =
{
	{
		{
			{
				{
					__TYPE(MovingEntity),
					(SpriteROMDef**)SNAIL_SPRITES,
				},

				// collision detection gap (up, down, left, right)
				{6, 0, 5, 3},

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
			(AnimationDescription*)&SNAIL_ANIM,

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
	1000,

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
				{6, 0, 5, 3},

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
			(AnimationDescription*)&SNAIL_ANIM,

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
	ITOFIX19_13(8 * 8),

	// time to rest idle
	3000,

	// axis
	__XAXIS,

	// direction
	__LEFT
};
