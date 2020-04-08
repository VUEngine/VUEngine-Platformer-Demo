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

#include <Libgccvb.h>
#include <BgmapAnimatedSprite.h>
#include <Box.h>
#include "Door.h"
#include "LayerSwitchDoor.h"
#include "GoalDoor.h"
#include "KeyDoor.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE DoorTiles[];
extern BYTE DoorMap[];
extern BYTE DoorBackTiles[];
extern BYTE DoorBackMap[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMSpec DOOR_OPENING_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{0, 1, 2, 3},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Opening",
};

// a function which defines the frames to play
AnimationFunctionROMSpec DOOR_CLOSING_ANIM =
{
	// number of frames of this animation function
	4,

	// frames to play in animation
	{3, 2, 1, 0},

	// number of cycles a frame of animation is displayed
	4,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closing",
};

// a function which defines the frames to play
AnimationFunctionROMSpec DOOR_OPEN_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{3},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Open",
};

// a function which defines the frames to play
AnimationFunctionROMSpec DOOR_CLOSED_ANIM =
{
	// number of frames of this animation function
	1,

	// frames to play in animation
	{4},

	// number of cycles a frame of animation is displayed
	0,

	// whether to play it in loop or not
	false,

	// method to call on function completion
	NULL,

	// function's name
	"Closed",
};

// a function which defines the frames to play
AnimationFunctionROMSpec DOOR_KEY_ANIM =
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
	"Key",
};

// a function which defines the frames to play
AnimationFunctionROMSpec DOOR_GOAL_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{5, 6},

	// number of cycles a frame of animation is displayed
	8,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Goal",
};

// an animation spec
AnimationDescriptionROMSpec DOOR_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&DOOR_OPENING_ANIM,
		(AnimationFunction*)&DOOR_CLOSING_ANIM,
		(AnimationFunction*)&DOOR_OPEN_ANIM,
		(AnimationFunction*)&DOOR_CLOSED_ANIM,
		(AnimationFunction*)&DOOR_KEY_ANIM,
		(AnimationFunction*)&DOOR_GOAL_ANIM,
		NULL,
	}
};

CharSetROMSpec DOOR_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	85,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char spec
	DoorTiles,
};

TextureROMSpec DOOR_TX =
{
	// charset spec
	(CharSetSpec*)&DOOR_CH,

	// bgmap spec
	DoorMap,

	// cols (max 64)
	3,

	// rows (max 64)
	4,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	7,

	// palette number (0-3)
	1,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec DOOR_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&DOOR_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, DOORS_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const DOOR_SPRITES[] =
{
	&DOOR_SPRITE,
	NULL
};

ShapeROMSpec DOOR_AG_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{19, 28, 32},

		// displacement (x, y, z, p)
		{0, 0, -16, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerSolid,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

DoorROMSpec DOOR_AG =
{
	{
		// class allocator
		__TYPE(Door),

		// behaviors
		NULL,

		// sprites
		(SpriteSpec**)DOOR_SPRITES,

		// collision shapes
		(ShapeSpec*)DOOR_AG_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeDoor,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

LayerSwitchDoorROMSpec LAYER_SWITCH_DOOR_AG =
{
	{
		// class allocator
		__TYPE(LayerSwitchDoor),

		// behaviors
		NULL,

		// sprites
		(SpriteSpec**)DOOR_SPRITES,

		// collision shapes
		(ShapeSpec*)DOOR_AG_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeDoor,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};


GoalDoorROMSpec GOAL_DOOR_AG =
{
	{
		// class allocator
		__TYPE(GoalDoor),

		// behaviors
		NULL,

		// sprites
		(SpriteSpec**)DOOR_SPRITES,

		// collision shapes
		(ShapeSpec*)DOOR_AG_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeDoor,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Open",
};

KeyDoorROMSpec KEY_DOOR_AG =
{
	{
		// class allocator
		__TYPE(KeyDoor),

		// behaviors
		NULL,

		// sprites
		(SpriteSpec**)DOOR_SPRITES,

		// collision shapes
		(ShapeSpec*)DOOR_AG_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeDoor,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

BgmapSpriteROMSpec AFFINE_DOOR_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&DOOR_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, DOORS_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_AFFINE,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const AFFINE_DOOR_SPRITES[] =
{
	&AFFINE_DOOR_SPRITE,
	NULL
};

DoorROMSpec AFFINE_DOOR_AG =
{
	{
		// class allocator
		__TYPE(Door),

		// behaviors
		NULL,

		// sprites
		(SpriteSpec**)AFFINE_DOOR_SPRITES,

		// collision shapes
		(ShapeSpec*)DOOR_AG_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeDoor,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

CharSetROMSpec DOOR_BACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	25,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char spec
	DoorBackTiles,
};

TextureROMSpec DOOR_BACK_TX =
{
	// charset spec
	(CharSetSpec*)&DOOR_BACK_CH,

	// bgmap spec
	DoorBackMap,

	// cols (max 64)
	2,

	// rows (max 64)
	3,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	7,

	// palette number (0-3)
	2,

	// recyclable
	false,

	// vertical flip
	false,

	// horizontal flip
	false,
};

BgmapSpriteROMSpec DOOR_BACK_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture spec
		(TextureSpec*)&DOOR_BACK_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, ENEMIES_PARALLAX_DISPLACEMENT},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const DOOR_BACK_SPRITES[] =
{
	&DOOR_BACK_SPRITE,
	NULL
};

DoorROMSpec DOOR_BACK_AG =
{
	{
		// class allocator
		__TYPE(Door),

		// behaviors
		NULL,

		// sprites
		(SpriteSpec**)DOOR_BACK_SPRITES,

		// collision shapes
		(ShapeSpec*)DOOR_AG_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeDoor,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

LayerSwitchDoorROMSpec LAYER_SWITCH_DOOR_BACK_AG =
{
	{
		// class allocator
		__TYPE(LayerSwitchDoor),

		// behaviors
		NULL,

		// sprites
		(SpriteSpec**)DOOR_BACK_SPRITES,

		// collision shapes
		(ShapeSpec*)DOOR_AG_SHAPES,

		// size
		// if 0, width and height will be inferred from the first sprite's texture's size
		{0, 0, 0},

		// gameworld's character's type
		kTypeDoor,

		// physical specification
		(PhysicalSpecification*)NULL,
	},

	// pointer to the animation spec for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Open",
};
