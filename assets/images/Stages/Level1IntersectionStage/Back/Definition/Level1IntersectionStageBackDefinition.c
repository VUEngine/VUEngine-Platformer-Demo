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

#include <StaticImage.h>
#include <BgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level1IntersectionStageBackTiles[];
extern BYTE Level1IntersectionStageBack1Map[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef LEVEL1_INTERSECTION_STAGE_BACK_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	42,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char definition
	Level1IntersectionStageBackTiles,
};

TextureROMDef LEVEL1_INTERSECTION_STAGE_BACK_1_TX =
{
	// charset definition
	(CharSetDefinition*)&LEVEL1_INTERSECTION_STAGE_BACK_CH,

	// bgmap definition
	Level1IntersectionStageBack1Map,

	// cols (max 64)
	48,

	// rows (max 64)
	24,

	// padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	0,
};

BgmapSpriteROMDef LEVEL1_INTERSECTION_STAGE_BACK_1_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture definition
		(TextureDefinition*)&LEVEL1_INTERSECTION_STAGE_BACK_1_TX,

		// transparent
		false,

		// displacement
		{
			FTOFIX19_13(0), // x
			FTOFIX19_13(0), // y
			FTOFIX19_13(2), // z
			FTOFIX19_13(0), // parallax
		},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const LEVEL1_INTERSECTION_STAGE_BACK_1_IM_SPRITES[] =
{
	&LEVEL1_INTERSECTION_STAGE_BACK_1_IM_SPRITE,
	NULL
};

StaticImageROMDef LEVEL1_INTERSECTION_STAGE_BACK_1_IM =
{
	__TYPE(StaticImage),
	(SpriteROMDef**)LEVEL1_INTERSECTION_STAGE_BACK_1_IM_SPRITES,
};

