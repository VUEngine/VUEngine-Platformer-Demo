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
#include <AnimatedInGameEntity.h>
#include <BgmapAnimatedSprite.h>
#include <GUI.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE GUITiles[];
extern BYTE GUIBandanaTiles[];
extern BYTE GUIMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// a function which defines the frames to play
AnimationFunctionROMDef GUI_DEFAULT_ANIM =
{
	// number of frames of this animation function
	15,

	// frames to play in animation
	{1,0,1,0,1,0,1,0,1,0,1,0,2,3,4},

	// number of cycles a frame of animation is displayed
	8 * __FPS_ANIM_FACTOR,

	// whether to play it in loop or not
	true,

	// method to call on function completion
	NULL,

	// function's name
	"Default",
};

// an animation definition
AnimationDescriptionROMDef GUI_ANIM =
{
	// animation functions
	{
		(AnimationFunction*)&GUI_DEFAULT_ANIM,
		NULL,
	}
};

CharSetROMDef GUI_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    96,

    // allocation type
    __ANIMATED_SINGLE,

    // char definition
    GUITiles,
};

CharSetROMDef GUI_BANDANA_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    96,

    // allocation type
    __ANIMATED_SINGLE,

    // char definition
    GUIBandanaTiles,
};

TextureROMDef GUI_TX =
{
    {
        // number of chars, depending on allocation type:
        // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
        // __ANIMATED_MULTI: sum of chars of all animation frames
        // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
        // __NOT_ANIMATED: number of chars of whole image
        96,

        // allocation type
        __ANIMATED_SINGLE,

        // char definition
        GUITiles,
    },

    // bgmap definition
    GUIMap,

    // cols (max 64)
    48,

    // rows (max 64)
    2,

    // number of frames
    5,

    // palette number
    1,
};

BgmapSpriteROMDef GUI_SPRITE =
{
	// sprite's type
	__TYPE(BgmapAnimatedSprite),

	// texture definition
	(TextureDefinition*)&GUI_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_HBIAS OR WRLD_OBJ)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const GUI_SPRITES[] =
{
	&GUI_SPRITE,
	NULL
};

AnimatedInGameEntityROMDef GUI_AG =
{
    {
        {
            __TYPE(GUI),
            (SpriteROMDef**)GUI_SPRITES,
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
        1
    },

    // pointer to the animation definition for the item
    (AnimationDescription*)&GUI_ANIM,

    // initial animation
    "Default",
};