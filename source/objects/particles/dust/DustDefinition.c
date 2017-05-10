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

extern ObjectSpriteROMDef DUST_PARTICLE_SMALL_SPRITE;
extern ObjectSpriteROMDef DUST_PARTICLE_LARGE_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef* const DUST_PARTICLE_SPRITES[] =
{
	&DUST_PARTICLE_SMALL_SPRITE,
	&DUST_PARTICLE_LARGE_SPRITE,
	NULL
};

// particle's definition
ParticleROMDef DUST_PARTICLE =
{
	// allocator
	__TYPE(Particle),

	// particle's minimum life span in milliseconds
	100,

	// particle's life span delta in milliseconds
	100,

	// particle's minimum mass
	FTOFIX19_13(0),

	// particle's mass delta
	FTOFIX19_13(0),

	// axis subject to gravity (false to disable)
	false,

	// function pointer to control particle's behavior
	//(void (*)(Particle))&dustParticleBehavior,
	NULL,

	// animation description
	// used only if sprite is animated
	NULL,

	// animation's name to play
	NULL
};

ParticleSystemROMDef DUST_PS =
{
	{
		__TYPE(ParticleSystem),
		NULL,
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
	(const ObjectSpriteDefinition**)DUST_PARTICLE_SPRITES,

	// auto start
	false,

	// particle definition
	(ParticleDefinition*)&DUST_PARTICLE,

	// minimum random distance from the center of the system for spawn
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},

	// minimum relative spawn position
	{ITOFIX19_13(-2), ITOFIX19_13(0), ITOFIX19_13(0)},

	// maximum relative spawn position
	{__1I_FIX19_13, ITOFIX19_13(0), ITOFIX19_13(0)},

	// minimum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},

	// maximum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},

	// movement type: __UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT
	__UNIFORM_MOVEMENT
};
