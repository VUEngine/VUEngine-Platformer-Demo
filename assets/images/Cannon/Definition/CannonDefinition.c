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

#include <BgmapAnimatedSprite.h>
#include <Actor.h>
#include <macros.h>
#include "Cannon.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CannonTiles[];
extern BYTE CannonMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef CANNON_IDLE_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Idle",
};

AnimationFunctionROMDef CANNON_SHOOT_ANIM =
{
	// number of frames of this animation function
	15,

	// frames to play in animation
	{1, 2, 1, 2, 0, 0, 0, 0, 0, 0, 3, 4, 5, 6, 0},

	// number of cycles a frame of animation is displayed
	6,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Cannon_spawnCannonBall,

	// function's name
	"Shoot",
};

// an animation definition
AnimationDescriptionROMDef CANNON_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&CANNON_IDLE_ANIM,
		(AnimationFunction*)&CANNON_SHOOT_ANIM,
		NULL,
	}
};

CharSetROMDef CANNON_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	64,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	CannonTiles,
};

TextureROMDef CANNON_TX =
{
	// charset definition
	(CharSetDefinition*)&CANNON_CH,

	// bgmap definition
	CannonMap,

	// cols (max 64)
	3,

	// rows (max 64)
	3,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	7,

	// palette number (0-3)
	1,
};

BgmapSpriteROMDef CANNON_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&CANNON_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine / hbias manipulation function
	// void (*)(BgmapSprite);
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const CANNON_SPRITES[] =
{
	&CANNON_SPRITE,
	NULL
};

ActorROMDef CANNON_AC =
{
	{
		{
			{
				__TYPE(Cannon),
				(SpriteROMDef**)CANNON_SPRITES,
			},

			// collision detection gap (up, down, left, right)
			{2, 2, 2, 2},

			// in game type
			kSolid,

			// width
			0,

			// height
			0,

			// depth
			10
		},

		// pointer to the animation definition for the character
		(AnimationDescription*)&CANNON_ANIM,

		// initial animation
		"Idle"
	},

	// friction for physics
	ITOFIX19_13(0),

	// elasticity for physics
	ITOFIX19_13(0),

	// mass
	ITOFIX19_13(10)
};

