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

#include <BgmapAnimatedSprite.h>
#include "SawBlade.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE SawBladeTiles[];
extern BYTE SawBladeMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunction SAW_BLADE_SPIN_ANIM =
{
	// number of frames of this animation function
	2,
	
	// frames to play in animation
	{0,1},
	
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
AnimationDescription SAW_BLADE_ANIM =
{
	// animation functions
	{
		&SAW_BLADE_SPIN_ANIM,
		NULL,
	}
};

TextureDefinition SAW_BLADE_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        18,

        // allocation type
        __ANIMATED_MULTI,

        // char definition
        SawBladeTiles,
    },

    // bgmap definition
    SawBladeMap,

    // cols (max 64)
    3,

    // rows (max 64)
    3,

    // number of frames
    2,

    // palette number
    1,
};

BgmapSpriteROMDef SAW_BLADE_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&SAW_BLADE_TX,
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	0
};

BgmapSpriteROMDef* const SAW_BLADE_SPRITES[] =
{
	&SAW_BLADE_SPRITE,
	NULL
};


SawBladeDefinition SAW_BLADE_AC =
{
    {
        {
            {
                __TYPE(SawBlade),
                (SpriteROMDef**)SAW_BLADE_SPRITES,
            },

            // collision detection gap (up, down, left, right)
            {1, 2, 2, 1},

            // in game type
            kSawBlade,

            // width
            0,
            
            // height
            0,
            
            // Depth
            10
        },

        // pointer to the animation definition for the character
        &SAW_BLADE_ANIM,

        // initial animation
        NULL
    },

    // axis
    __YAXIS,

    // direction
    __UP
};


BgmapSpriteROMDef AFFINE_SAW_BLADE_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&SAW_BLADE_TX,
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_AFFINE,
	
	// display mode
	WRLD_ON,

	// parallax displacement
	0
};

BgmapSpriteROMDef* const AFFINE_SAW_BLADE_SPRITES[] =
{
	&AFFINE_SAW_BLADE_SPRITE,
	NULL
};


SawBladeDefinition AFFINE_SAW_BLADE_AC =
{
    {
        {
            {
                __TYPE(SawBlade),
                (SpriteROMDef**)AFFINE_SAW_BLADE_SPRITES,
            },

            // collision detection gap (up, down, left, right)
            {1, 2, 2, 1},

            // in game type
            kSawBlade,

            // width
            0,
            
            // height
            0,
            
            // Depth
            10
        },

        // pointer to the animation definition for the character
        &SAW_BLADE_ANIM,

        // initial animation
        NULL
    },

    // axis
    __YAXIS,

    // direction
    __UP
};