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

extern uint32 WaterfallTopTiles[];
extern uint32 WaterfallTopTilesFrameOffsets[];
extern uint16 WaterfallTopMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec WaterfallTopDefaultAnimation =
{
	// number of frames of this animation function
	3,

	// frames to play in animation
	{0, 1, 2},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

// an animation spec
const AnimationFunction* const WaterfallTopAnimations[] =
{
	(AnimationFunction*)&WaterfallTopDefaultAnimation,
	NULL,
};

CharSetROMSpec WaterfallTopCharset =
{
	// number of chars in function of the number of frames to load at the same time
	4,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	WaterfallTopTiles,

	// pointer to the frames offsets
	WaterfallTopTilesFrameOffsets,
};

TextureROMSpec WaterfallTopTexture =
{
	// charset spec
	(CharSetSpec*)&WaterfallTopCharset,

	// bgmap spec
	WaterfallTopMap,

	// cols (max 64)
	4,

	// rows (max 64)
	1,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

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

BgmapSpriteROMSpec WaterfallTopSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&WaterfallTopTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{
			0,
			0,
			0,
			WATERFALLS_PARALLAX_DISPLACEMENT
		},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const WaterfallTopSprites[] =
{
	&WaterfallTopSprite,
	NULL
};

AnimatedEntityROMSpec WaterfallTopEntity =
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
		(SpriteSpec**)WaterfallTopSprites,

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
	(const AnimationFunction**)WaterfallTopAnimations,

	// initial animation
	"Default",
};
