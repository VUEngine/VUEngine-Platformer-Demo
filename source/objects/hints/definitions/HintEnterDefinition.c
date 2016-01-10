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

#include <AnimatedInGameEntity.h>
#include <BgmapAnimatedSprite.h>
#include <libgccvb.h>
#include <Hint.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HintEnterTiles[];
extern BYTE HintEnterMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_OPEN_ANIM =
{
	// number of frames of this animation function
	5,
	
	// frames to play in animation
	{0, 1, 2, 3, 4},
	
	// number of cycles a frame of animation is displayed
	1 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	&Hint_playActiveLanguageHint,
	
	// function's name
	"Open",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_ENGLISH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{5, 6},

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
AnimationFunctionROMDef HINT_ENTER_DEUTSCH_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{7, 8},
	
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
AnimationFunctionROMDef HINT_ENTER_ESPANOL_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{9, 10},

	// number of cycles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Espanol",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_FRANCAIS_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{11, 12},

	// number of cycles a frame of animation is displayed
	14 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Francais",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_CLOSE_ANIM =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	1 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	&Hint_onCloseDone,

	// function's name
	"Close",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_CLOSED_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	1 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closed",
};

// an animation definition
AnimationDescriptionROMDef HINT_ENTER_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HINT_ENTER_OPEN_ANIM,
		(AnimationFunction*)&HINT_ENTER_ENGLISH_ANIM,
		(AnimationFunction*)&HINT_ENTER_DEUTSCH_ANIM,
		(AnimationFunction*)&HINT_ENTER_ESPANOL_ANIM,
		(AnimationFunction*)&HINT_ENTER_FRANCAIS_ANIM,
		(AnimationFunction*)&HINT_ENTER_CLOSE_ANIM,
		(AnimationFunction*)&HINT_ENTER_CLOSED_ANIM,
		NULL,
	}
};

CharSetROMDef HINT_ENTER_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    18,

    // allocation type
    __ANIMATED_SINGLE,

    // char definition
    HintEnterTiles,
};

TextureROMDef HINT_ENTER_TX =
{
    // charset definition
    (CharSetDefinition*)&HINT_ENTER_CH,

    // bgmap definition
    HintEnterMap,

    // cols (max 64)
    6,

    // rows (max 64)
    3,

    // number of frames
    13,

    // palette number
    1,
};

BgmapSpriteROMDef HINT_ENTER_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&HINT_ENTER_TX,

	// displacement vector
	{0, 0, FTOFIX19_13(SORT_FRONT_4)},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_AFFINE,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};
	
BgmapSpriteROMDef* const HINT_ENTER_SPRITES[] =
{
	&HINT_ENTER_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef HINT_ENTER_MC =
{
    {
        {
            __TYPE(Hint),
            (SpriteROMDef**)HINT_ENTER_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {0, 0, 0, 0},

        // in game type
        kSolid,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        0,
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&HINT_ENTER_ANIM,

    // initial animation
    "Closed",
};