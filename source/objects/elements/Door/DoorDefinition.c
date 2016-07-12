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
#include "Door.h"
#include "LayerSwitchDoor.h"
#include "GoalDoor.h"
#include "KeyDoor.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE DoorTiles[];
extern BYTE DoorMap[];
extern BYTE DoorBackTiles[];
extern BYTE DoorBackMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef  DOOR_OPENING_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0, 1, 2, 3},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Opening",
};

// a function which defines the frames to play
AnimationFunctionROMDef  DOOR_CLOSING_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closing",
};

// a function which defines the frames to play
AnimationFunctionROMDef  DOOR_OPEN_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{3},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Open",
};

// a function which defines the frames to play
AnimationFunctionROMDef  DOOR_CLOSED_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{4},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closed",
};

// a function which defines the frames to play
AnimationFunctionROMDef  DOOR_KEY_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Key",
};

// a function which defines the frames to play
AnimationFunctionROMDef  DOOR_GOAL_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{5, 6},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Goal",
};

// an animation definition
AnimationDescriptionROMDef DOOR_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&DOOR_OPENING_ANIM,
		(AnimationFunction*)&DOOR_CLOSING_ANIM,
		(AnimationFunction*)&DOOR_OPEN_ANIM,
		(AnimationFunction*)&DOOR_CLOSED_ANIM,
		(AnimationFunction*)&DOOR_KEY_ANIM,
		(AnimationFunction*)&DOOR_GOAL_ANIM,
		NULL,
	}
};

CharSetROMDef DOOR_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    85,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_MULTI,

    // char definition
    DoorTiles,
};

TextureROMDef DOOR_TX =
{
    // charset definition
    (CharSetDefinition*)&DOOR_CH,

    // bgmap definition
    DoorMap,

    // cols (max 64)
    3,

    // rows (max 64)
    4,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    7,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef DOOR_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&DOOR_TX,

	// displacement
	{0, 0, FTOFIX19_13(2)},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const DOOR_SPRITES[] =
{
	&DOOR_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef DOOR_AG =
{
    {
        {
            __TYPE(Door),
            (SpriteROMDef**)DOOR_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 6, 6},

        // in game type
        kDoor,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};

AnimatedInGameEntityROMDef LAYER_SWITCH_DOOR_AG =
{
    {
        {
            __TYPE(LayerSwitchDoor),
            (SpriteROMDef**)DOOR_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 6, 6},

        // in game type
        kDoor,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};

AnimatedInGameEntityROMDef GOAL_DOOR_AG =
{
    {
        {
            __TYPE(GoalDoor),
            (SpriteROMDef**)DOOR_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {1, 0, 1, 1},

        // in game type
        kDoor,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Open",
};

AnimatedInGameEntityROMDef KEY_DOOR_AG =
{
    {
        {
            __TYPE(KeyDoor),
            (SpriteROMDef**)DOOR_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 6, 6},

        // in game type
        kDoor,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};

BgmapSpriteROMDef AFFINE_DOOR_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&DOOR_TX,

	// displacement
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_OBJ,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const AFFINE_DOOR_SPRITES[] =
{
	&AFFINE_DOOR_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef AFFINE_DOOR_AG =
{
    {
        {
            __TYPE(Door),
            (SpriteROMDef**)AFFINE_DOOR_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 6, 6},

        // in game type
        kDoor,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        4,
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};

CharSetROMDef DOOR_BACK_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    25,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_MULTI,

    // char definition
    DoorBackTiles,
};

TextureROMDef DOOR_BACK_TX =
{
    // charset definition
    (CharSetDefinition*)&DOOR_BACK_CH,

    // bgmap definition
    DoorBackMap,

    // cols (max 64)
    2,

    // rows (max 64)
    3,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    4,

    // palette number (0-3)
    2,
};

BgmapSpriteROMDef DOOR_BACK_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&DOOR_BACK_TX,

	// displacement
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const DOOR_BACK_SPRITES[] =
{
	&DOOR_BACK_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef DOOR_BACK_AG =
{
    {
        {
            __TYPE(Door),
            (SpriteROMDef**)DOOR_BACK_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {5, 0, 2, 3},

        // in game type
        kDoor,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        1,
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};

AnimatedInGameEntityROMDef LAYER_SWITCH_DOOR_BACK_AG =
{
    {
        {
            __TYPE(LayerSwitchDoor),
            (SpriteROMDef**)DOOR_BACK_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {5, 0, 2, 3},

        // in game type
        kDoor,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// depth
        1,
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};
