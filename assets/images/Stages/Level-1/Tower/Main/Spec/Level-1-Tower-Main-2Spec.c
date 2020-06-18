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
#include <HbiasMaskMBgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_Tower_MainTiles[];
extern BYTE Level_1_Tower_Main_2Map[];

extern BgmapSpriteROMSpec LEVEL_1_TOWER_MAIN_BACK_2_IM_SPRITE;
extern CharSetROMSpec LEVEL_1_TOWER_MAIN_CH;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMSpec LEVEL_1_TOWER_MAIN_2_TX =
{
	// charset spec
	(CharSetSpec*)&LEVEL_1_TOWER_MAIN_CH,

	// bgmap spec
	Level_1_Tower_Main_2Map,

	// cols (max 64)
	48,

	// rows (max 64)
	64,

	// padding for affine/hbias transformations (cols, rows)
	{0, 0},

	// number of frames, depending on charset's allocation type:
	// __ANIMATED_SINGLE*, __ANIMATED_SHARED*, __NOT_ANIMATED: 1
	// __ANIMATED_MULTI: total number of frames
	1,

	// palette number (0-3)
	0,

	// recyclable
	true,

	// vertical flip
	false,

	// horizontal flip
	false,
};

TextureROMSpec* const LEVEL_1_TOWER_MAIN_2_IM_TEXTURES[] =
{
	(TextureSpec*)&LEVEL_1_TOWER_MAIN_2_TX,
	NULL
};

MBgmapSpriteROMSpec LEVEL_1_TOWER_MAIN_2_IM_SPRITE =
{
	{
		{
			// sprite's type
			__TYPE(MBgmapSprite),

			// texture spec
			NULL,

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
	},

	(TextureSpec**)LEVEL_1_TOWER_MAIN_2_IM_TEXTURES,

	// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
	// textures must be 64x64 for anything other than 1x1
	__WORLD_1x1,

	// x loop
	false,

	// y loop
	false,

	/// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
	0,

	/// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
	0,
};

HbiasMaskMBgmapSpriteROMSpec LEVEL_1_TOWER_MAIN_2_HOT_AIR_IM_SPRITE =
{
	{
		{
			{
				// sprite's type
				__TYPE(HbiasMaskMBgmapSprite),

				// texture spec
				NULL,

				// transparent (__TRANSPARENCY_NONE, __TRANSPARENCY_EVEN or __TRANSPARENCY_ODD)
				__TRANSPARENCY_NONE,

				// displacement
				{0, 0, -2, 0},
			},

			// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJECT or __WORLD_HBIAS)
			// make sure to use the proper corresponding sprite type throughout the spec (BgmapSprite or ObjectSprite)
			__WORLD_HBIAS,

			// pointer to affine/hbias manipulation function
			(ParamTableEffectMethod)HbiasMaskMBgmapSprite_wave,

			// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
			__WORLD_ON,
		},

		(TextureSpec**)LEVEL_1_TOWER_MAIN_2_IM_TEXTURES,

		// SCX/SCY (__WORLD_1x1, 1x2, 1x4, 1x8, 2x1, 2x2, 2x4, 4x1, 4x2, or 8x1)
		// textures must be 64x64 for anything other than 1x1
		__WORLD_1x1,

		// x loop
		false,

		// y loop
		false,

		// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
		0,

		// Bounds the sprite's size to provide culling; if 0, the value is inferred from the texture
		0
	},

	// name of the owner of the reference sprite
	"Main_2",

	// height of the effect
	50,

	// height addition
	0
};

BgmapSpriteROMSpec* const LEVEL_1_TOWER_MAIN_2_IM_SPRITES[] =
{
	(BgmapSpriteROMSpec*)&LEVEL_1_TOWER_MAIN_2_IM_SPRITE,
	(BgmapSpriteROMSpec*)&LEVEL_1_TOWER_MAIN_BACK_2_IM_SPRITE,
	NULL
};

EntityROMSpec LEVEL_1_TOWER_MAIN_2_IM =
{
	// class allocator
	__TYPE(Entity),

	// behaviors
	NULL,

	// sprites
	(SpriteSpec**)LEVEL_1_TOWER_MAIN_2_IM_SPRITES,

	// use z displacement in projection
	false,

	// collision shapes
	(ShapeSpec*)NULL,

	// size
	// if 0, width and height will be inferred from the first sprite's texture's size
	{0, 0, 0},

	// gameworld's character's type
	kTypeNone,

	// physical specification
	(PhysicalSpecification*)NULL,
};
