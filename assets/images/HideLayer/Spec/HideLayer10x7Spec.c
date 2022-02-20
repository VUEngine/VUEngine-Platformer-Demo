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
#include <macros.h>
#include <BgmapAnimatedSprite.h>
#include <AnimatedEntity.h>
#include <Box.h>
#include "HideLayer.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 HideLayer10x7Tiles[];
extern uint32 HideLayer10x7TilesFrameOffsets[];
extern uint16 HideLayer10x7Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec HideLayer10x7SolidAnimation =
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
	"Shape",
};

AnimationFunctionROMSpec HideLayer10x7TransparentAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{6},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Transparent",
};

AnimationFunctionROMSpec HideLayer10x7_TOSolidAnimation =
{
	// number of frames of this animation function
	7,

	// frames to play in animation
	{6, 5, 4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"ToShape",
};

AnimationFunctionROMSpec HideLayer10x7_TOTransparentAnimation =
{
	// number of frames of this animation function
	7,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)NULL,

	// function's name
	"ToTransparent",
};

// an animation spec
AnimationDescriptionROMSpec HideLayer10x7Animation =
{
	// animation functions
	{
		(AnimationFunction*)&HideLayer10x7SolidAnimation,
		(AnimationFunction*)&HideLayer10x7TransparentAnimation,
		(AnimationFunction*)&HideLayer10x7_TOSolidAnimation,
		(AnimationFunction*)&HideLayer10x7_TOTransparentAnimation,
		NULL,
	}
};

CharSetROMSpec HideLayer10x7Charset =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	70,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char spec
	HideLayer10x7Tiles,

	// pointer to the frames offsets
	HideLayer10x7TilesFrameOffsets,
};

TextureROMSpec HideLayer10x7Texture =
{
	// charset spec
	(CharSetSpec*)&HideLayer10x7Charset,

	// bgmap spec
	HideLayer10x7Map,

	// cols (max 64)
	10,

	// rows (max 64)
	7,

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

BgmapSpriteROMSpec HideLayer10x7Sprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HideLayer10x7Texture,

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

BgmapSpriteROMSpec* const HideLayer10x7Sprites[] =
{
	&HideLayer10x7Sprite,
	NULL
};

ShapeROMSpec HideLayer10x7Shapes[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{80, 56, 16},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerTriggers,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

HideLayerROMSpec HideLayer10x7Entity =
{
	{
		// class allocator
		__TYPE(HideLayer),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)HideLayer10x7Sprites,

		// use z displacement in projection
		false,

		// collision shapes
		(ShapeSpec*)HideLayer10x7Shapes,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeHideLayer,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&HideLayer10x7Animation,

	// initial animation
	"Shape",
};
