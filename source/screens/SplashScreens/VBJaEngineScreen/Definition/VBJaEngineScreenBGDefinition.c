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

#include <Image.h>
#include <MBgmapSprite.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE VBJaEngineScreenBGTiles[];
extern BYTE VBJaEngineScreenBGMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef VBJAENGINE_BG_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    148,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    VBJaEngineScreenBGTiles,
};

TextureROMDef VBJAENGINE_BG_TX =
{
    // charset definition
    (CharSetDefinition*)&VBJAENGINE_BG_CH,

    // bgmap definition
    VBJaEngineScreenBGMap,

    // cols (max 64)
    64,

    // rows (max 64)
    28,

    // padding for affine transformations
	{0, 0},

	// number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0,
};

TextureROMDef* const VBJAENGINE_BG_IM_SPRITE_TEXTURES[] =
{
	(TextureDefinition*)&VBJAENGINE_BG_TX,
	NULL
};

MBgmapSpriteROMDef VBJAENGINE_BG_IM_SPRITE =
{
	{
        {
            // sprite's type
            __TYPE(MBgmapSprite),

            // texture definition
            NULL,

            // displacement
            {0, 0, 0},
        },

		// bgmap mode (__WORLD_BGMAP, __WORLD_AFFINE, __WORLD_OBJ or __WORLD_HBIAS)
		__WORLD_BGMAP,

		// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
		__WORLD_ON,
	},

	(TextureDefinition**)VBJAENGINE_BG_IM_SPRITE_TEXTURES,

	// SCX/SCY
	__WORLD_1x1,

	// x loop
	true,

	// y loop
	false,
};

BgmapSpriteROMDef* const VBJAENGINE_BG_IM_SPRITES[] =
{
	(BgmapSpriteROMDef*)&VBJAENGINE_BG_IM_SPRITE,
	NULL
};

ImageROMDef VBJAENGINE_BG_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)VBJAENGINE_BG_IM_SPRITES,
};

