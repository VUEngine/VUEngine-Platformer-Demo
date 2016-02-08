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
#include <BgmapAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE FlowerATiles[];
extern BYTE FlowerAMap[];


//---------------------------------------------------------------------------------------------------------
//												ANIMATION DEFINITION
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef FLOWER_A_DEFAULT_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{0, 1},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

// an animation definition
AnimationDescriptionROMDef FLOWER_A_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&FLOWER_A_DEFAULT_ANIM,
		NULL,
	}
};


//---------------------------------------------------------------------------------------------------------
// 											SPRITE DEFINITION
//---------------------------------------------------------------------------------------------------------

CharSetROMDef FLOWER_A_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    2,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SHARED,

    // char definition
    FlowerATiles,
};

TextureROMDef FLOWER_A_TX =
{
    // charset definition
    (CharSetDefinition*)&FLOWER_A_CH,

    // bgmap definition
    FlowerAMap,

    // cols (max 64)
    2,

    // rows (max 64)
    1,

        // number of frames, depending on charset's allocation type:
        // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
        // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0
};

BgmapSpriteROMDef FLOWER_A_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&FLOWER_A_TX,

	// displacement
	{FTOFIX19_13(0), FTOFIX19_13(0), FTOFIX19_13(0)},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const FLOWER_A_SPRITES[] =
{
	&FLOWER_A_SPRITE,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											ENTITY DEFINITION
//---------------------------------------------------------------------------------------------------------

AnimatedInGameEntityROMDef FLOWER_A_AG =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)FLOWER_A_SPRITES,
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
        8
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&FLOWER_A_ANIM,

    // initial animation
    "Default",
};
