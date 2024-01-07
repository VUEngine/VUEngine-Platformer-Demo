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
#include <Box.h>
#include "CannonBall.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 CannonBallTiles[];
extern uint16 CannonBallMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec CannonBallFlyAnimation =
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

// an animation spec
const AnimationFunction* const CannonBallAnimations[] =
{
	(AnimationFunction*)&CannonBallFlyAnimation,
	NULL,
};

CharSetROMSpec CannonBallCharset =
{
	// number of chars in function of the number of frames to load at the same time
	9,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	CannonBallTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec CannonBallTexture =
{
	// charset spec
	(CharSetSpec*)&CannonBallCharset,

	// bgmap spec
	CannonBallMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{1, 1},

	// number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec CannonBallSprite =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&CannonBallTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const CannonBallSprites[] =
{
	&CannonBallSprite,
	NULL
};

ColliderROMSpec CannonBallColliders[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{22, 22, 16},

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
		kLayerAll,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

CannonBallROMSpec CannonBallEntity =
{
	{
		{
			// class allocator
			__TYPE(CannonBall),

			// children
			NULL,

			// behaviors
			NULL,

			// extra
			NULL,

			// sprites
			(SpriteSpec**)CannonBallSprites,

			// use z displacement in projection
			false,
			
			/// meshes
			(WireframeSpec**)NULL,

			// collision shapes
			(ColliderSpec*)CannonBallColliders,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kTypeCannonBall,

			// physical specification
			(PhysicalProperties*)NULL,
		},

		// pointer to the animation spec for the character
		(const AnimationFunction**)CannonBallAnimations,

		// initial animation
		NULL
	},

	/// true to create a body
	true,

	/// axis subject to gravity
	__NO_AXIS,

	// axis around which to rotate the entity when syncronizing with body
	__NO_AXIS
};

PositionedEntityROMSpec CannonBallPositionedEntity =
{
	(EntitySpec*)&CannonBallEntity,
	{0, 0, -SORT_INCREMENT, 0},
	0,
	NULL,
	NULL,
	NULL,
	false
};