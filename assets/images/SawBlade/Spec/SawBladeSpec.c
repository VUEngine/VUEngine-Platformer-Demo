/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <Ball.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE SawBladeTiles[];
extern BYTE SawBladeMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec SAW_BLADE_SPIN_ANIM =
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

// an animation spec
AnimationDescriptionROMSpec SAW_BLADE_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&SAW_BLADE_SPIN_ANIM,
		NULL,
	}
};

CharSetROMSpec SAW_BLADE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	18,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char spec
	SawBladeTiles,
};

TextureROMSpec SAW_BLADE_TX =
{
	// charset spec
	(CharSetSpec*)&SAW_BLADE_CH,

	// bgmap spec
	SawBladeMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	2,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec SAW_BLADE_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&SAW_BLADE_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, FOREGROUND_ENEMIES_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const SAW_BLADE_SPRITES[] =
{
	&SAW_BLADE_SPRITE,
	NULL
};

ShapeROMSpec SAW_BLADE_AC_SHAPES[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{18, 18, 18},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerEnemies,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

MovingEntityROMSpec SAW_BLADE_V3_AC =
{
	{
		{
			{
				// class allocator
				__TYPE(MovingEntity),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,

				// sprites
				(SpriteSpec**)SAW_BLADE_SPRITES,

				// use z displacement in projection
	false,

	// collision shapes
				(ShapeSpec*)SAW_BLADE_AC_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSawBlade,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&SAW_BLADE_ANIM,

			// initial animation
			"Spin"
		},

		/// true to create a body
		true,

		/// axis subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__NO_AXIS
	},

	// velocity
	__F_TO_FIX10_6(2),

	// maximum deviation from initial position
	__F_TO_FIX10_6(1.5f),

	// time to rest idle
	750,

	// axis
	__Y_AXIS,

	// direction
	__DOWN,

	// axis on which synchronize shape with direction
	__ALL_AXIS,
};

MovingEntityROMSpec SAW_BLADE_H3_AC =
{
	{
		{
			{
				// class allocator
				__TYPE(MovingEntity),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,

				// sprites
				(SpriteSpec**)SAW_BLADE_SPRITES,

				// use z displacement in projection
	false,

	// collision shapes
				(ShapeSpec*)SAW_BLADE_AC_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSawBlade,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&SAW_BLADE_ANIM,

			// initial animation
			"Spin"
		},

		/// true to create a body
		true,

		/// axis subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__NO_AXIS
	},

	// velocity
	__F_TO_FIX10_6(2),

	// maximum deviation from initial position
	__F_TO_FIX10_6(1.5f),

	// time to rest idle
	750,

	// axis
	__X_AXIS,

	// direction
	__LEFT,

	// axis on which synchronize shape with direction
	__ALL_AXIS,
};

MovingEntityROMSpec SAW_BLADE_H8_AC =
{
	{
		{
			{
				// class allocator
				__TYPE(MovingEntity),

				// children
				NULL,

				// behaviors
				NULL,

				// extra
				NULL,

				// sprites
				(SpriteSpec**)SAW_BLADE_SPRITES,

				// use z displacement in projection
	false,

	// collision shapes
				(ShapeSpec*)SAW_BLADE_AC_SHAPES,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSawBlade,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&SAW_BLADE_ANIM,

			// initial animation
			"Spin"
		},

		/// true to create a body
		true,

		/// axis subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__NO_AXIS
	},

	// velocity
	__F_TO_FIX10_6(2),

	// maximum deviation from initial position
	__F_TO_FIX10_6(4),

	// time to rest idle
	750,

	// axis
	__X_AXIS,

	// direction
	__LEFT,

	// axis on which synchronize shape with direction
	__ALL_AXIS,
};
