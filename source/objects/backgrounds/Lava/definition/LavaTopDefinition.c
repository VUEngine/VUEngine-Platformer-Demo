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
#include <BgmapAnimatedSprite.h>
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
	8 * __FPS_ANIM_FACTOR,
	
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
	// animation functions
	{
		(AnimationFunction*)&LAVA_TOP_ANIM_1,
		NULL,
	}
};

TextureROMDef LAVA_TOP_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        48,

        // allocation type
        __ANIMATED_SINGLE,

        // char definition
        LavaTopTiles,
    },

    // bgmap definition
    LavaTopMap,

    // cols (max 64)
    48,

    // rows (max 64)
    1,

    // number of frames
    1,

    // palette number
    0
};

BgmapSpriteROMDef LAVA_TOP_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&LAVA_TOP_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, -2},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,
};

BgmapSpriteROMDef* const LAVA_TOP_SPRITES[] =
{
	&LAVA_TOP_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef LAVA_TOP_AG =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)LAVA_TOP_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {6, 0, 0, 0},

        // in game type
        kSolid,

        // width
        // if 0, width and height will be inferred from the texture's size
    	0,

    	// height
        // if 0, width and height will be inferred from the texture's size
    	0,
    	
    	// depth
        16
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&LAVA_TOP_ANIM,

    // initial animation
    "Lava",
};