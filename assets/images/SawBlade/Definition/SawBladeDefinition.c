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

#include <BgmapAnimatedSprite.h>
#include <MovingEntity.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE SawBladeTiles[];
extern BYTE SawBladeMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef SAW_BLADE_SPIN_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{0, 1},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Spin",
};

// an animation definition
AnimationDescriptionROMDef SAW_BLADE_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&SAW_BLADE_SPIN_ANIM,
		NULL,
	}
};

CharSetROMDef SAW_BLADE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	18,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	SawBladeTiles,
};

TextureROMDef SAW_BLADE_TX =
{
	// charset definition
	(CharSetDefinition*)&SAW_BLADE_CH,

	// bgmap definition
	SawBladeMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	2,

	// palette number (0-3)
	1,
};

BgmapSpriteROMDef SAW_BLADE_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&SAW_BLADE_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const SAW_BLADE_SPRITES[] =
{
	&SAW_BLADE_SPRITE,
	NULL
};

MovingEntityROMDef SAW_BLADE_V3_AC =
{
	{
		{
			{
				{
					__TYPE(MovingEntity),
					(SpriteROMDef**)SAW_BLADE_SPRITES,
				},

				// collision detection gap (up, down, left, right)
				{5, 2, 2, 5},

				// in game type
				kSawBlade,

				// width
				0,

				// height
				0,

				// depth
				8,
			},

			// pointer to the animation definition for the character
			(AnimationDescription*)&SAW_BLADE_ANIM,

			// initial animation
			"Spin"
		},

		// friction for physics
		ITOFIX19_13(0),

		// elasticity for physics
		ITOFIX19_13(0),

		// mass
		ITOFIX19_13(10)
	},

	// velocity
	ITOFIX19_13(50),

	// maximum deviation from initial position
	ITOFIX19_13(3 * 8),

	// time to rest idle
	500,

	// axis
	__YAXIS,

	// direction
	__DOWN
};

MovingEntityROMDef SAW_BLADE_H3_AC =
{
	{
		{
			{
				{
					__TYPE(MovingEntity),
					(SpriteROMDef**)SAW_BLADE_SPRITES,
				},

				// collision detection gap (up, down, left, right)
				{5, 2, 2, 5},

				// in game type
				kSawBlade,

				// width
				0,

				// height
				0,

				// depth
				8,
			},

			// pointer to the animation definition for the character
			(AnimationDescription*)&SAW_BLADE_ANIM,

			// initial animation
			"Spin"
		},

		// friction for physics
		ITOFIX19_13(0),

		// elasticity for physics
		ITOFIX19_13(0),

		// mass
		ITOFIX19_13(10)
	},

	// velocity
	ITOFIX19_13(50),

	// maximum deviation from initial position
	ITOFIX19_13(3 * 8),

	// time to rest idle
	1000,

	// axis
	__XAXIS,

	// direction
	__LEFT
};

MovingEntityROMDef SAW_BLADE_H8_AC =
{
	{
		{
			{
				{
					__TYPE(MovingEntity),
					(SpriteROMDef**)SAW_BLADE_SPRITES,
				},

				// collision detection gap (up, down, left, right)
				{5, 2, 2, 5},

				// in game type
				kSawBlade,

				// width
				0,

				// height
				0,

				// depth
				8,
			},

			// pointer to the animation definition for the character
			(AnimationDescription*)&SAW_BLADE_ANIM,

			// initial animation
			"Spin"
		},

		// friction for physics
		ITOFIX19_13(0),

		// elasticity for physics
		ITOFIX19_13(0),

		// mass
		ITOFIX19_13(10)
	},

	// velocity
	ITOFIX19_13(50),

	// maximum deviation from initial position
	ITOFIX19_13(8 * 8),

	// time to rest idle
	0,

	// axis
	__XAXIS,

	// direction
	__LEFT
};
