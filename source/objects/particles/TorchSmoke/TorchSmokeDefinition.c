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

extern AnimationDescriptionROMDef SMOKE_PARTICLE_SMALL_ANIM;
extern ObjectSpriteROMDef SMOKE_PARTICLE_SMALL_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef* const TORCH_SMOKE_SPRITES[] =
{
	&SMOKE_PARTICLE_SMALL_SPRITE,
	NULL
};

// particle's definition
ParticleROMDef TORCH_SMOKE_PARTICLE =
{
	// allocator
	__TYPE(Particle),

	// particle's minimum life span in milliseconds
	3000,

	// particle's life span delta in milliseconds (maximum = minimum + delta)
	3000,

	// particle's minimum mass
	FTOFIX19_13(0),

	// particle's mass delta (maximum = minimum + delta)
	FTOFIX19_13(0),

	// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
	false,

	// function pointer to control particle's behavior
	NULL,

	// animation description (used only if sprite is animated)
	(AnimationDescription*)&SMOKE_PARTICLE_SMALL_ANIM,

	// name of animation to play
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
	(const ObjectSpriteDefinition**)TORCH_SMOKE_SPRITES,

	// auto start
	true,

	// particle definition
	(ParticleDefinition*)&TORCH_SMOKE_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},

	// maximum relative spawn position (x, y, z)
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},

	// minimum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{-2, -5, 0},

	// maximum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{2, -10, 0},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__UNIFORM_MOVEMENT
};
