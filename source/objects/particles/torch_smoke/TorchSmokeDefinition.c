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

extern BYTE SmokeParticleSmallTiles[];
extern BYTE SmokeParticleSmallMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------


// a function which defines the frames to play
AnimationFunctionROMDef TORCH_SMOKE_PARTICLE_SMALL_FLOAT_ANIM =
{
	// number of frames of this animation function
	8,

	// frames to play in animation
	{0, 0, 0, 0, 0, 1, 2, 3},

	// number of cycles a frame of animation is displayed
	32,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Float",
};

// an animation definition
AnimationDescriptionROMDef TORCH_SMOKE_PARTICLE_SMALL_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&TORCH_SMOKE_PARTICLE_SMALL_FLOAT_ANIM,
		NULL,
	}
};

CharSetROMDef TORCH_SMOKE_PARTICLE_SMALL_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	SmokeParticleSmallTiles,
};

TextureROMDef TORCH_SMOKE_PARTICLE_SMALL_TX =
{
	// charset definition
	(CharSetDefinition*)&TORCH_SMOKE_PARTICLE_SMALL_CH,

	// bgmap definition
	SmokeParticleSmallMap,

	// cols (max 64)
	1,

	// rows (max 64)
	1,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	4,

	// palette number (0-3)
	0,
};

ObjectSpriteROMDef TORCH_SMOKE_PARTICLE_SMALL_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectAnimatedSprite),

		// texture definition
		(TextureDefinition*)&TORCH_SMOKE_PARTICLE_SMALL_TX,

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

ObjectSpriteROMDef* const TORCH_SMOKE_PARTICLE_SMALL_SPRITES[] =
{
	&TORCH_SMOKE_PARTICLE_SMALL_SPRITE,
	NULL
};

// particle's definition
ParticleROMDef TORCH_SMOKE_PARTICLE =
{
	// allocator
	__TYPE(Particle),

	// particle's minimum life span in milliseconds
	3000,

	// particle's life span delta in milliseconds
	3000,

	// particle's minimum mass
	FTOFIX19_13(0),

	// particle's mass delta
	FTOFIX19_13(0),

	// axis subject to gravity (false to disable)
	false,

	// function pointer to control particle's behavior
	//(void (*)(Particle))&smokeParticleBehavior,
	NULL,

	// animation description
	// used only if sprite is animated
	(AnimationDescription*)&TORCH_SMOKE_PARTICLE_SMALL_ANIM,

	// animation's name to play
	"Float"
};

ParticleSystemROMDef TORCH_SMOKE_PS =
{
	{
		__TYPE(ParticleSystem),
		NULL,
	},

	// reuse expired particles?
	true,

	// minimum generation delay in milliseconds
	100,

	// generation delay delta in milliseconds
	200,

	// maximum total particles
	5,

	// array of textures
	(const ObjectSpriteDefinition**)TORCH_SMOKE_PARTICLE_SMALL_SPRITES,

	// auto start
	true,

	// particle definition
	(ParticleDefinition*)&TORCH_SMOKE_PARTICLE,

	// minimum random distance from the center of the system for spawn
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},

	// minimum relative spawn position
	{ITOFIX19_13(-2), ITOFIX19_13(0), ITOFIX19_13(0)},

	// maximum relative spawn position
	{ITOFIX19_13(2), ITOFIX19_13(0), ITOFIX19_13(0)},

	// minimum force to apply
	// use int values in the definition to avoid overflow
	{(-5), (-10), (0)},

	// maximum force to apply
	// use int values in the definition to avoid overflow
	{(-5), (-20), (0)},

	// movement type: __UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT
	__UNIFORM_MOVEMENT
};
