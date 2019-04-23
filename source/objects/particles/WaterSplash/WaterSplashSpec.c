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

extern ObjectSpriteROMSpec WATER_DROP_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMSpec* const WATER_SPLASH_SPRITES[] =
{
	&WATER_DROP_SPRITE,
	NULL
};

// particle's spec
PhysicalParticleROMSpec WATER_SPLASH_PARTICLE =
{
	{
		// allocator
		__TYPE(PhysicalParticle),

		// particle's minimum life span in milliseconds
		1000,

		// particle's life span delta in milliseconds (maximum = minimum + delta)
		500,

		// function pointer to control particle's behavior
		NULL,

		// animation description (used only if sprite is animated)
		NULL,

		// name of animation to play
		NULL
	},

	// particle's minimum mass
	__F_TO_FIX10_6(8.0f),

	// particle's mass delta (maximum = minimum + delta)
	__F_TO_FIX10_6(8.0f),

	// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
	__Y_AXIS,

};

ParticleSystemROMSpec WATER_SPLASH_PS =
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
	50,

	// maximum generation delay in milliseconds
	100,

	// maximum total particles
	8,

	// array of textures
	(const ObjectSpriteSpec**)WATER_SPLASH_SPRITES,

	// auto start
	true,

	// particle spec
	(ParticleSpec*)&WATER_SPLASH_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{__I_TO_FIX10_6(-16), __I_TO_FIX10_6(0), __I_TO_FIX10_6(-1)},

	// maximum relative spawn position (x, y, z)
	{__I_TO_FIX10_6(16), __I_TO_FIX10_6(0), __I_TO_FIX10_6(1)},

	// minimum force to apply (x, y, z)
	// (use int values in the spec to avoid overflow)
	{__I_TO_FIX10_6(-1000), __I_TO_FIX10_6(-15000), __I_TO_FIX10_6(-200)},

	// maximum force to apply (x, y, z)
	// (use int values in the spec to avoid overflow)
	{__I_TO_FIX10_6(1000), __I_TO_FIX10_6(-15500), __I_TO_FIX10_6(200)},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__ACCELERATED_MOVEMENT
};
