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
#include <BgmapAnimatedSprite.h>
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
AnimationFunctionROMDef DOOR_OPENING_ANIM =
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
AnimationFunctionROMDef DOOR_CLOSING_ANIM =
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
AnimationFunctionROMDef DOOR_OPEN_ANIM =
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
AnimationFunctionROMDef DOOR_CLOSED_ANIM =
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
AnimationFunctionROMDef DOOR_KEY_ANIM =
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
AnimationFunctionROMDef DOOR_GOAL_ANIM =
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

// an animation definition
AnimationDescriptionROMDef DOOR_ANIM =
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

CharSetROMDef DOOR_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	85,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	DoorTiles,
};

TextureROMDef DOOR_TX =
{
	// charset definition
	(CharSetDefinition*)&DOOR_CH,

	// bgmap definition
	DoorMap,

	// cols (max 64)
	3,

	// rows (max 64)
	4,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	7,

	// palette number (0-3)
	1,
};

BgmapSpriteROMDef DOOR_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&DOOR_TX,

		// transparent
		false,

		// displacement
		{0, 0, FTOFIX19_13(2), 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const DOOR_SPRITES[] =
{
	&DOOR_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef DOOR_AG =
{
	{
		{
			__TYPE(Door),
			(SpriteROMDef**)DOOR_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{6, 0, 6, 6},

		// in game type
		kDoor,

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
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

AnimatedInGameEntityROMDef LAYER_SWITCH_DOOR_AG =
{
	{
		{
			__TYPE(LayerSwitchDoor),
			(SpriteROMDef**)DOOR_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{6, 0, 6, 6},

		// in game type
		kDoor,

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
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

AnimatedInGameEntityROMDef GOAL_DOOR_AG =
{
	{
		{
			__TYPE(GoalDoor),
			(SpriteROMDef**)DOOR_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{1, 0, 1, 1},

		// in game type
		kDoor,

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
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Open",
};

AnimatedInGameEntityROMDef KEY_DOOR_AG =
{
	{
		{
			__TYPE(KeyDoor),
			(SpriteROMDef**)DOOR_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{6, 0, 6, 6},

		// in game type
		kDoor,

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
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

BgmapSpriteROMDef AFFINE_DOOR_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&DOOR_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_OBJ,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const AFFINE_DOOR_SPRITES[] =
{
	&AFFINE_DOOR_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef AFFINE_DOOR_AG =
{
	{
		{
			__TYPE(Door),
			(SpriteROMDef**)AFFINE_DOOR_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{6, 0, 6, 6},

		// in game type
		kDoor,

		// width
		// if 0, width and height will be inferred from the texture's size
		0,

		// height
		// if 0, width and height will be inferred from the texture's size
		0,

		// depth
		4,
	},

	// pointer to the animation definition for the item
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

CharSetROMDef DOOR_BACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	25,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__ANIMATED_MULTI,

	// char definition
	DoorBackTiles,
};

TextureROMDef DOOR_BACK_TX =
{
	// charset definition
	(CharSetDefinition*)&DOOR_BACK_CH,

	// bgmap definition
	DoorBackMap,

	// cols (max 64)
	2,

	// rows (max 64)
	3,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	7,

	// palette number (0-3)
	2,
};

BgmapSpriteROMDef DOOR_BACK_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapAnimatedSprite),

		// texture definition
		(TextureDefinition*)&DOOR_BACK_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const DOOR_BACK_SPRITES[] =
{
	&DOOR_BACK_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef DOOR_BACK_AG =
{
	{
		{
			__TYPE(Door),
			(SpriteROMDef**)DOOR_BACK_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{5, 0, 2, 3},

		// in game type
		kDoor,

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
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Closed",
};

AnimatedInGameEntityROMDef LAYER_SWITCH_DOOR_BACK_AG =
{
	{
		{
			__TYPE(LayerSwitchDoor),
			(SpriteROMDef**)DOOR_BACK_SPRITES,
		},

		// collision detection gap (up, down, left, right)
		{5, 0, 2, 3},

		// in game type
		kDoor,

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
	(AnimationDescription*)&DOOR_ANIM,

	// initial animation
	"Open",
};
