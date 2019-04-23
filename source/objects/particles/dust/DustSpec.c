/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include <Libgccvb.h>
#include <ParticleSystem.h>
#include <ObjectSprite.h>
#include <PhysicalParticle.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern ObjectSpriteROMSpec DUST_PARTICLE_SMALL_SPRITE;
extern ObjectSpriteROMSpec DUST_PARTICLE_LARGE_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMSpec* const DUST_PARTICLE_SPRITES[] =
{
	&DUST_PARTICLE_SMALL_SPRITE,
	&DUST_PARTICLE_LARGE_SPRITE,
	NULL
};

// particle's spec
PhysicalParticleROMSpec DUST_PARTICLE =
{
	{
		// allocator
		__TYPE(PhysicalParticle),

		// particle's minimum life span in milliseconds
		100,

		// particle's life span delta in milliseconds (maximum = minimum + delta)
		100,

		// function pointer to control particle's behavior
		//(void (*)(Particle))&dustParticleBehavior,
		NULL,

		// animation description (used only if sprite is animated)
		NULL,

		// name of animation to play
		NULL
	},

	// particle's minimum mass
	__F_TO_FIX10_6(0.9f),

	// particle's mass delta (maximum = minimum + delta)
	__F_TO_FIX10_6(1.0f),

	// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
	false,
};

ParticleSystemROMSpec DUST_PS =
{
	{
		// class allocator
		__TYPE(ParticleSystem),

		// behaviors 
		NULL,

		// sprites
		(SpriteSpec**)NULL,

		// collision shapes
		(ShapeSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kNoType,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// reuse expired particles?
	true,

	// minimum generation delay in milliseconds
	0,

	// generation delay delta in milliseconds
	5,

	// maximum total particles
	4,

	// array of textures
	(const ObjectSpriteSpec**)DUST_PARTICLE_SPRITES,

	// auto start
	false,

	// particle spec
	(ParticleSpec*)&DUST_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{__PIXELS_TO_METERS(-4), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

	// maximum relative spawn position (x, y, z)
	{__PIXELS_TO_METERS(4), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

	// minimum force to apply (x, y, z)
	// (use int values in the spec to avoid overflow)
	{__I_TO_FIX10_6(0), __F_TO_FIX10_6(-0.03f), __I_TO_FIX10_6(0)},

	// maximum force to apply (x, y, z)
	// (use int values in the spec to avoid overflow)
	{__I_TO_FIX10_6(0), __F_TO_FIX10_6(-0.01f), __I_TO_FIX10_6(0)},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__UNIFORM_MOVEMENT
};
