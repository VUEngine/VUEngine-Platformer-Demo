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
#include <ObjectAnimatedSprite.h>
#include "../behaviors.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CoinTiles[];
extern BYTE CoinMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef TEST_PARTICLE_SPIN_ANIM =
{
	// number of frames of this animation function
	4,
	
	// frames to play in animation
	{0,1,2,3},
	
	// number of cycles a frame of animation is displayed
	2 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Spin",
};

// an animation definition
AnimationDescriptionROMDef TEST_PARTICLE_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&TEST_PARTICLE_SPIN_ANIM,
		NULL,
	}
};

TextureROMDef OBJECT_TEST_PARTICLE_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        28,

        // allocation type
		__ANIMATED_MULTI,
        
        // char definition
        CoinTiles,
    },

    // bgmap definition
    CoinMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // number of frames
    7,

    // palette number
    1,
};


//---------------------------------------------------------------------------------------------------------
// 										  OBJECT TEST_PARTICLE
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef OBJECT_TEST_PARTICLE_SPRITE =
{
	// sprite's type
	__TYPE(ObjectAnimatedSprite),

	// texture definition
	(TextureDefinition*)&OBJECT_TEST_PARTICLE_TX,
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_OBJ,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	0		
};

ObjectSpriteROMDef* const OBJECT_TEST_PARTICLE_SPRITES[] =
{
	&OBJECT_TEST_PARTICLE_SPRITE,
	NULL
};

// particle's definition
ParticleROMDef TEST_PARTICLE =
{
	// allocator
    __TYPE(Particle),

	// particle's minimum life span in milliseconds
	1000,

	// particle's maximum life span in milliseconds
	2000,

	// particle's minimum mass
	FTOFIX19_13(5.0f),

	// particle's maximum mass
	FTOFIX19_13(10.0f),
	
	// axis subject to gravity (false to disable)
	__YAXIS,
	
	// function pointer to control particle's behavior
	(void (*)(Particle))&testParticleBehavior,

	// animation description
	// used only if sprite is animated
	(AnimationDescription*)&TEST_PARTICLE_ANIM,
	
	// animation's name to play 
	"Spin"
};

ParticleSystemROMDef TEST_PS =
{
    {
        __TYPE(ParticleSystem),
        NULL,
    },

	// minimum generation delay in milliseconds
	150,

	// maximum generation delay in milliseconds
	350,

	// maximum total particles
	15,

	// array of textures
	(const ObjectSpriteDefinition**)OBJECT_TEST_PARTICLE_SPRITES,

	// auto start
	true,
	
	// particle definition
	(ParticleDefinition*)&TEST_PARTICLE,
	
	// minimum random distance from the center of the system for spawn
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},

	// minimum relative spawn position
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},

	// maximum relative spawn position
	{ITOFIX19_13(0), ITOFIX19_13(0), ITOFIX19_13(0)},
	
	// minimum force to apply
	// use int values in the definition to avoid overflow
	{(-5000), (-20000), (0)},

	// maximum force to apply
	// use int values in the definition to avoid overflow
	{(5000), (-16000), (0)},
};