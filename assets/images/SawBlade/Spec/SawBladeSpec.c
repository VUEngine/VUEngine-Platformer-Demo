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
#include <MovingEntity.h>
#include <Ball.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 SawBladeTiles[];
extern uint32 SawBladeTilesFrameOffsets[];
extern uint16 SawBladeMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec SawBladeSpinAnimation =
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
const AnimationFunction* const SawBladeAnimations[] =
{
	(AnimationFunction*)&SawBladeSpinAnimation,
	NULL,
};

CharSetROMSpec SawBladeCharset =
{
	// number of chars in function of the number of frames to load at the same time
	18,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	SawBladeTiles,

	// pointer to the frames offsets
	SawBladeTilesFrameOffsets,
};

TextureROMSpec SawBladeTexture =
{
	// charset spec
	(CharSetSpec*)&SawBladeCharset,

	// bgmap spec
	SawBladeMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames
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

BgmapSpriteROMSpec SawBladeSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&SawBladeTexture,

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

BgmapSpriteROMSpec* const SawBladeSprites[] =
{
	&SawBladeSprite,
	NULL
};

ShapeROMSpec SawBladeShapes[] =
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

MovingEntityROMSpec SawBladeV3Entity =
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
				(SpriteSpec**)SawBladeSprites,

				// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec**)NULL,

	// collision shapes
				(ShapeSpec*)SawBladeShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSawBlade,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(const AnimationFunction**)SawBladeAnimations,

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

MovingEntityROMSpec SawBladeH3Entity =
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
				(SpriteSpec**)SawBladeSprites,

				// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec**)NULL,

	// collision shapes
				(ShapeSpec*)SawBladeShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSawBlade,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(const AnimationFunction**)SawBladeAnimations,

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

MovingEntityROMSpec SawBladeH8Entity =
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
				(SpriteSpec**)SawBladeSprites,

				// use z displacement in projection
	false,
			
	/// meshes
	(WireframeSpec**)NULL,

	// collision shapes
				(ShapeSpec*)SawBladeShapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{0, 0, 0},

				// gameworld's character's type
				kTypeSawBlade,

				// physical specification
				(PhysicalSpecification*)NULL,
			},

			// pointer to the animation spec for the character
			(const AnimationFunction**)SawBladeAnimations,

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
