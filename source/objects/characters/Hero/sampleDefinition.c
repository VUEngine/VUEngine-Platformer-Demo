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
#include <BgmapAnimatedSprite.h>
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
AnimationFunctionROMDef DUMMY_HERO_IDLE_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_WALKING_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_JUMPING_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_FALLING_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_SLIDING_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_HIT_FRONT_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_HIT_BEHIND_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_HIT_FIRE_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_JUMP_BACK_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_JUMP_FRONT_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_FRONT_ANIM =
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
AnimationFunctionROMDef DUMMY_HERO_BACK_ANIM =
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
AnimationDescriptionROMDef DUMMY_HERO_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&DUMMY_HERO_IDLE_ANIM,
		(AnimationFunction*)&DUMMY_HERO_WALKING_ANIM,
		(AnimationFunction*)&DUMMY_HERO_JUMPING_ANIM,
		(AnimationFunction*)&DUMMY_HERO_FALLING_ANIM,
		(AnimationFunction*)&DUMMY_HERO_SLIDING_ANIM,
		(AnimationFunction*)&DUMMY_HERO_HIT_FRONT_ANIM,
		(AnimationFunction*)&DUMMY_HERO_HIT_BEHIND_ANIM,
		(AnimationFunction*)&DUMMY_HERO_JUMP_BACK_ANIM,
		(AnimationFunction*)&DUMMY_HERO_JUMP_FRONT_ANIM,
		(AnimationFunction*)&DUMMY_HERO_FRONT_ANIM,
		(AnimationFunction*)&DUMMY_HERO_BACK_ANIM,
		NULL,
	}
};

TextureROMDef DUMMY_HERO_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        9,

        // allocation type
        __ANIMATED_SHARED_COORDINATED,

        // char definition
        HeroTiles,
    },

    // bgmap definition
    HeroMap,

    // cols (max 64)
    3,

    // rows (max 64)
    3,

    // number of frames
    15,

    // palette number
    1,
};

ObjectSpriteROMDef DUMMY_HERO_SPRITE =
{
	// sprite's type
	__TYPE(ObjectAnimatedSprite),

	// texture definition
	(TextureDefinition*)&DUMMY_HERO_TX,
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	0
};

ObjectSpriteROMDef* const DUMMY_HERO_SPRITES[] =
{
	&DUMMY_HERO_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef DUMMY_HERO_AC =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)DUMMY_HERO_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {5, 1, 4, 4},

        // in game type
        kHero,

        // if 0, width and height will be inferred from the texture's size
        // width
    	0,

    	// height
    	0,
    	
    	// Depth
        8
    },

    // pointer to the animation definition for the character
    (AnimationDescription*)&DUMMY_HERO_ANIM,

    // initial animation
    NULL,
};
