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

extern BYTE TorchTiles[];
extern BYTE TorchMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef TORCH_BURN_ANIM =
{
	// number of frames of this animation function
	3,

	// frames to play in animation
	{0, 1, 2},

	// number of cycles a frame of animation is displayed
	5 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Burn",
};

// an animation definition
AnimationDescriptionROMDef TORCH_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&TORCH_BURN_ANIM,
		NULL,
	}
};

CharSetROMDef TORCH_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    3,

    // allocation type
    __ANIMATED_SHARED,

    // char definition
    TorchTiles,
};

TextureROMDef TORCH_TX =
{
    // charset definition
    (CharSetDefinition*)&TORCH_CH,

    // bgmap definition
    TorchMap,

    // cols (max 64)
    1,

    // rows (max 64)
    3,

    // number of frames
    4,

    // palette number
    0
};

ObjectSpriteROMDef TORCH_SPRITE =
{
	// sprite's type
	__TYPE(ObjectAnimatedSprite),

	// texture definition
	(TextureDefinition*)&TORCH_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, FTOFIX19_13(1)},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_OBJ,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const TORCH_SPRITES[] =
{
	&TORCH_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef TORCH_AG =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)TORCH_SPRITES,
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
    (AnimationDescription*)&TORCH_ANIM,

    // initial animation
    "Burn",
};