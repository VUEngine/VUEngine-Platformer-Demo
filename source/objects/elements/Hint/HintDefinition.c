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

extern BYTE HintTiles[];
extern BYTE HintMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_OPEN_ANIM =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{0, 1, 2, 3, 4},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hint_playActiveLanguageHint,

	// function's name
	"Open",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_CLOSE_ANIM =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hint_onCloseDone,

	// function's name
	"Close",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_CLOSED_ANIM =
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
	"Closed",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_ENTER_ENGLISH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{5, 6},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterEnglish",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_ENTER_DEUTSCH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{7, 8},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterDeutsch",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_ENTER_ESPANOL_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{9, 10},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterEspanol",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_ENTER_FRANCAIS_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{11, 12},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterFrancais",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_PICK_UP_ENGLISH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{13, 14},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpEnglish",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_PICK_UP_DEUTSCH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{15, 16},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpDeutsch",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_PICK_UP_ESPANOL_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{17, 18},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpEspanol",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_PICK_UP_FRANCAIS_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{19, 20},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpFrancais",
};

// a function which defines the frames to play
AnimationFunctionROMDef  HINT_KEY_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{21, 22},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Key",
};

// an animation definition
AnimationDescriptionROMDef HINT_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HINT_OPEN_ANIM,
		(AnimationFunction*)&HINT_CLOSE_ANIM,
		(AnimationFunction*)&HINT_CLOSED_ANIM,
		(AnimationFunction*)&HINT_ENTER_ENGLISH_ANIM,
		(AnimationFunction*)&HINT_ENTER_DEUTSCH_ANIM,
		(AnimationFunction*)&HINT_ENTER_ESPANOL_ANIM,
		(AnimationFunction*)&HINT_ENTER_FRANCAIS_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_ENGLISH_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_DEUTSCH_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_ESPANOL_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_FRANCAIS_ANIM,
		(AnimationFunction*)&HINT_KEY_ANIM,
		NULL,
	}
};

CharSetROMDef HINT_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    24,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SINGLE,

    // char definition
    HintTiles,
};

TextureROMDef HINT_TX =
{
    // charset definition
    (CharSetDefinition*)&HINT_CH,

    // bgmap definition
    HintMap,

    // cols (max 64)
    8,

    // rows (max 64)
    3,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    23,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef HINT_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapAnimatedSprite),

        // texture definition
        (TextureDefinition*)&HINT_TX,

        // displacement
        {FTOFIX19_13(28), FTOFIX19_13(-21), 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const HINT_SPRITES[] =
{
	&HINT_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef HINT_MC =
{
    {
        {
            __TYPE(Hint),
            (SpriteROMDef**)HINT_SPRITES,
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
    (AnimationDescription*)&HINT_ANIM,

    // initial animation
    "Closed",
};

