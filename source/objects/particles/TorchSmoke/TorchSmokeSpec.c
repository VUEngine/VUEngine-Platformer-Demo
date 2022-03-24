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
#include <ObjectAnimatedSprite.h>
#include <PhysicalParticle.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern AnimationDescriptionROMSpec SmokeParticleSmallAnimation;
extern ObjectSpriteROMSpec SmokeParticleSmallSprite;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMSpec* const TorchSmokeSprites[] =
{
	&SmokeParticleSmallSprite,
	NULL
};

// particle's spec
PhysicalParticleROMSpec TorchSmokeParticle =
{
	{
		// allocator
		__TYPE(PhysicalParticle),

		// particle's minimum life span in milliseconds
		1000,

		// particle's life span delta in milliseconds (maximum = minimum + delta)
		1000,

		// function pointer to control particle's behavior
		NULL,

		// animation description (used only if sprite is animated)
		(AnimationDescription*)&SmokeParticleSmallAnimation,

		// name of animation to play
		"Default"
	},

	// particle's minimum mass
	__F_TO_FIX10_6(0.5f),

	// particle's mass delta (maximum = minimum + delta)
	__F_TO_FIX10_6(0),

	// axis subject to gravity (bitwise or of __X_AXIS, __Y_AXIS, __Z_AXIS, or false to disable)
	__NO_AXIS,
};

ParticleSystemROMSpec TorchSmokeParticleSystem =
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

		// collision shapes
		(ShapeSpec*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeNoShape,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// reuse expired particles?
	true,

	// minimum generation delay in milliseconds
	100,

	// generation delay delta in milliseconds
	200,

	// maximum total particles
	5,

	// maximum number of particles to spawn in each cycle
	1,

	// array of textures
	(const SpriteSpec**)TorchSmokeSprites,

	// auto start
	true,

	// particle spec
	(ParticleSpec*)&TorchSmokeParticle,

	// minimum relative spawn position (x, y, z)
	{__PIXELS_TO_METERS(0), __PIXELS_TO_METERS(0), __PIXELS_TO_METERS(0)},

	// maximum relative spawn position (x, y, z)
	{__PIXELS_TO_METERS(0), __PIXELS_TO_METERS(0), __PIXELS_TO_METERS(0)},

	// minimum force to apply (x, y, z)
	// (use int values in the spec to avoid overflow)
	{-__PIXELS_TO_METERS(4), -__PIXELS_TO_METERS(8), __PIXELS_TO_METERS(0)},

	// maximum force to apply (x, y, z)
	// (use int values in the spec to avoid overflow)
	{__PIXELS_TO_METERS(4), -__PIXELS_TO_METERS(8), __PIXELS_TO_METERS(0)},

	// movement type (__UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT)
	__UNIFORM_MOVEMENT,

	/// use particle system movement vector for the force to apply to the particles
	false
};
