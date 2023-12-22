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
#include <ParticleSystem.h>
#include <ObjectSprite.h>
#include <PhysicalParticle.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern ObjectSpriteROMSpec WaterDropSprite;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMSpec* const WaterSplashSprites[] =
{
	&WaterDropSprite,
	NULL
};

// particle's spec
PhysicalParticleROMSpec WaterSplashParticle =
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

ParticleSystemROMSpec WaterSplashParticleSystem =
{
	{
		// class allocator
		__TYPE(ParticleSystem),

		// children
		NULL,

		// behaviors
		NULL,

		// extra
		NULL,

		// sprites
		NULL,

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
		kTypeNone,

		// physical specification
		(PhysicalProperties*)NULL,
	},

	// reuse expired particles?
	true,

	// minimum generation delay in milliseconds
	50,

	// maximum generation delay in milliseconds
	100,

	// maximum total particles
	8,

	// maximum number of particles to spawn in each cycle
	1,

	// array of textures
	(const SpriteSpec**)WaterSplashSprites,

	// array of wireframes
	(const WireframeSpec**)NULL,

	// auto start
	true,

	// particle spec
	(ParticleSpec*)&WaterSplashParticle,

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
	__ACCELERATED_MOVEMENT,

	/// use particle system movement vector for the force to apply to the particles
	false
};
