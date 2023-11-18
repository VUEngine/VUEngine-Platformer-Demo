/**
 * VUEngine Platformer Demo
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <BgmapAnimatedSprite.h>
#include <Actor.h>
#include <macros.h>
#include "Cannon.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 CannonTiles[];
extern uint32 CannonTilesFrameOffsets[];
extern uint16 CannonMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec CannonIdleAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

AnimationFunctionROMSpec CannonShootAnimation =
{
	// number of frames of this animation function
	15,

	// frames to play in animation
	{1, 2, 1, 2, 0, 0, 0, 0, 0, 0, 3, 4, 5, 6, 0},

	// number of cycles a frame of animation is displayed
	6,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Cannon_spawnCannonBall,

	// function's name
	"Shoot",
};

// an animation spec
const AnimationFunction* const CannonAnimations[] =
{
	(AnimationFunction*)&CannonIdleAnimation,
	(AnimationFunction*)&CannonShootAnimation,
	NULL,
};

CharSetROMSpec CannonCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	63,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char spec
	CannonTiles,

	// pointer to the frames offsets

	CannonTilesFrameOffsets,
};

TextureROMSpec CannonTexture =
{
	// charset spec
	(CharSetSpec*)&CannonCharset,

	// bgmap spec
	CannonMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	7,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec CannonSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&CannonTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, -1, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const CannonSprites[] =
{
	&CannonSprite,
	NULL
};

ActorROMSpec CannonEntity =
{
	{
		{
			// class allocator
			__TYPE(Cannon),

			// children
			NULL,

			// behaviors
			NULL,

			// extra
			NULL,

			// sprites
			(SpriteSpec**)CannonSprites,

			// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec**)NULL,

	// collision shapes
			(ShapeSpec*)NULL,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kTypeNoShape,

			// physical specification
			(PhysicalSpecification*)NULL,
		},

		// pointer to the animation spec for the character
		(const AnimationFunction**)CannonAnimations,

		// initial animation
		"Idle"
	},

	/// true to create a body
	false,

	/// axis subject to gravity
	__NO_AXIS,

	// axis around which to rotate the entity when syncronizing with body
	__Y_AXIS
};

