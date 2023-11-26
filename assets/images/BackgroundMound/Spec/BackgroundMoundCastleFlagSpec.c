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

extern uint32 BackgroundMoundCastleFlagTiles[];
extern uint16 BackgroundMoundCastleFlagMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec MoundBgCastleFlagWaveAnimation =
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
const AnimationFunction* const MoundBgCastleFlagAnimations[] =
{
	(AnimationFunction*)&MoundBgCastleFlagWaveAnimation,
	NULL,
};

CharSetROMSpec MoundBgCastleFlagCharset =
{
	// number of chars in function of the number of frames to load at the same time
	1,

	// whether it is shared or not
	true,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	BackgroundMoundCastleFlagTiles,

	// pointer to the frames offsets
	NULL,
};

TextureROMSpec MoundBgCastleFlagTexture =
{
	// charset spec
	(CharSetSpec*)&MoundBgCastleFlagCharset,

	// bgmap spec
	BackgroundMoundCastleFlagMap,

	// cols (max 64)
	1,

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

ObjectSpriteROMSpec MoundBgCastleFlagSprite =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture spec
		(TextureSpec*)&MoundBgCastleFlagTexture,

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

ObjectSpriteROMSpec* const MoundBgCastleFlagSprites[] =
{
	&MoundBgCastleFlagSprite,
	NULL
};

AnimatedEntityROMSpec MoundBgCastleFlagEntity =
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
		(SpriteSpec**)MoundBgCastleFlagSprites,

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
	(const AnimationFunction**)MoundBgCastleFlagAnimations,

	// initial animation
	"Wave",
};
