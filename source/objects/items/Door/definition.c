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
#include "Door.h"
#include "EnterRoomDoor.h"
#include "ExitRoomDoor.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE DoorTiles[];
extern BYTE DoorMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef DOOR_OPENINIG_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0,1,2,3},

	// number of cycles a frame of animation is displayed
	5 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,
	
	// function's name
	"Opening",
};

// a function which defines the frames to play
AnimationFunctionROMDef DOOR_CLOSING_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	5 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,
	
	// function's name
	"Closing",
};

// a function which defines the frames to play
AnimationFunctionROMDef DOOR_OPENED_ANIM =
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
	"Opened",
};

// a function which defines the frames to play
AnimationFunctionROMDef DOOR_CLOSED_ANIM =
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
	"Closed",
};

// an animation definition
AnimationDescriptionROMDef DOOR_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&DOOR_OPENINIG_ANIM,
		(AnimationFunction*)&DOOR_CLOSING_ANIM,
		(AnimationFunction*)&DOOR_OPENED_ANIM,
		(AnimationFunction*)&DOOR_CLOSED_ANIM,
		NULL,
	}
};

TextureROMDef DOOR_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        49,

        // allocation type
        __ANIMATED_MULTI,

        // char definition
        DoorTiles,
    },

    // bgmap definition
    DoorMap,

    // cols (max 64)
    3,

    // rows (max 64)
    4,

    // number of frames
    4,

    // palette number
    1
};

BgmapSpriteROMDef DOOR_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&DOOR_TX,
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	1		
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

        // if 0, width and height will be inferred from 
        // the texture's size
        // width
    	0,

    	// height
    	0,
    	
    	// Depth
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};

AnimatedInGameEntityROMDef ENTER_ROOM_DOOR_AG =
{
    {
        {
            __TYPE(EnterRoomDoor),
            (SpriteROMDef**)DOOR_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 6, 6},

        // in game type
        kDoor,

        // if 0, width and height will be inferred from 
        // the texture's size
        // width
    	0,

    	// height
    	0,
    	
    	// Depth
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};

AnimatedInGameEntityROMDef EXIT_ROOM_DOOR_AG =
{
    {
        {
            __TYPE(ExitRoomDoor),
            (SpriteROMDef**)DOOR_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 6, 6},

        // in game type
        kDoor,

        // if 0, width and height will be inferred from 
        // the texture's size
        // width
    	0,

    	// height
    	0,
    	
    	// Depth
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
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_AFFINE,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	1		
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

        // if 0, width and height will be inferred from 
        // the texture's size
        // width
    	0,

    	// height
    	0,
    	
    	// Depth
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};