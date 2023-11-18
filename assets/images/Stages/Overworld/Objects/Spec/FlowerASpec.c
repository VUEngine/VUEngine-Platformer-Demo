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

#include <Libgccvb.h>
#include <AnimatedEntity.h>
#include <BgmapAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 FlowerATiles[];
extern uint32 FlowerATilesFrameOffsets[];
extern uint16 FlowerAMap[];


//---------------------------------------------------------------------------------------------------------
//												ANIMATION DEFINITION
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec FlowerADefaultAnimation =
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
	"Default",
};

// an animation spec
const AnimationFunction* const FlowerAAnimations[] =
{
	(AnimationFunction*)&FlowerADefaultAnimation,
	NULL,
};


//---------------------------------------------------------------------------------------------------------
//											SPRITE DEFINITION
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec FlowerACharset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	2,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED,

	// char spec
	FlowerATiles,

	// pointer to the frames offsets
	FlowerATilesFrameOffsets,
};

TextureROMSpec FlowerATexture =
{
	// charset spec
	(CharSetSpec*)&FlowerACharset,

	// bgmap spec
	FlowerAMap,

	// cols (max 64)
	2,

	// rows (max 64)
	1,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec FlowerASprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&FlowerATexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{__F_TO_FIX10_6(0), __F_TO_FIX10_6(0), __F_TO_FIX10_6(0), 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const FlowerASprites[] =
{
	&FlowerASprite,
	NULL
};


//---------------------------------------------------------------------------------------------------------
//											ENTITY DEFINITION
//---------------------------------------------------------------------------------------------------------

AnimatedEntityROMSpec FlowerAEntity =
{
	{
		// class allocator
		__TYPE(AnimatedEntity),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)FlowerASprites,

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

	// pointer to the animation spec for the item
	(const AnimationFunction**)FlowerAAnimations,

	// initial animation
	"Default",
};
