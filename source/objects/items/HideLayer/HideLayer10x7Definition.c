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
#include <macros.h>
#include <BgmapAnimatedSprite.h>
#include <AnimatedInGameEntity.h>
#include "HideLayer.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HideLayer10x7Tiles[];
extern BYTE HideLayer10x7Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef HIDE_LAYER_10x7_SOLID_ANIM =
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
	"Solid",
};

AnimationFunctionROMDef HIDE_LAYER_10x7_TRANSPARENT_ANIM =
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
	"Transparent",
};

AnimationFunctionROMDef HIDE_LAYER_10x7_TO_SOLID_ANIM =
{
	// number of frames of this animation function
	7,

	// frames to play in animation
	{6, 5, 4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	2 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"ToSolid",
};

AnimationFunctionROMDef HIDE_LAYER_10x7_TO_TRANSPARENT_ANIM =
{
	// number of frames of this animation function
	7,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6},

	// number of cycles a frame of animation is displayed
	2 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"ToTransparent",
};

// an animation definition
AnimationDescriptionROMDef HIDE_LAYER_10x7_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HIDE_LAYER_10x7_SOLID_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TRANSPARENT_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TO_SOLID_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TO_TRANSPARENT_ANIM,
		NULL,
	}
};

CharSetROMDef HIDE_LAYER_10x7_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    70,

    // allocation type
    __ANIMATED_SINGLE,

    // char definition
    HideLayer10x7Tiles,
};

TextureROMDef HIDE_LAYER_10x7_TX =
{
    // charset definition
    (CharSetDefinition*)&HIDE_LAYER_10x7_CH,

    // bgmap definition
    HideLayer10x7Map,

    // cols (max 64)
    10,

    // rows (max 64)
    7,

    // number of frames
    2,

    // palette number
    1,
};

BgmapSpriteROMDef HIDE_LAYER_10x7_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&HIDE_LAYER_10x7_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, FTOFIX19_13(SORT_FRONT_4)},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const HIDE_LAYER_10x7_SPRITES[] =
{
	&HIDE_LAYER_10x7_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef HIDE_LAYER_10x7_AG =
{
    {
        {
            __TYPE(HideLayer),
            (SpriteROMDef**)HIDE_LAYER_10x7_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {8, 8, 8, 8},

        // in game type
        kHideLayer,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,
    	
    	// depth
        8
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&HIDE_LAYER_10x7_ANIM,

    // initial animation
    "Solid",
};
