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

#include <Libgccvb.h>
#include <BgmapAnimatedSprite.h>
#include <PlatformerCameraTriggerEntity.h>
#include <Ball.h>
#include <InverseBox.h>

#include "Hero.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HeroTiles[];
extern BYTE HeroBandanaTiles[];
extern BYTE HeroMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_IDLE_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{4, 5},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_WALKING_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{13, 14},

	// number of cycles a frame of animation is displayed
	10,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Walk",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_JUMPING_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{6},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Jump",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_FALLING_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{7},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Fall",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_SLIDING_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{7},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Slide",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_HIT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{8},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hit",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_CLIMB_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{9, 10},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Climb",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_FRONT_ANIM =
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
	"Front",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_BACK_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{2, 3},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Back",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_WALKING_FRONT_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{17, 18},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"WalkingFront",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_WALKING_BACK_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{15, 16},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"WalkingBack",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_TRANSITION_ANIM =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{19, 20, 21, 22, 23},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hero_onPowerUpTransitionComplete,

	// function's name
	"Transition",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HERO_SLEEP_ANIM =
{
	// number of frames of this animation function
	10,

	// frames to play in animation
	{24, 24, 24, 24, 24, 25, 26, 27, 26, 25},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Sleep",
};


// an animation spec
AnimationDescriptionROMSpec HERO_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HERO_IDLE_ANIM,
		(AnimationFunction*)&HERO_WALKING_ANIM,
		(AnimationFunction*)&HERO_JUMPING_ANIM,
		(AnimationFunction*)&HERO_FALLING_ANIM,
		(AnimationFunction*)&HERO_SLIDING_ANIM,
		(AnimationFunction*)&HERO_HIT_ANIM,
		(AnimationFunction*)&HERO_CLIMB_ANIM,
		(AnimationFunction*)&HERO_FRONT_ANIM,
		(AnimationFunction*)&HERO_BACK_ANIM,
		(AnimationFunction*)&HERO_WALKING_FRONT_ANIM,
		(AnimationFunction*)&HERO_WALKING_BACK_ANIM,
		(AnimationFunction*)&HERO_TRANSITION_ANIM,
		(AnimationFunction*)&HERO_SLEEP_ANIM,
		NULL,
	}
};

CharSetROMSpec HERO_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	9,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	HeroTiles,
};

CharSetROMSpec HERO_BANDANA_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	9,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	HeroBandanaTiles,
};

TextureROMSpec HERO_TX =
{
	(CharSetSpec*)&HERO_CH,

	// bgmap spec
	HeroMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{1, 1},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,
};

TextureROMSpec HERO_BANDANA_TX =
{
	(CharSetSpec*)&HERO_BANDANA_CH,

	// bgmap spec
	HeroMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,
};

BgmapSpriteROMSpec HERO_AFFINE_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HERO_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, HERO_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec HERO_BANDANA_AFFINE_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HERO_BANDANA_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, HERO_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec HERO_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HERO_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const HERO_AFFINE_SPRITES[] =
{
	&HERO_AFFINE_SPRITE,
	NULL
};

BgmapSpriteROMSpec* const HERO_BANDANA_AFFINE_SPRITES[] =
{
	&HERO_BANDANA_AFFINE_SPRITE,
	NULL
};

BgmapSpriteROMSpec* const HERO_SPRITES[] =
{
	&HERO_SPRITE,
	NULL
};

ShapeROMSpec HERO_AC_SHAPES[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{14, 14, 14},

		// displacement (x, y, z, p)
		{-1, 4, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		true,

		/// layers in which I live
		kPlayerLayer,

		/// layers to ignore when checking for collisions
		kParticlesLayer | kCameraLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

PhysicalSpecificationROMSpec HERO_PHYSICAL_PROPERTIES =
{
	// mass
	__F_TO_FIX10_6(0.65f),

	// friction
	__F_TO_FIX10_6(0),

	// bounciness
	__F_TO_FIX10_6(HERO_BOUNCINESS),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)}
};

HeroROMSpec HERO_AC =
{
	{
		{
			// class allocator
			__TYPE(Hero),

			// sprites
			(SpriteROMSpec**)HERO_AFFINE_SPRITES,

			// collision shapes
			(ShapeSpec*)HERO_AC_SHAPES,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kHero,

			// physical specification
			(PhysicalSpecification*)&HERO_PHYSICAL_PROPERTIES,
		},

		// pointer to the animation spec for the character
		(AnimationDescription*)&HERO_ANIM,

		// initial animation
		"Idle",
	},

	/// true to create a body
	true,

	/// axes subject to gravity
	__Y_AXIS
};

AnimatedEntityROMSpec HERO_IDLE_AG =
{
	{
		// class allocator
		__TYPE(AnimatedEntity),

		// sprites
		(SpriteROMSpec**)HERO_SPRITES,

		// collision shapes
		(ShapeSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kHero,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the character
	(AnimationDescription*)&HERO_ANIM,

	// initial animation
	"Idle",
};

AnimatedEntityROMSpec HERO_SLEEPING_AG =
{
	{
		// class allocator
		__TYPE(AnimatedEntity),

		// sprites
		(SpriteROMSpec**)HERO_SPRITES,

		// collision shapes
		(ShapeSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kHero,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the character
	(AnimationDescription*)&HERO_ANIM,

	// initial animation
	"Sleep",
};


AnimatedEntityROMSpec HERO_BANDANA_AG =
{
	{
		// class allocator
		__TYPE(AnimatedEntity),

		// sprites
		(SpriteROMSpec**)HERO_BANDANA_AFFINE_SPRITES,

		// collision shapes
		(ShapeSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kHero,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the character
	(AnimationDescription*)&HERO_ANIM,

	// initial animation
	"Idle",
};


