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
#include <ObjectSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern ObjectSpriteROMDef WATER_DROP_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef* const WATER_SPLASH_SPRITES[] =
{
	&WATER_DROP_SPRITE,
	NULL
};

// particle's definition
ParticleROMDef WATER_SPLASH_PARTICLE =
{
	// allocator
	__TYPE(Particle),

	// particle's minimum life span in milliseconds
	1000,

	// particle's life span delta in milliseconds (maximum = minimum + delta)
	500,

	// particle's minimum mass
	__F_TO_FIX19_13(8.0f),

	// particle's mass delta (maximum = minimum + delta)
	__F_TO_FIX19_13(8.0f),

	// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
	__Y_AXIS,

	// function pointer to control particle's behavior
	NULL,

	// animation description (used only if sprite is animated)
	NULL,

	// name of animation to play
	NULL
};

ParticleSystemROMDef WATER_SPLASH_PS =
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
	true,

	// minimum generation delay in milliseconds
	50,

	// maximum generation delay in milliseconds
	100,

	// maximum total particles
	8,

	// array of textures
	(const ObjectSpriteDefinition**)WATER_SPLASH_SPRITES,

	// auto start
	true,

	// particle definition
	(ParticleDefinition*)&WATER_SPLASH_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{__I_TO_FIX19_13(-16), __I_TO_FIX19_13(0), __I_TO_FIX19_13(-1)},

	// maximum relative spawn position (x, y, z)
	{__I_TO_FIX19_13(16), __I_TO_FIX19_13(0), __I_TO_FIX19_13(1)},

	// minimum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{-1000, -15000, -200},

	// maximum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{1000, -15500, 200},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__ACCELERATED_MOVEMENT
};
