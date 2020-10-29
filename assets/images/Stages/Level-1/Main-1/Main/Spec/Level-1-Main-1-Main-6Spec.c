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

#include <Entity.h>
#include <MBgmapSprite.h>
#include <macros.h>

//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_Main_1_Main_6Map[];

extern CharSetROMSpec LEVEL_1_MAIN_1_MAIN_CH;

extern BgmapSpriteROMSpec LEVEL_1_MAIN_1_MAIN_BACK_6_IM_SPRITE;
extern BgmapSpriteROMSpec LEVEL_1_MAIN_1_MAIN_FRONT_6_IM_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMSpec LEVEL_1_MAIN_1_MAIN_6_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_MAIN_1_MAIN_CH,

	// bgmap spec
	Level_1_Main_1_Main_6Map,

	// cols (max 64)
	64,

	// rows (max 64)
	34,

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

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec* const LEVEL_1_MAIN_1_MAIN_6_IM_TEXTURES[] =
{
	(TextureSpec*)&LEVEL_1_MAIN_1_MAIN_6_TX,
	NULL
};

BgmapSpriteROMSpec LEVEL_1_MAIN_1_MAIN_6_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LEVEL_1_MAIN_1_MAIN_6_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const LEVEL_1_MAIN_1_MAIN_6_IM_SPRITES[] =
{
	(BgmapSpriteROMSpec*)&LEVEL_1_MAIN_1_MAIN_6_IM_SPRITE,
	(BgmapSpriteROMSpec*)&LEVEL_1_MAIN_1_MAIN_BACK_6_IM_SPRITE,
	(BgmapSpriteROMSpec*)&LEVEL_1_MAIN_1_MAIN_FRONT_6_IM_SPRITE,
	NULL
};

EntityROMSpec LEVEL_1_MAIN_1_MAIN_6_IM =
{
	// class allocator
	__TYPE(Entity),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)LEVEL_1_MAIN_1_MAIN_6_IM_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNoShape,

	// physical specification
	(PhysicalSpecification*)NULL,
};
