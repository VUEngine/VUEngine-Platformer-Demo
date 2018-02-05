/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include <AnimatedEntity.h>
#include <BgmapAnimatedSprite.h>
#include <libgccvb.h>
#include <Hint.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE HintTiles[];
extern BYTE HintMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef HINT_OPEN_ANIM =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{0, 1, 2, 3, 4},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hint_onHintOpened,

	// function's name
	"Open",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_CLOSE_ANIM =
{
	// number of frames of this animation function
	5,

	// frames to play in animation
	{4, 3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	(EventListener)&Hint_onCloseDone,

	// function's name
	"Close",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_CLOSED_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{0},

	// number of cycles a frame of animation is displayed
	2,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closed",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_ENGLISH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{5, 6},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterEnglish",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_DEUTSCH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{7, 8},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterDeutsch",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_ESPANOL_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{9, 10},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterEspanol",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_ENTER_FRANCAIS_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{11, 12},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"EnterFrancais",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_ENGLISH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{13, 14},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpEnglish",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_DEUTSCH_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{15, 16},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpDeutsch",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_ESPANOL_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{17, 18},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpEspanol",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_PICK_UP_FRANCAIS_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{19, 20},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"PickUpFrancais",
};

// a function which defines the frames to play
AnimationFunctionROMDef HINT_KEY_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{21, 22},

	// number of cycles a frame of animation is displayed
	14,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Key",
};

// an animation definition
AnimationDescriptionROMDef HINT_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&HINT_OPEN_ANIM,
		(AnimationFunction*)&HINT_CLOSE_ANIM,
		(AnimationFunction*)&HINT_CLOSED_ANIM,
		(AnimationFunction*)&HINT_ENTER_ENGLISH_ANIM,
		(AnimationFunction*)&HINT_ENTER_DEUTSCH_ANIM,
		(AnimationFunction*)&HINT_ENTER_ESPANOL_ANIM,
		(AnimationFunction*)&HINT_ENTER_FRANCAIS_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_ENGLISH_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_DEUTSCH_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_ESPANOL_ANIM,
		(AnimationFunction*)&HINT_PICK_UP_FRANCAIS_ANIM,
		(AnimationFunction*)&HINT_KEY_ANIM,
		NULL,
	}
};

CharSetROMDef HINT_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	24,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_SINGLE,

	// char definition
	HintTiles,
};

TextureROMDef HINT_TX =
{
	// charset definition
	(CharSetDefinition*)&HINT_CH,

	// bgmap definition
	HintMap,

	// cols (max 64)
	8,

	// rows (max 64)
	3,

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

BgmapSpriteROMDef HINT_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&HINT_TX,

		// transparent
		false,

		// displacement
		{28, -21, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const HINT_SPRITES[] =
{
	&HINT_SPRITE,
	NULL
};

AnimatedEntityROMDef HINT_MC =
{
	{
		// class allocator
		__TYPE(Hint),

		// sprites
		(SpriteROMDef**)HINT_SPRITES,

		// collision shapes
		(ShapeDefinition*)NULL,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kNotShape,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&HINT_ANIM,

	// initial animation
	"Closed",
};

