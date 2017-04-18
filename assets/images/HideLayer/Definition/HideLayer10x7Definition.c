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
#include <macros.h>
#include <BgmapAnimatedSprite.h>
#include <AnimatedInGameEntity.h>
#include "HideLayer.h"


//---------------------------------------------------------------------------------------------------------
//												PROTOTYPES
//---------------------------------------------------------------------------------------------------------

void HideLayer_onToTransparentAnimationComplete(HideLayer this);


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HideLayer10x7Tiles[];
extern BYTE HideLayer10x7Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

AnimationFunctionROMDef HIDE_LAYER_10x7_SOLID_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Solid",
};

AnimationFunctionROMDef HIDE_LAYER_10x7_TRANSPARENT_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{6},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Transparent",
};

AnimationFunctionROMDef HIDE_LAYER_10x7_TO_SOLID_ANIM =
{
	// number of frames of this animation function
	7,

	// frames to play in animation
	{6, 5, 4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"ToSolid",
};

AnimationFunctionROMDef HIDE_LAYER_10x7_TO_TRANSPARENT_ANIM =
{
	// number of frames of this animation function
	7,

	// frames to play in animation
	{0, 1, 2, 3, 4, 5, 6},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&HideLayer_onToTransparentAnimationComplete,

	// function's name
	"ToTransparent",
};

// an animation definition
AnimationDescriptionROMDef HIDE_LAYER_10x7_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HIDE_LAYER_10x7_SOLID_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TRANSPARENT_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TO_SOLID_ANIM,
		(AnimationFunction*)&HIDE_LAYER_10x7_TO_TRANSPARENT_ANIM,
		NULL,
	}
};

CharSetROMDef HIDE_LAYER_10x7_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	70,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	HideLayer10x7Tiles,
};

TextureROMDef HIDE_LAYER_10x7_TX =
{
	// charset definition
	(CharSetDefinition*)&HIDE_LAYER_10x7_CH,

	// bgmap definition
	HideLayer10x7Map,

	// cols (max 64)
	10,

	// rows (max 64)
	7,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	1,
};

BgmapSpriteROMDef HIDE_LAYER_10x7_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&HIDE_LAYER_10x7_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine / hbias manipulation function
	// void (*)(BgmapSprite);
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const HIDE_LAYER_10x7_SPRITES[] =
{
	&HIDE_LAYER_10x7_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef HIDE_LAYER_10x7_AG =
{
	{
		{
			__TYPE(HideLayer),
			(SpriteROMDef**)HIDE_LAYER_10x7_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{8, 8, 8, 8},

		// in game type
		kHideLayer,

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
	(AnimationDescription*)&HIDE_LAYER_10x7_ANIM,

	// initial animation
	"Solid",
};

