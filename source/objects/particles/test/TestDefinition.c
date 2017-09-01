/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <libgccvb.h>
#include <ParticleSystem.h>
#include <ObjectAnimatedSprite.h>
#include <macros.h>

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CoinTiles[];
extern BYTE CoinMap[];
extern void testParticleBehavior(Particle particle);


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef TEST_PARTICLE_SPIN_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0, 1, 2, 3},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Spin",
};

// an animation definition
AnimationDescriptionROMDef TEST_PARTICLE_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&TEST_PARTICLE_SPIN_ANIM,
		NULL,
	}
};

CharSetROMDef OBJECT_TEST_PARTICLE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	28,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	CoinTiles,
};

TextureROMDef OBJECT_TEST_PARTICLE_TX =
{
	// charset definition
	(CharSetDefinition*)&OBJECT_TEST_PARTICLE_CH,

	// bgmap definition
	CoinMap,

	// cols (max 64)
	2,

	// rows (max 64)
	2,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	7,

	// palette number (0-3)
	1,

	// recyclable
	false,
};


//---------------------------------------------------------------------------------------------------------
//											OBJECT TEST_PARTICLE
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef OBJECT_TEST_PARTICLE_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&OBJECT_TEST_PARTICLE_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const OBJECT_TEST_PARTICLE_SPRITES[] =
{
	&OBJECT_TEST_PARTICLE_SPRITE,
	NULL
};

// particle's definition
ParticleROMDef TEST_PARTICLE =
{
	// allocator
	__TYPE(Particle),

	// particle's minimum life span in milliseconds
	300,

	// particle's maximum life span in milliseconds
	1500,

	// particle's minimum mass
	__F_TO_FIX19_13(5.0f),

	// particle's maximum mass
	__F_TO_FIX19_13(10.0f),

	// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
	__Y_AXIS,

	// function pointer to control particle's behavior
	(void (*)(Particle))&testParticleBehavior,

	// animation description (used only if sprite is animated)
	(AnimationDescription*)&TEST_PARTICLE_ANIM,

	// name of animation to play
	"Spin"
};

ParticleSystemROMDef TEST_PS =
{
	{
		// class allocator
		__TYPE(ParticleSystem),

		// sprites
		(SpriteROMDef**)NULL,

		// collision shapes
		(ShapeDefinition*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kNoType,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// reuse expired particles?
	false,

	// minimum generation delay in milliseconds
	50,

	// maximum generation delay in milliseconds
	100,

	// maximum total particles
	30,

	// array of textures
	(const ObjectSpriteDefinition**)OBJECT_TEST_PARTICLE_SPRITES,

	// auto start
	true,

	// particle definition
	(ParticleDefinition*)&TEST_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{__I_TO_FIX19_13(0), __I_TO_FIX19_13(0), __I_TO_FIX19_13(0)},

	// maximum relative spawn position (x, y, z)
	{__I_TO_FIX19_13(0), __I_TO_FIX19_13(0), __I_TO_FIX19_13(0)},

	// minimum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{-5000, -20000, 0},

	// maximum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{5000, -16000, 0},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__UNIFORM_MOVEMENT
};
