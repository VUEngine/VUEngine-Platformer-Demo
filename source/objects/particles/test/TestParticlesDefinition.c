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

#include <libgccvb.h>
#include <SolidParticle.h>
#include <ParticleSystem.h>
#include <ObjectAnimatedSprite.h>
#include <AnimatedEntity.h>
#include <macros.h>

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern void testParticleBehavior(Particle particle);

extern ObjectSpriteDefinition COIN_BACK_SPRITE;
extern AnimationDescription COIN_ANIM;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
//											OBJECT TEST_PARTICLE
//---------------------------------------------------------------------------------------------------------


ObjectSpriteROMDef* const TEST_PARTICLE_SPRITES[] =
{
	&COIN_BACK_SPRITE,
	NULL
};

// particle's definition
SolidParticleROMDef TEST_PARTICLE =
{
	{
		// allocator
		__TYPE(SolidParticle),

		// particle's minimum life span in milliseconds
		800,

		// particle's maximum life span in milliseconds
		1550,

		// particle's minimum mass
		__F_TO_FIX10_6(0.01f),

		// particle's maximum mass
		__F_TO_FIX10_6(0.01f),

		// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
		__Y_AXIS,

		// function pointer to control particle's behavior
		(void (*)(Particle))&testParticleBehavior,

		// animation description (used only if sprite is animated)
		(AnimationDescription*)&COIN_ANIM,

		// name of animation to play
		"Spin"
	},

	/// ball's radius
	__F_TO_FIX10_6(0.25f),

	/// friction for physics
	__F_TO_FIX10_6(0.0f),

	/// bounciness for physics
	__F_TO_FIX10_6(0.6f),

	/// object's in-game type
	kUncollectableCoin,

	/// layers in which I live
	kParticlesLayer,

	/// layers to ignore when checking for collisions
	kParticlesLayer | kTriggersLayer,
//	kTriggersLayer,

	/// disable collision detection when the particle stops
	false,
};

ParticleSystemROMDef TEST_1_PS =
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
	300,

	// maximum total particles
	10,

	// array of textures
	(const ObjectSpriteDefinition**)TEST_PARTICLE_SPRITES,

	// auto start
	true,

	// particle definition
	(ParticleDefinition*)&TEST_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{__F_TO_FIX10_6(-30 / 16.0f), __F_TO_FIX10_6(0), __F_TO_FIX10_6(0)},

	// maximum relative spawn position (x, y, z)
	{__F_TO_FIX10_6(30 / 16.0f), __F_TO_FIX10_6(0), __F_TO_FIX10_6(0)},

	// minimum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{__F_TO_FIX10_6(0), __F_TO_FIX10_6(1), 0},

	// maximum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{__F_TO_FIX10_6(0), __F_TO_FIX10_6(0), 0},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__ACCELERATED_MOVEMENT
};


ParticleSystemROMDef TEST_2_PS =
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
	300,

	// maximum total particles
	10,

	// array of textures
	(const ObjectSpriteDefinition**)TEST_PARTICLE_SPRITES,

	// auto start
	true,

	// particle definition
	(ParticleDefinition*)&TEST_PARTICLE,

	// minimum relative spawn position (x, y, z)
	{__F_TO_FIX10_6(0), __F_TO_FIX10_6(0), __F_TO_FIX10_6(0)},

	// maximum relative spawn position (x, y, z)
	{__F_TO_FIX10_6(0), __F_TO_FIX10_6(0), __F_TO_FIX10_6(0)},

	// minimum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{__F_TO_FIX10_6(32), __F_TO_FIX10_6(-40), 0},

	// maximum force to apply (x, y, z)
	// (use int values in the definition to avoid overflow)
	{__F_TO_FIX10_6(54), __F_TO_FIX10_6(-68), 0},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__ACCELERATED_MOVEMENT
};