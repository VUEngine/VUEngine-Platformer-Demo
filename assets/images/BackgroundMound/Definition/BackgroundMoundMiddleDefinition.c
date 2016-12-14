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

#include <Clouds.h>
#include <Image.h>
#include <MBgmapSprite.h>
#include <InanimatedInGameEntity.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE BackgroundMoundMiddleTiles[];
extern BYTE BackgroundMoundMiddleMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef MOUND_BG_MIDDLE_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    81,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    BackgroundMoundMiddleTiles,
};

TextureROMDef MOUND_BG_MIDDLE_TX =
{
    // charset definition
    (CharSetDefinition*)&MOUND_BG_MIDDLE_CH,

    // bgmap definition
    BackgroundMoundMiddleMap,

    // cols (max 64)
    64,

    // rows (max 64)
    4,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0,
};

TextureROMDef* const MOUND_BG_MIDDLE_SB_TEXTURES[] =
{
	(TextureDefinition*)&MOUND_BG_MIDDLE_TX,
	NULL
};

MBgmapSpriteROMDef MOUND_BG_MIDDLE_SB_SPRITE =
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
            {0, 0, 0},
        },

		// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
		__WORLD_BGMAP,

		// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
		__WORLD_ON,
	},

	(TextureDefinition**)MOUND_BG_MIDDLE_SB_TEXTURES,

	// SCX/SCY
	__WORLD_1x1,

	// x loop
	true,

	// y loop
	false,
};

BgmapSpriteROMDef* const MOUND_BG_MIDDLE_SB_SPRITES[] =
{
	(BgmapSpriteROMDef*)&MOUND_BG_MIDDLE_SB_SPRITE,
	NULL
};

ImageROMDef MOUND_BG_MIDDLE_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)MOUND_BG_MIDDLE_SB_SPRITES,
};

CloudsROMDef CLOUDS_IM =
{
	{
		__TYPE(Clouds),
		(SpriteROMDef**)MOUND_BG_MIDDLE_SB_SPRITES,
	},

	// displacement per cycle
	ITOFIX19_13(150),
};
