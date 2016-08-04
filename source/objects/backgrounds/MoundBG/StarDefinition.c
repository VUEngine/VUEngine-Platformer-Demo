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
#include <AnimatedInGameEntity.h>
#include <ObjectAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BackgroundMoundStarTiles[];
extern BYTE BackgroundMoundStarMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef  STAR_STILL_ANIM =
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
	"Still",
};

// a function which defines the frames to play
AnimationFunctionROMDef  STAR_FLASH_ANIM =
{
	// number of frames of this animation function
	6,

	// frames to play in animation
	{0, 0, 0, 1, 2, 1},

	// number of cycles a frame of animation is displayed
	6,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Flash",
};

// an animation definition
AnimationDescriptionROMDef STAR_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&STAR_STILL_ANIM,
		(AnimationFunction*)&STAR_FLASH_ANIM,
		NULL,
	}
};

CharSetROMDef STAR_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    4,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_MULTI,

    // char definition
    BackgroundMoundStarTiles,
};

TextureROMDef STAR_TX =
{
    // charset definition
    (CharSetDefinition*)&STAR_CH,

    // bgmap definition
    BackgroundMoundStarMap,

    // cols (max 64)
    1,

    // rows (max 64)
    1,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    3,

    // palette number (0-3)
    0,
};

ObjectSpriteROMDef STAR_SPRITE =
{
    {
        // sprite's type
        __TYPE(ObjectAnimatedSprite),

        // texture definition
        (TextureDefinition*)&STAR_TX,

        // displacement
        {0, 0, 0},
    },

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_OBJ,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const STAR_SPRITES[] =
{
	&STAR_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef STAR_AG =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)STAR_SPRITES,
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
        1,
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&STAR_ANIM,

    // initial animation
    "Flash",
};
