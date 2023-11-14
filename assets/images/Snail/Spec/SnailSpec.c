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

#include <ObjectAnimatedSprite.h>
#include <BgmapAnimatedSprite.h>
#include <Ball.h>
#include "MovingEntity.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 SnailTiles[];
extern uint32 SnailTilesFrameOffsets[];
extern uint16 SnailMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec SnailMoveAnimation =
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

// an animation spec
AnimationDescriptionROMSpec SnailAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&SnailMoveAnimation,
		NULL,
	}
};

CharSetROMSpec SnailCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	12,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char spec
	SnailTiles,

	// pointer to the frames offsets
	SnailTilesFrameOffsets,
};

TextureROMSpec SnailTexture =
{
	// charset spec
	(CharSetSpec*)&SnailCharset,

	// bgmap spec
	SnailMap,

	// cols (max 64)
	3,

	// rows (max 64)
	2,

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

ObjectSpriteROMSpec SnailSprite =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&SnailTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, FOREGROUND_ENEMIES_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const SnailSprites[] =
{
	&SnailSprite,
	NULL
};

ShapeROMSpec SnailShapes[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{14, 14, 14},

		// displacement (x, y, z, p)
		{0, 2, 0, 0},

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

MovingEntityROMSpec Snail3Entity =
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
				(SpriteSpec**)SnailSprites,

				// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec**)NULL,

	// collision shapes
				(ShapeSpec*)SnailShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSnail,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&SnailAnimation,

			// initial animation
			"Move"
		},

		/// true to create a body
		true,

		/// axis subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__Y_AXIS
	},

	// velocity
	__F_TO_FIX10_6(0.5f),

	// maximum deviation from initial position
	__F_TO_FIX10_6(1.5f),

	// time to rest idle
	1500,

	// axis
	__X_AXIS,

	// direction
	__LEFT,

	// axis on which synchronize shape with direction
	__ALL_AXIS,
};

MovingEntityROMSpec Snail8Entity =
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
				(SpriteSpec**)SnailSprites,

				// use z displacement in projection
				false,
			
				/// meshes
				(WireframeSpec**)NULL,

				// collision shapes
				(ShapeSpec*)SnailShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSnail,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&SnailAnimation,

			// initial animation
			"Move"
		},

		/// true to create a body
		true,

		/// axis subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__Y_AXIS
	},

	// velocity
	__F_TO_FIX10_6(0.5f),

	// maximum deviation from initial position
	__F_TO_FIX10_6(4),

	// time to rest idle
	1500,

	// axis
	__X_AXIS,

	// direction
	__LEFT,

	// axis on which synchronize shape with direction
	__ALL_AXIS,
};
