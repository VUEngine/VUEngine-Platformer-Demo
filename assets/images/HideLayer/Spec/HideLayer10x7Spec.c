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

extern BYTE HideLayer10x7Tiles[];
extern BYTE HideLayer10x7Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMSpec HIDE_LAYER_10x7_SOLID_ANIM =
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

AnimationFunctionROMSpec HIDE_LAYER_10x7_TRANSPARENT_ANIM =
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

AnimationFunctionROMSpec HIDE_LAYER_10x7_TO_SOLID_ANIM =
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

AnimationFunctionROMSpec HIDE_LAYER_10x7_TO_TRANSPARENT_ANIM =
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
AnimationDescriptionROMSpec HIDE_LAYER_10x7_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HIDE_LAYER_10x7_SOLID_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TRANSPARENT_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TO_SOLID_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TO_TRANSPARENT_ANIM,
		NULL,
	}
};

CharSetROMSpec HIDE_LAYER_10x7_CH =
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
};

TextureROMSpec HIDE_LAYER_10x7_TX =
{
	// charset spec
	(CharSetSpec*)&HIDE_LAYER_10x7_CH,

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

BgmapSpriteROMSpec HIDE_LAYER_10x7_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HIDE_LAYER_10x7_TX,

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

BgmapSpriteROMSpec* const HIDE_LAYER_10x7_SPRITES[] =
{
	&HIDE_LAYER_10x7_SPRITE,
	NULL
};

ShapeROMSpec HIDE_LAYER_10x7_SHAPES[] =
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

HideLayerROMSpec HIDE_LAYER_10x7_EN =
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
		(SpriteSpec**)HIDE_LAYER_10x7_SPRITES,

		// use z displacement in projection
		false,

		// collision shapes
		(ShapeSpec*)HIDE_LAYER_10x7_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeHideLayer,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&HIDE_LAYER_10x7_ANIM,

	// initial animation
	"Shape",
};
