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
#include <AnimatedInGameEntity.h>
#include <BgmapAnimatedSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE FlowerATiles[];
extern BYTE FlowerAMap[];


//---------------------------------------------------------------------------------------------------------
//												ANIMATION DEFINITION
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef FLOWER_A_DEFAULT_ANIM =
{
	// number of frames of this animation function
	2,

	// frames to play in animation
	{0, 1},

	// number of cycles a frame of animation is displayed
	16,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

// an animation definition
AnimationDescriptionROMDef FLOWER_A_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&FLOWER_A_DEFAULT_ANIM,
		NULL,
	}
};


//---------------------------------------------------------------------------------------------------------
// 											SPRITE DEFINITION
//---------------------------------------------------------------------------------------------------------

CharSetROMDef FLOWER_A_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    2,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __ANIMATED_SHARED,

    // char definition
    FlowerATiles,
};

TextureROMDef FLOWER_A_TX =
{
    // charset definition
    (CharSetDefinition*)&FLOWER_A_CH,

    // bgmap definition
    FlowerAMap,

    // cols (max 64)
    2,

    // rows (max 64)
    1,

        // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
        // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
        // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0
};

BgmapSpriteROMDef FLOWER_A_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapAnimatedSprite),

        // texture definition
        (TextureDefinition*)&FLOWER_A_TX,

        // transparent
		false,

		// displacement
        {FTOFIX19_13(0), FTOFIX19_13(0), FTOFIX19_13(0), 0},
    },

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const FLOWER_A_SPRITES[] =
{
	&FLOWER_A_SPRITE,
	NULL
};


//---------------------------------------------------------------------------------------------------------
// 											ENTITY DEFINITION
//---------------------------------------------------------------------------------------------------------

AnimatedInGameEntityROMDef FLOWER_A_AG =
{
    {
        {
            __TYPE(AnimatedInGameEntity),
            (SpriteROMDef**)FLOWER_A_SPRITES,
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
        8
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&FLOWER_A_ANIM,

    // initial animation
    "Default",
};
