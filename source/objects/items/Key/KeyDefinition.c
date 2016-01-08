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
#include <ObjectAnimatedSprite.h>
#include "Key.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE KeyTiles[];
extern BYTE KeyMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef KEY_SPIN_ANIM =
{
	// number of frames of this animation function
	8,
	
	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6, 7},
	
	// number of cycles a frame of animation is displayed
	8 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Spin",
};

// an animation definition
AnimationDescriptionROMDef KEY_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&KEY_SPIN_ANIM,
		NULL,
	}
};

CharSetROMDef KEY_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    32,

    // allocation type
    __ANIMATED_MULTI,

    // char definition
    KeyTiles,
};

TextureROMDef KEY_TX =
{
    // charset definition
    (CharSetDefinition*)&KEY_CH,

    // bgmap definition
    KeyMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // number of frames
    8,

    // palette number
    1,
};

ObjectSpriteROMDef KEY_SPRITE =
{
	// sprite's type
	__TYPE(ObjectAnimatedSprite),

	// texture definition
	(TextureDefinition*)&KEY_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, FTOFIX19_13(SORT_BACK_3)},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_OBJ,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const KEY_SPRITES[] =
{
	&KEY_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef KEY_AG =
{
    {
        {
            __TYPE(Key),
            (SpriteROMDef**)KEY_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {1, 1, 1, 2},

        // in game type
        kKey,

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
    (AnimationDescription*)&KEY_ANIM,

    // initial animation
    "Spin",
};