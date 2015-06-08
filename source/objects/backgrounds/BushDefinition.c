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
#include <AnimatedInGameEntity.h>
#include <ObjectAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BushTiles[];
extern BYTE BushMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef BUSH_STILL_ANIM =
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
	"Still",
};

// a function which defines the frames to play
AnimationFunctionROMDef BUSH_WINDY_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{0,1},

	// number of cycles a frame of animation is displayed
	15 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Windy",
};

// an animation definition
AnimationDescriptionROMDef BUSH_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&BUSH_STILL_ANIM,
		(AnimationFunction*)&BUSH_WINDY_ANIM,
		NULL,
	}
};

TextureROMDef BUSH_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        3,

        // allocation type
        __ANIMATED_SHARED,

        // char definition
        BushTiles,
    },

    // bgmap definition
    BushMap,

    // cols (max 64)
    3,

    // rows (max 64)
    1,

    // number of frames
    2,

    // palette number
    1
};

ObjectSpriteROMDef BUSH_SPRITE =
{
	// sprite's type
	__TYPE(ObjectAnimatedSprite),

	// texture definition
	(TextureDefinition*)&BUSH_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_OBJ,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const BUSH_SPRITES[] =
{
	&BUSH_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef BUSH_AG =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)BUSH_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {0, 0, 0, 0},

        // in game type
        kNotSolid,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,
    	
    	// depth
        1
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&BUSH_ANIM,

    // initial animation
    "Windy",
};