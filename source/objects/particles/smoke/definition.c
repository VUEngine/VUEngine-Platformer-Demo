/* VBJaEngine: bitmap graphics engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007 Jorge Eremiev
 * jorgech3@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <libgccvb.h>
#include <ParticleSystem.h>
#include <ObjectSprite.h>
#include "../behaviors.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE SmokeParticleSmallTiles[];
extern BYTE SmokeParticleSmallMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef SMOKE_PARTICLE_SMALL_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        1,

        // allocation type
        __NOT_ANIMATED,

        // char definition
        SmokeParticleSmallTiles,
    },

    // bgmap definition
    SmokeParticleSmallMap,

    // cols (max 64)
    1,

    // rows (max 64)
    1,

    // number of frames
    1,

    // palette number
    0,
};

ObjectSpriteROMDef SMOKE_PARTICLE_SMALL_IM_SPRITE =
{
	// sprite's type
	__TYPE(ObjectSprite),

	// texture definition
	(TextureDefinition*)&SMOKE_PARTICLE_SMALL_TX,

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_OBJ,

	// display mode
	WRLD_ON,

	// parallax displacement
	0
};

ObjectSpriteROMDef* const SMOKE_PARTICLE_IM_SPRITES[] =
{
	&SMOKE_PARTICLE_SMALL_IM_SPRITE,
	NULL
};



//---------------------------------------------------------------------------------------------------------
// 										  OBJECT SMOKE_PARTICLE
//---------------------------------------------------------------------------------------------------------

// particle's definition
ParticleROMDef SMOKE_PARTICLE =
{
	// allocator
    __TYPE(Particle),

	// particle's minimum life span in milliseconds
	200,

	// particle's life span delta in miliseconds
	200,

	// particle's minimum mass
	FTOFIX19_13(0),

	// particle's mass delta
	FTOFIX19_13(0),
	
	// axis subject to gravity (false to disable)
	false,
	
	// function pointer to control particle's behavior
	//(void (*)(Particle))&smokeParticleBehavior,
	NULL,

	// animation description
	// used only if sprite is animated
	NULL,
	
	// animation's name to play 
	NULL
};

ParticleSystemROMDef SMOKE_PS =
{
    {
        __TYPE(ParticleSystem),
        NULL,
    },

	// reuse expired particles?
    true,
    
	// minimum generation delay in milliseconds
	50,

	// generation delay delta in miliseconds
	100,

	// maximum total particles
	10,

	// array of textures
	(const ObjectSpriteDefinition**)SMOKE_PARTICLE_IM_SPRITES,

	// auto start
	false,
	
	// particle definition
	(ParticleDefinition*)&SMOKE_PARTICLE,
	
	// minimum random distance from the center of the system for spawn
	{ITOFIX19_13(8), ITOFIX19_13(8), ITOFIX19_13(0)},

	// minimum relative spawn position
	{ITOFIX19_13(-16), ITOFIX19_13(-16), ITOFIX19_13(-1)},

	// maximum relative spawn position
	{ITOFIX19_13(16), ITOFIX19_13(16), ITOFIX19_13(-1)},

	// minimum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},

	// maximum force to apply
	// use int values in the definition to avoid overflow
	{(0), (0), (0)},
};