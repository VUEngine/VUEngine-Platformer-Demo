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
#include <AnimatedInGameEntity.h>
#include <BgmapAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE WaterfallStream2x16Tiles[];
extern BYTE WaterfallStream2x16Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef WATERFALL_STREAM_2x16_DEFAULT_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0, 1, 2, 3},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

// an animation definition
AnimationDescriptionROMDef WATERFALL_STREAM_2x16_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&WATERFALL_STREAM_2x16_DEFAULT_ANIM,
		NULL,
	}
};

CharSetROMDef WATERFALL_STREAM_2x16_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	32 * 4,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	WaterfallStream2x16Tiles,
};

TextureROMDef WATERFALL_STREAM_2x16_TX =
{
	// charset definition
	(CharSetDefinition*)&WATERFALL_STREAM_2x16_CH,

	// bgmap definition
	WaterfallStream2x16Map,

	// cols (max 64)
	2,

	// rows (max 64)
	16,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	4,

	// palette number (0-3)
	0,
};

BgmapSpriteROMDef WATERFALL_STREAM_2x16_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&WATERFALL_STREAM_2x16_TX,

		// transparent
		true,

		// displacement
		{
			0,
			0,
			FTOFIX19_13(-1),
			0
		},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const WATERFALL_STREAM_2x16_SPRITES[] =
{
	&WATERFALL_STREAM_2x16_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef WATERFALL_STREAM_2x16_AG =
{
	{
		{
			__TYPE(AnimatedInGameEntity),
			(SpriteROMDef**)WATERFALL_STREAM_2x16_SPRITES,
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
	(AnimationDescription*)&WATERFALL_STREAM_2x16_ANIM,

	// initial animation
	"Default",
};