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

#include <RecyclableImage.h>
#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE Level_1_Tower_MainTiles[];
extern BYTE Level_1_Tower_Main_2Map[];

extern BgmapSpriteROMDef LEVEL_1_TOWER_MAIN_BACK_2_IM_SPRITE;
extern CharSetROMDef LEVEL_1_TOWER_MAIN_CH;


//---------------------------------------------------------------------------------------------------------
//												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

TextureROMDef LEVEL_1_TOWER_MAIN_2_TX =
{
	// charset definition
	(CharSetDefinition*)&LEVEL_1_TOWER_MAIN_CH,

	// bgmap definition
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
};

TextureROMDef* const LEVEL_1_TOWER_MAIN_2_IM_TEXTURES[] =
{
	(TextureDefinition*)&LEVEL_1_TOWER_MAIN_2_TX,
	NULL
};

MBgmapSpriteROMDef LEVEL_1_TOWER_MAIN_2_IM_SPRITE =
{
	{
		{
			// sprite's type
			__TYPE(MBgmapSprite),

			// texture definition
			NULL,

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
	},

	(TextureDefinition**)LEVEL_1_TOWER_MAIN_2_IM_TEXTURES,

	// SCX/SCY
	__WORLD_1x1,

	// x loop
	false,

	// y loop
	false,
};

BgmapSpriteROMDef* const LEVEL_1_TOWER_MAIN_2_IM_SPRITES[] =
{
	(BgmapSpriteROMDef*)&LEVEL_1_TOWER_MAIN_BACK_2_IM_SPRITE,
	(BgmapSpriteROMDef*)&LEVEL_1_TOWER_MAIN_2_IM_SPRITE,
	NULL
};

RecyclableImageROMDef LEVEL_1_TOWER_MAIN_2_IM =
{
	__TYPE(RecyclableImage),
	(SpriteROMDef**)LEVEL_1_TOWER_MAIN_2_IM_SPRITES,
};
