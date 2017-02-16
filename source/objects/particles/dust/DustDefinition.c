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

extern BYTE DustParticleSmallTiles[];
extern BYTE DustParticleSmallMap[];
extern BYTE DustParticleLargeTiles[];
extern BYTE DustParticleLargeMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef DUST_PARTICLE_SMALL_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	1,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char definition
	DustParticleSmallTiles,
};

TextureROMDef DUST_PARTICLE_SMALL_TX =
{
	// charset definition
	(CharSetDefinition*)&DUST_PARTICLE_SMALL_CH,

	// bgmap definition
	DustParticleSmallMap,

	// cols (max 64)
	1,

	// rows (max 64)
	1,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,
};

ObjectSpriteROMDef DUST_PARTICLE_SMALL_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectSprite),

		// texture definition
		(TextureDefinition*)&DUST_PARTICLE_SMALL_TX,

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

CharSetROMDef DUST_PARTICLE_LARGE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	1,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char definition
	DustParticleLargeTiles,
};

TextureROMDef DUST_PARTICLE_LARGE_TX =
{
	// charset definition
	(CharSetDefinition*)&DUST_PARTICLE_LARGE_CH,

	// bgmap definition
	DustParticleLargeMap,

	// cols (max 64)
	1,

	// rows (max 64)
	1,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,
};

ObjectSpriteROMDef DUST_PARTICLE_LARGE_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(ObjectSprite),

		// texture definition
		(TextureDefinition*)&DUST_PARTICLE_LARGE_TX,

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

ObjectSpriteROMDef* const DUST_PARTICLE_IM_SPRITES[] =
{
	&DUST_PARTICLE_SMALL_IM_SPRITE,
	&DUST_PARTICLE_LARGE_IM_SPRITE,
	NULL
};



//---------------------------------------------------------------------------------------------------------
//											OBJECT DUST_PARTICLE
//---------------------------------------------------------------------------------------------------------

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
	(const ObjectSpriteDefinition**)DUST_PARTICLE_IM_SPRITES,

	// auto start
	false,

	// particle definition
	(ParticleDefinition*)&DUST_PARTICLE,

	// minimum random distance from the center of the system for spawn
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},

	// minimum relative spawn position
	{ITOFIX19_13(-1), ITOFIX19_13(-1), ITOFIX19_13(0)},

	// maximum relative spawn position
	{__1I_FIX19_13, __1I_FIX19_13, ITOFIX19_13(0)},

	// minimum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},

	// maximum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},

	// movement type: __UNIFORM_MOVEMENT or __ACCELERATED_MOVEMENT
	__UNIFORM_MOVEMENT
};
