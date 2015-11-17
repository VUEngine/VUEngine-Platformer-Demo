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

#include <BgmapAnimatedSprite.h>
#include <Actor.h>
#include <macros.h>
#include "Cannon.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CannonTiles[];
extern BYTE CannonMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunction CANNON_IDLE_ANIM =
{
	// number of frames of this animation function
	1,
	
	// frames to play in animation
	{0},
	
	// number of cycles a frame of animation is displayed
	1 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	false,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Idle",
};

AnimationFunction CANNON_SHOOT_ANIM =
{
	// number of frames of this animation function
	15,

	// frames to play in animation
	{1,2,1,2,0,0,0,0,0,0,3,4,5,6,0},

	// number of cycles a frame of animation is displayed
	6 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	&Cannon_spawnCannonBall,

	// function's name
	"Shoot",
};

// an animation definition
AnimationDescription CANNON_ANIM =
{
	// animation functions
	{
		&CANNON_IDLE_ANIM,
		&CANNON_SHOOT_ANIM,
		NULL,
	}
};

TextureDefinition CANNON_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        9,

        // allocation type
        __ANIMATED_SHARED,

        // char definition
        CannonTiles,
    },

    // bgmap definition
    CannonMap,

    // cols (max 64)
    3,

    // rows (max 64)
    3,

    // number of frames
    7,

    // palette number
    1,
};

BgmapSpriteROMDef CANNON_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&CANNON_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON) (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const CANNON_SPRITES[] =
{
	&CANNON_SPRITE,
	NULL
};

ActorROMDef CANNON_AC =
{
    {
        {
            {
                __TYPE(Cannon),
                (SpriteROMDef**)CANNON_SPRITES,
            },

            // collision detection gap (up, down, left, right)
            {2, 2, 2, 2},

            // in game type
            kSolid,

            // width
            0,

            // height
            0,

            // depth
            10
        },

        // pointer to the animation definition for the character
        &CANNON_ANIM,

        // initial animation
        "Idle"
    },

    // friction for physics
    ITOFIX19_13(0),

    // elasticity for physics
    ITOFIX19_13(0),

    // mass
    ITOFIX19_13(10)
};