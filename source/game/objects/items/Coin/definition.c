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
#include "Coin.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CoinLTiles[];
extern BYTE CoinLMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef COIN_SPIN_ANIM =
{
	// number of frames of this animation function
	4,
	
	// frames to play in animation
	{0,1,2,3},
	
	// number of cycles a frame of animation is displayed
	10 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Spin",
};

// a function which defines the frames to play
AnimationFunctionROMDef COIN_TAKEN_ANIM =
{
	// number of frames of this animation function
	3,
	
	// frames to play in animation
	{4,5,6},
	
	// number of cycles a frame of animation is displayed
	10 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	&Coin_removeFromStage,
	
	// function's name
	"Taken",
};

// an animation definition
AnimationDescriptionROMDef COIN_ANIM =
{
	// number of animation frames
	7,
	
	// animation functions
	{
		(AnimationFunction*)&COIN_SPIN_ANIM,
		(AnimationFunction*)&COIN_TAKEN_ANIM,
		NULL,
	}
};

TextureROMDef COIN_TX =
{
    {
        // number of chars
        28,

        // allocation type
        __ANIMATED_SHARED,

        // char definition
        CoinLTiles,
    },

    // bgmap definition
    CoinLMap,

    // cols (max 48)
    2,

    // rows (max 28)
    2,

    // palette number
    1,
};

SpriteROMDef COIN_SPRITES[] =
{
	{
		// texture definition
		(TextureDefinition*)&COIN_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_AFFINE,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		0,
	},
};

AnimatedInGameEntityROMDef COIN_MC =
{
    {
        {
            __TYPE(Coin),
            __SPRITE_ARRAY(COIN_SPRITES),
        },

        // collision detection gap (up, down, left, right)
        {4, 4, 4, 4},

        // in game type
        kCoin,

        // deep
        4,
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&COIN_ANIM,

    // initial animation
    "Spin",
};