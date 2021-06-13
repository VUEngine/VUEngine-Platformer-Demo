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
#include <macros.h>
#include <Lava.h>
#include <HbiasEffects.h>
#include <Box.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE LavaTiles[];
extern BYTE LavaMap[];

extern BgmapSpriteROMSpec LEVEL_1_TOWER_BACK_1_HOT_AIR_IM_SPRITE;
extern BgmapSpriteROMSpec LEVEL_1_TOWER_MAIN_1_HOT_AIR_IM_SPRITE;
extern BgmapSpriteROMSpec LEVEL_1_TOWER_MAIN_2_HOT_AIR_IM_SPRITE;
extern BgmapSpriteROMSpec LEVEL_1_TOWER_MAIN_BACK_1_HOT_AIR_IM_SPRITE;
extern BgmapSpriteROMSpec LEVEL_1_TOWER_MAIN_BACK_2_HOT_AIR_IM_SPRITE;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMSpec LAVA_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	19,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char spec
	LavaTiles,
};

TextureROMSpec LAVA_TX =
{
	// charset spec
	(CharSetSpec*)&LAVA_CH,

	// bgmap spec
	LavaMap,

	// cols (max 64)
	48,

	// rows (max 64)
	24,

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

BgmapSpriteROMSpec LAVA_BG_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture spec
		(TextureSpec*)&LAVA_TX,

		// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
		__TRANSPARENCY_NONE,

		// displacement
		{0, 0, -2, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
	__WORLD_HBIAS,

	// pointer to affine/hbias manipulation function
	(ParamTableEffectMethod)HbiasEffects_wave,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMSpec* const LAVA_BG_SPRITES[] =
{
	&LAVA_BG_SPRITE,
	&LEVEL_1_TOWER_BACK_1_HOT_AIR_IM_SPRITE,
//	&LEVEL_1_TOWER_MAIN_BACK_1_HOT_AIR_IM_SPRITE,
	&LEVEL_1_TOWER_MAIN_1_HOT_AIR_IM_SPRITE,
//	&LEVEL_1_TOWER_MAIN_BACK_2_HOT_AIR_IM_SPRITE,
	&LEVEL_1_TOWER_MAIN_2_HOT_AIR_IM_SPRITE,
	NULL
};

ShapeROMSpec LAVA_SHAPES[] =
{
	{
		// shape
		__TYPE(Box),

		// size (x, y, z)
		{48 * 8, 24 * 8, 2 * 8},

		// displacement (x, y, z, p)
		{0, 0, 0, 0},

		// rotation (x, y, z)
		{0, 0, 0},

		// scale (x, y, z)
		{__I_TO_FIX7_9(1), __I_TO_FIX7_9(1), __I_TO_FIX7_9(1)},

		/// if true this shape checks for collisions against other shapes
		false,

		/// layers in which I live
		kLayerEnemies,

		/// layers to ignore when checking for collisions
		kLayerNone,
	},

	{NULL, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}, {0, 0, 0}, false, kLayerNone, kLayerNone}
};

LavaROMSpec LAVA_EN =
{
	// class allocator
	__TYPE(Lava),

	// children
	NULL,

	// behaviors
	NULL,

	// extra
	NULL,

	// sprites
	(SpriteSpec**)LAVA_BG_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)LAVA_SHAPES,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeLava,

	// physical specification
	(PhysicalSpecification*)NULL,
};
