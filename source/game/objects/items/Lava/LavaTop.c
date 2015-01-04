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
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE LavaTopTiles[];
extern BYTE LavaTopMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef LAVA_TOP_ANIM_1 =
{
	// number of frames of this animation function
	9,
	
	// frames to play in animation
	{0,1,2,3,4,5,6,7,8},
	
	// number of cycles a frame of animation is displayed
	10 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Lava",
	
};

// an animation definition
AnimationDescriptionROMDef LAVA_TOP_ANIM =
{
	// number of animation frames
	9,
	
	// animation functions
	{
		(AnimationFunction*)&LAVA_TOP_ANIM_1,
		NULL,
	}
};

TextureROMDef LAVA_TOP_TX =
{
    {
        // number of chars
        145,

        // allocation type
        __ANIMATED,

        // char definition
        LavaTopTiles,
    },

    // bgmap definition
    LavaTopMap,

    // cols (max 48)
    16,

    // rows (max 28)
    1,

    // palette number
    0
};

SpriteROMDef LAVA_TOP_SPRITES[] =
{
	{
		// sprite's type
		__TYPE(AnimatedSprite),

		// texture definition
		(TextureDefinition*)&LAVA_TOP_TX,
		
		// bgmap mode (BGMAP, AFFINE or H-BIAS)
		WRLD_BGMAP,
		
		// display mode
		WRLD_ON,

		// parallax displacement
		-2,
	},
	{NULL, NULL, 0, 0, 0}
};

AnimatedInGameEntityROMDef LAVA_TOP_MC =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            LAVA_TOP_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 0, 0},

        // in game type
        kLavaTop,

        // if 0, width and height will be inferred from the texture's size
        // width
    	0,

    	// height
    	0,
    	
    	// deep
        16
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&LAVA_TOP_ANIM,

    // initial animation
    "Lava",
};