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
#include <BgmapAnimatedSprite.h>
#include <CameraTriggerEntity.h>

#include "Hero.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HeroTiles[];
extern BYTE HeroBandanaTiles[];
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
	{4, 5},
	
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
AnimationFunctionROMDef HERO_HIT_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{8},
	
	// number of cycles a frame of animation is displayed
	80 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Hit",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_CLIMB_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{9, 10},

	// number of cycles a frame of animation is displayed
	8 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Climb",
};

// a function which defines the frames to play
AnimationFunctionROMDef HERO_FRONT_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{0, 1},
	
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
	{2, 3},
	
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
	// animation functions
	{
		(AnimationFunction*)&HERO_IDLE_ANIM,
		(AnimationFunction*)&HERO_WALKING_ANIM,
		(AnimationFunction*)&HERO_JUMPING_ANIM,
		(AnimationFunction*)&HERO_FALLING_ANIM,
		(AnimationFunction*)&HERO_SLIDING_ANIM,
		(AnimationFunction*)&HERO_HIT_ANIM,
		(AnimationFunction*)&HERO_CLIMB_ANIM,
		(AnimationFunction*)&HERO_FRONT_ANIM,
		(AnimationFunction*)&HERO_BACK_ANIM,
		NULL,
	}
};

CharSetROMDef HERO_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    9,

    // allocation type
    __ANIMATED_SINGLE,

    // char definition
    HeroTiles,
};

CharSetROMDef HERO_BANDANA_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    9,

    // allocation type
    __ANIMATED_SINGLE,

    // char definition
    HeroBandanaTiles,
};

TextureROMDef HERO_TX =
{
    (CharSetDefinition*)&HERO_CH,

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

BgmapSpriteROMDef HERO_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&HERO_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_AFFINE,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const HERO_SPRITES[] =
{
	&HERO_SPRITE,
	NULL
};

ActorROMDef HERO_AC =
{
	{
	    {
	        {
	            __TYPE(Hero),
	            (SpriteROMDef**)HERO_SPRITES,
	        },

	        // collision detection gap (up, down, left, right)
	        {5, 1, 6, 6},

	        // in game type
	        kHero,

	        // width
	        // if 0, width and height will be inferred from the texture's size
	    	0,

	    	// height
	        // if 0, width and height will be inferred from the texture's size
	    	0,

	    	// depth
	        1
	    },

	    // pointer to the animation definition for the character
	    (AnimationDescription*)&HERO_ANIM,

	    // initial animation
	    NULL,
	},

	// friction for physics
	ITOFIX19_13(0),

	// elasticity for physics
	FTOFIX19_13(0.0f),

	// mass
	ITOFIX19_13(10)
};


CameraTriggerEntityROMDef CAMERA_BOUNDING_BOX_IG =
{
    {
        {
            __TYPE(CameraTriggerEntity),
            NULL,
        },

        // collision detection gap (up, down, left, right)
        {0, 0, 0, 0},

        // in game type
        kCameraTarget,

    	// width
        // if 0, width and height will be inferred from the texture's size
    	6 * 8,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	18 * 8,

    	// depth
    	4 * 8
    },

    // shape type
    kInverseCuboid,
    
    // moves 
    true
};