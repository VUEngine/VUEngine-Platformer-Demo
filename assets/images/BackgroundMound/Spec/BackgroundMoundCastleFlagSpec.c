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
#include <ObjectAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BackgroundMoundCastleFlagTiles[];
extern BYTE BackgroundMoundCastleFlagMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec MOUND_BG_CASTLE_FLAG_WAVE_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{0, 1},

	// number of cycles a frame of animation is displayed
	10,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Wave",
};

// an animation spec
AnimationDescriptionROMSpec MOUND_BG_CASTLE_FLAG_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&MOUND_BG_CASTLE_FLAG_WAVE_ANIM,
		NULL,
	}
};

CharSetROMSpec MOUND_BG_CASTLE_FLAG_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	1,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SHARED,

	// char spec
	BackgroundMoundCastleFlagTiles,
};

TextureROMSpec MOUND_BG_CASTLE_FLAG_TX =
{
	// charset spec
	(CharSetSpec*)&MOUND_BG_CASTLE_FLAG_CH,

	// bgmap spec
	BackgroundMoundCastleFlagMap,

	// cols (max 64)
	1,

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

ObjectSpriteROMSpec MOUND_BG_CASTLE_FLAG_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&MOUND_BG_CASTLE_FLAG_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMSpec* const MOUND_BG_CASTLE_FLAG_SPRITES[] =
{
	&MOUND_BG_CASTLE_FLAG_SPRITE,
	NULL
};

AnimatedEntityROMSpec MOUND_BG_CASTLE_FLAG_EN =
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
		(SpriteSpec**)MOUND_BG_CASTLE_FLAG_SPRITES,

		// use z displacement in projection
		false,

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
	(AnimationDescription*)&MOUND_BG_CASTLE_FLAG_ANIM,

	// initial animation
	"Wave",
};
