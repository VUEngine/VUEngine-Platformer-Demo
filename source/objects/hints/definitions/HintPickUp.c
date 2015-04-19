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

#include <AnimatedInGameEntity.h>
#include <BAnimatedSprite.h>
#include <libgccvb.h>
#include <macros.h>
#include <Hint.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HintPickUpTiles[];
extern BYTE HintPickUpMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_OPEN_ANIM =
{
	// number of frames of this animation function
	5,
	
	// frames to play in animation
	{0,1,2,3,4},

	// number of cycles a frame of animation is displayed
	__FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	&Hint_playActiveLanguageHint,
	
	// function's name
	"Open",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_ENGLISH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{5,6},

	// number of cycles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"English",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_DEUTSCH_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{7,8},
	
	// number of cycles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Deutsch",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_CLOSE_ANIM =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{4,3,2,1,0},

	// number of cycles a frame of animation is displayed
	__FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	&Hint_onCloseDone,

	// function's name
	"Close",
};

// an animation definition
AnimationDescriptionROMDef HINT_PICK_UP_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HINT_PICK_UP_OPEN_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_ENGLISH_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_DEUTSCH_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_CLOSE_ANIM,
		NULL,
	}
};

TextureROMDef HINT_PICK_UP_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_SHARED: sum of chars of all animation frames
        // __NO_ANIMATED: number of chars of whole image
        217,

        // allocation type
        __ANIMATED_SHARED,

        // char definition
        HintPickUpTiles,
    },

    // bgmap definition
    HintPickUpMap,

    // cols (max 64)
    8,

    // rows (max 64)
    3,

    // number of frames
    9,

    // palette number
    1,
};

BSpriteROMDef HINT_PICK_UP_SPRITE =
{
	// sprite's type
	__TYPE(BAnimatedSprite),

	// texture definition
	(TextureDefinition*)&HINT_PICK_UP_TX,
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_AFFINE,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	0
};

BSpriteROMDef* const HINT_PICK_UP_SPRITES[] =
{
	&HINT_PICK_UP_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef HINT_PICK_UP_MC =
{
    {
        {
            __TYPE(Hint),
            (SpriteROMDef**)HINT_PICK_UP_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {0, 0, 0, 0},

        // in game type
        kSolid,

        // if 0, width and height will be inferred from
        // the texture's size
        // width
    	0,

    	// height
    	0,

    	// deep
        0,
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&HINT_PICK_UP_ANIM,

    // initial animation
    "Open",
};