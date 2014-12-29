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
#include "Door.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE DoorTiles[];
extern BYTE DoorMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

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

// a function which defines the frames to play
AnimationFunctionROMDef DOOR_OPEN_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{1},
	
	// number of cycles a frame of animation is displayed
	0,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Open",
	
};

// an animation definition
AnimationDescriptionROMDef DOOR_ANIM =
{
	// number of animation frames
	2,
	
	// animation functions
	{
		(AnimationFunction*)&DOOR_CLOSED_ANIM,
		(AnimationFunction*)&DOOR_OPEN_ANIM,
		NULL,
	}
};

TextureROMDef DOOR_TX =
{
    {
        // number of chars
        12,

        // allocation type
        __ANIMATED_SHARED,

        // char definition
        DoorTiles,
    },

    // bgmap definition
    DoorMap,

    // cols (max 48)
    3,

    // rows (max 28)
    4,

    // palette number
    1
};

SpriteROMDef DOOR_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(AnimatedSprite),

		// texture definition
		(TextureDefinition*)&DOOR_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_AFFINE,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		1,
	},
	{NULL, NULL, 0, 0, 0}
};

AnimatedInGameEntityROMDef DOOR_MC =
{
    {
        {
            __TYPE(Door),
            DOOR_SPRITES,
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
    	
    	// deep
        4
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&DOOR_ANIM,

    // initial animation
    "Closed",
};
