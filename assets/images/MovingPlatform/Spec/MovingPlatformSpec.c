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

#include <BgmapSprite.h>
#include <MovingEntity.h>
#include <Box.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 MovingPlatform4Tiles[];
extern uint16 MovingPlatform4Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec MovingPlatformMoveAnimation =
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

// an animation spec
AnimationDescriptionROMSpec MovingPlatformAnimation =
{
	// animation functions
	{
		(AnimationFunction*)&MovingPlatformMoveAnimation,
		NULL,
	}
};

CharSetROMSpec MovingPlatformCharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	MovingPlatform4Tiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec MovingPlatformTexture =
{
	// charset spec
	(CharSetSpec*)&MovingPlatformCharset,

	// bgmap spec
	MovingPlatform4Map,

	// cols (max 64)
	4,

	// rows (max 64)
	1,

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

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec MovingPlatformSprite =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&MovingPlatformTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, -4, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const MovingPlatformSprites[] =
{
	&MovingPlatformSprite,
	NULL
};

ShapeROMSpec MovingPlatformV6Shapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{30, 32, 16},

		// displacement (x, y, z, p)
		{0, 8, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerMovingPlatforms,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

PhysicalSpecificationROMSpec MovingPlatformV6PhysicalProperties =
{
	// mass
	__F_TO_FIX10_6(0),

	// friction
	__F_TO_FIX10_6(FLOOR_FRICTION),

	// bounciness
	__F_TO_FIX10_6(FLOOR_BOUNCINESS),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)},

	// maximum speed
	__I_TO_FIX10_6(0)
};

MovingEntityROMSpec MovingPlatformV6Entity =
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
				(SpriteSpec**)MovingPlatformSprites,

				// use z displacement in projection
	false,
			
	/// meshes
	(MeshSpec*)NULL,

	// collision shapes
				(ShapeSpec*)MovingPlatformV6Shapes,

				// size
				// if 0, width and height will be inferred from the first sprite's texture's size
				{4 * 8, 2 * 8, 4},

				// gameworld's character's type
				kTypeMovingPlatform,

				// physical specification
				(PhysicalSpecification*)&MovingPlatformV6PhysicalProperties,
			},

			// pointer to the animation spec for the character
			(AnimationDescription*)&MovingPlatformAnimation,

			// initial animation
			"Move"
		},

		/// true to create a body
		true,

		/// axis subject to gravity
		__NO_AXIS,

		// axis around which to rotate the entity when syncronizing with body
		__NO_AXIS
	},

	// velocity
	__I_TO_FIX10_6(2),

	// maximum deviation from initial position
	__I_TO_FIX10_6(3),

	// time to rest idle
	1000,

	// axis
	__Y_AXIS,

	// direction
	__DOWN,

	// axis on which synchronize shape with direction
	__NO_AXIS,
};
