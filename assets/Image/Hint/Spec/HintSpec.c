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

#include <AnimatedEntity.h>
#include <BgmapAnimatedSprite.h>
#include <Libgccvb.h>
#include <Hint.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 HintTiles[];
extern uint32 HintTilesFrameOffsets[];
extern uint16 HintMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec HintOpenAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{0, 1, 2, 3, 4},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hint_onHintOpened,

	// function's name
	"Open",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintCloseAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hint_onCloseDone,

	// function's name
	"Close",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintClosedAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closed",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintEnterEnglishAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{5, 6},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterEnglish",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintEnterDeutschAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{7, 8},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterDeutsch",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintEnterEspanolAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{9, 10},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterEspanol",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintEnterFrancaisAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{11, 12},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterFrancais",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintPickUpEnglishAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{13, 14},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpEnglish",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintPickUpDeutschAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{15, 16},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpDeutsch",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintPickUpEspanolAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{17, 18},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpEspanol",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HintPickUpFrancaisAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{19, 20},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpFrancais",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HINT_KeyAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{21, 22},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Key",
};

// an animation spec
const AnimationFunction* const HintAnimations[] =
{
	(AnimationFunction*)&HintOpenAnimation,
	(AnimationFunction*)&HintCloseAnimation,
	(AnimationFunction*)&HintClosedAnimation,
	(AnimationFunction*)&HintEnterEnglishAnimation,
	(AnimationFunction*)&HintEnterDeutschAnimation,
	(AnimationFunction*)&HintEnterEspanolAnimation,
	(AnimationFunction*)&HintEnterFrancaisAnimation,
	(AnimationFunction*)&HintPickUpEnglishAnimation,
	(AnimationFunction*)&HintPickUpDeutschAnimation,
	(AnimationFunction*)&HintPickUpEspanolAnimation,
	(AnimationFunction*)&HintPickUpFrancaisAnimation,
	(AnimationFunction*)&HINT_KeyAnimation,
};

CharSetROMSpec HintCharset =
{
	// number of chars in function of the number of frames to load at the same time
	24,

	// whether it is shared or not
	false,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	HintTiles,

	// pointer to the frames offsets
	HintTilesFrameOffsets,
};

TextureROMSpec HintTexture =
{
	// charset spec
	(CharSetSpec*)&HintCharset,

	// bgmap spec
	HintMap,

	// cols (max 64)
	8,

	// rows (max 64)
	3,

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

BgmapSpriteROMSpec HintSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HintTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{28, -21, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const HintSprites[] =
{
	&HintSprite,
	NULL
};

AnimatedEntityROMSpec HintMc =
{
	{
		// class allocator
		__TYPE(Hint),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		(SpriteSpec**)HintSprites,

		// use z displacement in projection
		false,
			
		/// meshes
		(WireframeSpec**)NULL,

		// collision shapes
		(ColliderSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeNoCollider,

		// physical specification
		(PhysicalProperties*)NULL,
	},

	// pointer to the animation spec for the item
	(const AnimationFunction**)HintAnimations,

	// initial animation
	"Closed",
};

