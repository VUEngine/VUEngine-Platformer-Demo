/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2017 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
// 												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <libgccvb.h>
#include <ObjectAnimatedSprite.h>
#include "Coin.h"


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE CoinTiles[];
extern BYTE CoinMap[];
extern BYTE CoinSilhouetteTiles[];
extern BYTE CoinSilhouetteMap[];
extern BYTE CoinBackTiles[];
extern BYTE CoinBackMap[];
extern BYTE CoinBackSilhouetteTiles[];
extern BYTE CoinBackSilhouetteMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef COIN_SPIN_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0, 1, 2, 3},

	// number of cycles a frame of animation is displayed
	8,

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

CharSetROMDef COIN_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    4,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SHARED_COORDINATED,

    // char definition
    CoinTiles,
};

TextureROMDef COIN_TX =
{
    // charset definition
    (CharSetDefinition*)&COIN_CH,

    // bgmap definition
    CoinMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    4,

    // palette number (0-3)
    1,
};

CharSetROMDef COIN_SILHOUETTE_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    4,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SHARED_COORDINATED,

    // char definition
    CoinSilhouetteTiles,
};

TextureROMDef COIN_SILHOUETTE_TX =
{
    // charset definition
    (CharSetDefinition*)&COIN_SILHOUETTE_CH,

    // bgmap definition
    CoinSilhouetteMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    4,

    // palette number (0-3)
    1,
};

CharSetROMDef AFFINE_COIN_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    16,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_MULTI,

    // char definition
    CoinTiles,
};

TextureROMDef AFFINE_COIN_TX =
{
    // charset definition
    (CharSetDefinition*)&AFFINE_COIN_CH,

    // bgmap definition
    CoinMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    4,

    // palette number (0-3)
    1,
};

CharSetROMDef COIN_BACK_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    4,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SHARED_COORDINATED,

    // char definition
    CoinBackTiles,
};

TextureROMDef COIN_BACK_TX =
{
    // charset definition
    (CharSetDefinition*)&COIN_BACK_CH,

    // bgmap definition
    CoinBackMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    4,

    // palette number (0-3)
    2,
};

CharSetROMDef COIN_BACK_SILHOUETTE_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    4,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SHARED_COORDINATED,

    // char definition
    CoinBackSilhouetteTiles,
};

TextureROMDef COIN_BACK_SILHOUETTE_TX =
{
    // charset definition
    (CharSetDefinition*)&COIN_BACK_SILHOUETTE_CH,

    // bgmap definition
    CoinBackSilhouetteMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    4,

    // palette number (0-3)
    2,
};

//---------------------------------------------------------------------------------------------------------
// 										  OBJECT COIN
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef COIN_SPRITE =
{
    {
        // sprite's type
        __TYPE(ObjectAnimatedSprite),

        // texture definition
        (TextureDefinition*)&COIN_TX,

        // transparent
		false,

		// displacement
        {0, 0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_OBJ,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const COIN_SPRITES[] =
{
	&COIN_SPRITE,
	NULL
};

ObjectSpriteROMDef COIN_SILHOUETTE_SPRITE =
{
    {
        // sprite's type
        __TYPE(ObjectAnimatedSprite),

        // texture definition
        (TextureDefinition*)&COIN_SILHOUETTE_TX,

        // transparent
		false,

		// displacement
        {0, 0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_OBJ,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
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
        {3, 3, 3, 3},

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
        {3, 3, 3, 3},

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
// 										  OBJECT COIN BACKGROUND
//---------------------------------------------------------------------------------------------------------

ObjectSpriteROMDef COIN_BACK_SPRITE =
{
    {
        // sprite's type
        __TYPE(ObjectAnimatedSprite),

        // texture definition
        (TextureDefinition*)&COIN_BACK_TX,

        // transparent
		false,

		// displacement
        {0, 0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_OBJ,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const COIN_BACK_SPRITES[] =
{
	&COIN_BACK_SPRITE,
	NULL
};

ObjectSpriteROMDef COIN_BACK_SILHOUETTE_SPRITE =
{
    {
        // sprite's type
        __TYPE(ObjectAnimatedSprite),

        // texture definition
        (TextureDefinition*)&COIN_BACK_SILHOUETTE_TX,

        // transparent
		false,

		// displacement
        {0, 0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_OBJ,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const COIN_BACK_SILHOUETTE_SPRITES[] =
{
	&COIN_BACK_SILHOUETTE_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef COIN_BACK_AG =
{
    {
        {
            __TYPE(Coin),
            (SpriteROMDef**)COIN_BACK_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {3, 4, 3, 4},

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

AnimatedInGameEntityROMDef COIN_BACK_SILHOUETTE_AG =
{
    {
        {
            __TYPE(Coin),
            (SpriteROMDef**)COIN_BACK_SILHOUETTE_SPRITES,
        },

        // collision detection gap (up, down, left, right)
        {3, 4, 3, 4},

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
    {
        // sprite's type
        __TYPE(ObjectAnimatedSprite),

        // texture definition
        (TextureDefinition*)&AFFINE_COIN_TX,

        // transparent
		false,

		// displacement
        {0, 0, 0, 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_AFFINE,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
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
        {3, 3, 3, 3},

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
