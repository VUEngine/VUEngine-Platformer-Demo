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

#include <Entity.h>
#include <MBgmapSprite.h>
#include <HbiasMaskMBgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_Main_1_BackTiles[];
extern BYTE Level_1_Main_1_Back_5Map[];


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef LEVEL_1_MAIN_1_BACK_5_CH =
{
	// number of chars, depending on allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*: number of chars of a single animation frame (cols * rows)
	// __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
	152,

	// allocation type
	// (__ANIMATED_SINGLE, __ANIMATED_SINGLE_OPTIMIZED, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
	__NOT_ANIMATED,

	// char definition
	Level_1_Main_1_BackTiles,
};

TextureROMDef LEVEL_1_MAIN_1_BACK_5_TX =
{
	// charset definition
	(CharSetDefinition*)&LEVEL_1_MAIN_1_BACK_5_CH,

	// bgmap definition
	Level_1_Main_1_Back_5Map,

	// cols (max 64)
	61,

	// rows (max 64)
	24,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	2,

	// recyclable
	false,
};

TextureROMDef* const LEVEL_1_MAIN_1_BACK_5_IM_TEXTURES[] =
{
	(TextureDefinition*)&LEVEL_1_MAIN_1_BACK_5_TX,
	NULL
};

BgmapSpriteROMDef LEVEL_1_MAIN_1_BACK_5_IM_SPRITE =
{
	{
		// sprite's type
		__TYPE(BgmapSprite),

		// texture definition
		(TextureDefinition*)&LEVEL_1_MAIN_1_BACK_5_TX,

		// transparent
		false,

		// displacement
		{0, 0, 0, 0},
	},

	// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
	// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
	__WORLD_BGMAP,

	// pointer to affine/hbias manipulation function
	NULL,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const LEVEL_1_MAIN_1_BACK_5_IM_SPRITES[] =
{
	(BgmapSpriteROMDef*)&LEVEL_1_MAIN_1_BACK_5_IM_SPRITE,
	NULL
};

EntityROMDef LEVEL_1_MAIN_1_BACK_5_IM =
{
	// class allocator
	__TYPE(Entity),

	// sprites
	(SpriteROMDef**)LEVEL_1_MAIN_1_BACK_5_IM_SPRITES,

	// collision shapes
	(ShapeDefinition*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kNoType,

	// physical specification
	(PhysicalSpecification*)NULL,
};

HbiasMaskMBgmapSpriteROMDef LEVEL_1_MAIN_1_BACK_5_HBIAS_MASK_IM =
{
	{
		{
			{
				// sprite's type
				__TYPE(HbiasMaskMBgmapSprite),

				// texture definition
				NULL,

				// transparent
				false,

				// displacement
				{0, 0, 0, __I_TO_FIX19_13(-20)},
			},

			// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
			// make sure to use the proper corresponding sprite type throughout the definition (BgmapSprite or ObjectSprite)
			__WORLD_HBIAS,

			// pointer to affine/hbias manipulation function
			(ParamTableEffectMethod)HbiasMaskMBgmapSprite_wave,

			// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
			__WORLD_ON,
		},

		(TextureDefinition**)LEVEL_1_MAIN_1_BACK_5_IM_TEXTURES,

		// SCX/SCY
		__WORLD_1x1,

		// x loop
		false,

		// y loop
		false,
	},

	// name of the owner of the reference sprite
	"PlatfBk",

	// height of the effect
	15 * 8,

	// height addition
	0
};
