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
#include <BgmapAnimatedSprite.h>
#include <ObjectAnimatedSprite.h>
#include "Coin.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CoinTiles[];
extern BYTE CoinMap[];
extern BYTE CoinSilhouetteTiles[];
extern BYTE CoinSilhouetteMap[];


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
	8 * __FPS_ANIM_FACTOR,
	
	// whether to play it in loop or not
	true,
	
	// method to call on function completion
	NULL,
	
	// function's name
	"Spin",
};

// an animation definition
AnimationDescriptionROMDef COIN_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&COIN_SPIN_ANIM,
		NULL,
	}
};

TextureROMDef COIN_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        4,

        // allocation type
        __ANIMATED_SHARED_COORDINATED,
        
        // char definition
        CoinTiles,
    },

    // bgmap definition
    CoinMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // number of frames
    4,

    // palette number
    1,
};

TextureROMDef COIN_SILHOUETTE_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        4,

        // allocation type
        __ANIMATED_SHARED_COORDINATED,

        // char definition
        CoinSilhouetteTiles,
    },

    // bgmap definition
    CoinSilhouetteMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // number of frames
    4,

    // palette number
    2,
};

TextureROMDef AFFINE_COIN_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        16,

        // allocation type
        __ANIMATED_MULTI,
        
        // char definition
        CoinTiles,
    },

    // bgmap definition
    CoinMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // number of frames
    4,

    // palette number
    1,
};

//---------------------------------------------------------------------------------------------------------
// 										  OBJECT COIN
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef COIN_SPRITE =
{
	// sprite's type
	__TYPE(ObjectAnimatedSprite),

	// texture definition
	(TextureDefinition*)&COIN_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_OBJ,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const COIN_SPRITES[] =
{
	&COIN_SPRITE,
	NULL
};

ObjectSpriteROMDef COIN_SILHOUETTE_SPRITE =
{
	// sprite's type
	__TYPE(ObjectAnimatedSprite),

	// texture definition
	(TextureDefinition*)&COIN_SILHOUETTE_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_OBJ,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const COIN_SILHOUETTE_SPRITES[] =
{
	&COIN_SILHOUETTE_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef COIN_AG =
{
    {
        {
            __TYPE(Coin),
            (SpriteROMDef**)COIN_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {4, 4, 4, 4},

        // in game type
        kCoin,

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
    (AnimationDescription*)&COIN_ANIM,

    // initial animation
    "Spin",
};

AnimatedInGameEntityROMDef COIN_SILHOUETTE_AG =
{
    {
        {
            __TYPE(Coin),
            (SpriteROMDef**)COIN_SILHOUETTE_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {4, 4, 4, 4},

        // in game type
        kCoin,

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
    (AnimationDescription*)&COIN_ANIM,

    // initial animation
    "Spin",
};


//---------------------------------------------------------------------------------------------------------
// 										  AFFINE COIN
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef AFFINE_COIN_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&AFFINE_COIN_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_AFFINE,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

ObjectSpriteROMDef* const AFFINE_COIN_SPRITES[] =
{
	&AFFINE_COIN_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef AFFINE_COIN_AG =
{
    {
        {
            __TYPE(Coin),
            (SpriteROMDef**)AFFINE_COIN_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {4, 4, 4, 4},

        // in game type
        kCoin,

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
    (AnimationDescription*)&COIN_ANIM,

    // initial animation
    "Spin",
};
