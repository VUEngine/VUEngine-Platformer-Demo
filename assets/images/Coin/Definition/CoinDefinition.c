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
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <libgccvb.h>
#include <ObjectAnimatedSprite.h>
#include <Ball.h>
#include "Coin.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
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
//												DEFINITIONS
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
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
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

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,
};

CharSetROMDef COIN_SILHOUETTE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
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

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,
};

CharSetROMDef AFFINE_COIN_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	16,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
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

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,

	// recyclable
	false,
};

CharSetROMDef COIN_BACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
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

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	2,

	// recyclable
	false,
};

CharSetROMDef COIN_BACK_SILHOUETTE_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
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

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	2,

	// recyclable
	false,
};

//---------------------------------------------------------------------------------------------------------
//											OBJECT COIN
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

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

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

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const COIN_SILHOUETTE_SPRITES[] =
{
	&COIN_SILHOUETTE_SPRITE,
	NULL
};

ShapeROMDef COIN_SHAPES[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{4, 4, 4},

		// displacement (x, y, z)
		{__I_TO_FIX10_6(0), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kCollectablesLayer,

		/// layers to ignore when checking for collisions
		kNoLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

CoinROMDef COIN_AG =
{
	{
		// class allocator
		__TYPE(Coin),

		// sprites
		(SpriteROMDef**)COIN_SPRITES,

		// collision shapes
		(ShapeDefinition*)COIN_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kCoin,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&COIN_ANIM,

	// initial animation
	"Spin",
};

CoinROMDef COIN_SILHOUETTE_AG =
{
	{
		// class allocator
		__TYPE(Coin),

		// sprites
		(SpriteROMDef**)COIN_SILHOUETTE_SPRITES,

		// collision shapes
		(ShapeDefinition*)COIN_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kCoin,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&COIN_ANIM,

	// initial animation
	"Spin",
};


//---------------------------------------------------------------------------------------------------------
//											OBJECT COIN BACKGROUND
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

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

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

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJECT,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

ObjectSpriteROMDef* const COIN_BACK_SILHOUETTE_SPRITES[] =
{
	&COIN_BACK_SILHOUETTE_SPRITE,
	NULL
};


ShapeROMDef COIN_BACK_SHAPES[] =
{
	{
		// shape
		__TYPE(Ball),

		// size (x, y, z)
		{4, 4, 4},

		// displacement (x, y, z)
		{__I_TO_FIX10_6(0), __I_TO_FIX10_6(0), __I_TO_FIX10_6(0)},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kCollectablesLayer,

		/// layers to ignore when checking for collisions
		kNoLayer,
	},

	{NULL, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kNoLayer, kNoLayer}
};

CoinROMDef COIN_BACK_AG =
{
	{
		// class allocator
		__TYPE(Coin),

		// sprites
		(SpriteROMDef**)COIN_BACK_SPRITES,

		// collision shapes
		(ShapeDefinition*)COIN_BACK_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kCoin,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&COIN_ANIM,

	// initial animation
	"Spin",
};

CoinROMDef COIN_BACK_SILHOUETTE_AG =
{
	{
		// class allocator
		__TYPE(Coin),

		// sprites
		(SpriteROMDef**)COIN_BACK_SILHOUETTE_SPRITES,

		// collision shapes
		(ShapeDefinition*)COIN_BACK_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kCoin,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&COIN_ANIM,

	// initial animation
	"Spin",
};


