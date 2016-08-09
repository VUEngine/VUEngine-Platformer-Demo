/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev <jorgech3@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <libgccvb.h>
#include <ParticleSystem.h>
#include <ObjectSprite.h>
#include "../behaviors.h"
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE DustParticleSmallTiles[];
extern BYTE DustParticleSmallMap[];
extern BYTE DustParticleLargeTiles[];
extern BYTE DustParticleLargeMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
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

        // displacement
        {0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_OBJ,

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

        // displacement
        {0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_OBJ,

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
// 										  OBJECT DUST_PARTICLE
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
	20,

	// generation delay delta in milliseconds
	60,

	// maximum total particles
	5,

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
	{ITOFIX19_13(1), ITOFIX19_13(1), ITOFIX19_13(0)},

	// minimum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},

	// maximum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},
};
