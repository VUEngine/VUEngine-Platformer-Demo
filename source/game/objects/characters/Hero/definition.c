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
#include "Hero.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HeroTiles[];
extern BYTE HeroMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef HERO_IDLE_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{4,5},
	
	// number of cycles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Idle",
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_WALKING_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{13, 14},
	
	// number of cycles a frame of animation is displayed
	9 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Walk",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMPING_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{6},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Jump",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_FALLING_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{7},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Fall",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_SLIDING_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{7},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Slide",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_HIT_FRONT_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{8},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"HitFront",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_HIT_BEHIND_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{8},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"HitBehind",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_HIT_FIRE_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{8},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"HitFire",
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMP_BACK_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{12},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"JumpBack",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_JUMP_FRONT_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{13},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"JumpFront",
};


// a function which defines the frames to play
AnimationFunctionROMDef HERO_FRONT_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{0,1},
	
	// number of cycles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Front",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_BACK_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{2,3},
	
	// number of cycles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Back",
};


// an animation definition
AnimationDescriptionROMDef HERO_ANIM =
{
	// total number of animation frames
	15,
	
	// animation functions
	{
		(AnimationFunction*)&HERO_IDLE_ANIM,
		(AnimationFunction*)&HERO_WALKING_ANIM,
		(AnimationFunction*)&HERO_JUMPING_ANIM,
		(AnimationFunction*)&HERO_FALLING_ANIM,
		(AnimationFunction*)&HERO_SLIDING_ANIM,
		(AnimationFunction*)&HERO_HIT_FRONT_ANIM,
		(AnimationFunction*)&HERO_HIT_BEHIND_ANIM,
		(AnimationFunction*)&HERO_JUMP_BACK_ANIM,
		(AnimationFunction*)&HERO_JUMP_FRONT_ANIM,
		(AnimationFunction*)&HERO_FRONT_ANIM,
		(AnimationFunction*)&HERO_BACK_ANIM,
		NULL,
	}
};

TextureROMDef HERO_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        9,

        // allocation type
        __ANIMATED,

        // char definition
        HeroTiles,
    },

    // bgmap definition
    HeroMap,

    // cols (max 48)
    3,

    // rows (max 28)
    3,

    // palette number
    1,
};

SpriteROMDef HERO_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(AnimatedSprite),

		// texture definition
		(TextureDefinition*)&HERO_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_AFFINE,
		//WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
	{NULL, NULL, 0, 0, 0}
};

ActorROMDef HERO_MC =
{
    {
        {
            __TYPE(Hero),
            HERO_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {5, 1, 4, 4},

        // in game type
        kHero,

        // if 0, width and height will be inferred from 
        // the texture's size
        // width
    	0,

    	// height
    	0,
    	
    	// deep
        8
    },

    // pointer to the animation definition for the character
    (AnimationDescription*)&HERO_ANIM,

    // initial animation
    NULL,
};