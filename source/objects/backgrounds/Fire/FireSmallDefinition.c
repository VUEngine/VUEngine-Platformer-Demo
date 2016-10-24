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

extern BYTE FireSmallTiles[];
extern BYTE FireSmallMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef FIRE_SMALL_BURN_ANIM =
{
	// number of frames of this animation function
	3,

	// frames to play in animation
	{0, 1, 2},

	// number of cycles a frame of animation is displayed
	6,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Burn",
};

// an animation definition
AnimationDescriptionROMDef FIRE_SMALL_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&FIRE_SMALL_BURN_ANIM,
		NULL,
	}
};

CharSetROMDef FIRE_SMALL_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    1,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SHARED,

    // char definition
    FireSmallTiles,
};

TextureROMDef FIRE_SMALL_TX =
{
    // charset definition
    (CharSetDefinition*)&FIRE_SMALL_CH,

    // bgmap definition
    FireSmallMap,

    // cols (max 64)
    1,

    // rows (max 64)
    1,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0,
};

ObjectSpriteROMDef FIRE_SMALL_SPRITE =
{
    {
        // sprite's type
        __TYPE(ObjectAnimatedSprite),

        // texture definition
        (TextureDefinition*)&FIRE_SMALL_TX,

        // displacement
        {0, 0, FTOFIX19_13(1)},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_OBJ,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const FIRE_SMALL_SPRITES[] =
{
	&FIRE_SMALL_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef FIRE_SMALL_AG =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)FIRE_SMALL_SPRITES,
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
    (AnimationDescription*)&FIRE_SMALL_ANIM,

    // initial animation
    "Burn",
};