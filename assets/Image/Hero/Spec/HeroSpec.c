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
#include <BgmapAnimatedSprite.h>
#include <PlatformerCameraTriggerEntity.h>
#include <Ball.h>
#include <InverseBox.h>

#include "Hero.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern uint32 HeroTiles[];
extern uint32 HeroTilesFrameOffsets[];
extern uint32 HeroBandanaTiles[];
extern uint32 HeroBandanaTilesFrameOffsets[];
extern uint16 HeroMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec HeroIdleAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{4, 5},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroWalkingAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{13, 14},

	// number of cycles a frame of animation is displayed
	10,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Walk",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroJumpingAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{6},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Jump",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroFallingAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{7},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Fall",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroSlidingAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{7},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Slide",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroHitAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{8},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Hit",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroClimbAnimation =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{9, 10},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Climb",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroFrontAnimation =
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
	"Front",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroBackAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{2, 3},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Back",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroWalkingFrontAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{17, 18},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"WalkingFront",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroWalkingBackAnimation =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{15, 16},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"WalkingBack",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroTransitionAnimation =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{19, 20, 21, 22, 23},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hero_onPowerUpTransitionComplete,

	// function's name
	"Transition",
};

// a function which defines the frames to play
AnimationFunctionROMSpec HeroSleepAnimation =
{
	// number of frames of this animation function
	10,

	// frames to play in animation
	{24, 24, 24, 24, 24, 25, 26, 27, 26, 25},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Sleep",
};


// an animation spec
const AnimationFunction* const HeroAnimations[] =
{
	(AnimationFunction*)&HeroIdleAnimation,
	(AnimationFunction*)&HeroWalkingAnimation,
	(AnimationFunction*)&HeroJumpingAnimation,
	(AnimationFunction*)&HeroFallingAnimation,
	(AnimationFunction*)&HeroSlidingAnimation,
	(AnimationFunction*)&HeroHitAnimation,
	(AnimationFunction*)&HeroClimbAnimation,
	(AnimationFunction*)&HeroFrontAnimation,
	(AnimationFunction*)&HeroBackAnimation,
	(AnimationFunction*)&HeroWalkingFrontAnimation,
	(AnimationFunction*)&HeroWalkingBackAnimation,
	(AnimationFunction*)&HeroTransitionAnimation,
	(AnimationFunction*)&HeroSleepAnimation,
	NULL,
};

CharSetROMSpec HeroCharset =
{
	// number of chars in function of the number of frames to load at the same time
	9,

	// whether it is shared or not
	false,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	HeroTiles,

	// pointer to the frames offsets
	HeroTilesFrameOffsets,
};

CharSetROMSpec HeroBandanaCharset =
{
	// number of chars in function of the number of frames to load at the same time
	9,

	// whether it is shared or not
	false,
	
	// whether the tiles are optimized or not
	false,

	// char spec
	HeroBandanaTiles,

	// pointer to the frames offsets
	HeroBandanaTilesFrameOffsets,
};

TextureROMSpec HeroTexture =
{
	(CharSetSpec*)&HeroCharset,

	// bgmap spec
	HeroMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{1, 1},

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

TextureROMSpec HeroBandanaTexture =
{
	(CharSetSpec*)&HeroBandanaCharset,

	// bgmap spec
	HeroMap,

	// cols (max 64)
	3,

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

BgmapSpriteROMSpec HeroAffineSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HeroTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, HERO_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec HeroBandanaAffineSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HeroBandanaTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, HERO_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec HeroSprite =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&HeroTexture,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const HeroAffineSprites[] =
{
	&HeroAffineSprite,
	NULL
};

BgmapSpriteROMSpec* const HeroBandanaAffineSprites[] =
{
	&HeroBandanaAffineSprite,
	NULL
};

BgmapSpriteROMSpec* const HeroSprites[] =
{
	&HeroSprite,
	NULL
};

ColliderROMSpec HeroColliders[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{14, 14, 14},

		// displacement (x, y, z, p)
		{-1, 4, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		true,

		/// layers in which I live
		kLayerPlayer,

		/// layers to ignore when checking for collisions
		kLayerParticles | kLayerCamera,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

PhysicalPropertiesROMSpec HeroPhysicalProperties =
{
	// mass
	__F_TO_FIX10_6(0.65f),

	// friction
	__F_TO_FIX10_6(0),

	// bounciness
	__F_TO_FIX10_6(HERO_BOUNCINESS),

	// maximum velocity
	{__I_TO_FIX10_6(100), __I_TO_FIX10_6(100), __I_TO_FIX10_6(100)},

	// maximum speed
	__I_TO_FIX10_6(0)
};

HeroROMSpec HeroEntity =
{
	{
		{
			// class allocator
			__TYPE(Hero),

			// children
			NULL,

			// behaviors
			NULL,

			// extra
			NULL,

			// sprites
			(SpriteSpec**)HeroAffineSprites,

			// use z displacement in projection
			false,
			
			/// meshes
			(WireframeSpec**)NULL,

			// collision shapes
			(ColliderSpec*)HeroColliders,

			// size
			// if 0, width and height will be inferred from the first sprite's texture's size
			{0, 0, 0},

			// gameworld's character's type
			kTypeHero,

			// physical specification
			(PhysicalProperties*)&HeroPhysicalProperties,
		},

		// pointer to the animation spec for the character
		(const AnimationFunction**)HeroAnimations,

		// initial animation
		"Idle",
	},

	/// true to create a body
	true,

	/// axis subject to gravity
	__Y_AXIS,

	// axis around which to rotate the entity when syncronizing with body
	__Y_AXIS
};

AnimatedEntityROMSpec HeroIdleEntity =
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
		(SpriteSpec**)HeroSprites,

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
		kTypeHero,

		// physical specification
		(PhysicalProperties*)NULL,
	},

	// pointer to the animation spec for the character
	(const AnimationFunction**)HeroAnimations,

	// initial animation
	"Idle",
};

AnimatedEntityROMSpec HeroSleepingEntity =
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
		(SpriteSpec**)HeroSprites,

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
		kTypeHero,

		// physical specification
		(PhysicalProperties*)NULL,
	},

	// pointer to the animation spec for the character
	(const AnimationFunction**)HeroAnimations,

	// initial animation
	"Sleep",
};


AnimatedEntityROMSpec HeroBandanaEntity =
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
		(SpriteSpec**)HeroBandanaAffineSprites,

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
		kTypeHero,

		// physical specification
		(PhysicalProperties*)NULL,
	},

	// pointer to the animation spec for the character
	(const AnimationFunction**)HeroAnimations,

	// initial animation
	"Idle",
};


