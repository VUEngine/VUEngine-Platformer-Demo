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
#include <BgmapSprite.h>
#include <macros.h>


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE VBJaEngineScreenLogoTiles[];
extern BYTE VBJaEngineScreenLogoMap[];
extern BYTE VBJaEngineScreenLogoOutlineTiles[];
extern BYTE VBJaEngineScreenLogoOutlineMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef VBJAENGINE_LOGO_3D_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    49,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    VBJaEngineScreenLogoTiles,
};

TextureROMDef VBJAENGINE_LOGO_3D_TX =
{
    // charset definition
    (CharSetDefinition*)&VBJAENGINE_LOGO_3D_CH,

    // bgmap definition
    VBJaEngineScreenLogoMap,

    // cols (max 64)
    8,

    // rows (max 64)
    9,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

   // palette number (0-3)
    0,
};

CharSetROMDef VBJAENGINE_LOGO_OUTLINE_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    80,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    VBJaEngineScreenLogoOutlineTiles,
};

TextureROMDef VBJAENGINE_LOGO_OUTLINE_TX =
{
    // charset definition
    (CharSetDefinition*)&VBJAENGINE_LOGO_OUTLINE_CH,

    // bgmap definition
    VBJaEngineScreenLogoOutlineMap,

    // cols (max 64)
    18,

    // rows (max 64)
    9,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    1,
};

BgmapSpriteROMDef VBJAENGINE_LOGO_3D_IM_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&VBJAENGINE_LOGO_3D_TX,

        // displacement
        {0, 0, FTOFIX19_13(SORT_INCREMENT)},
    },

	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef VBJAENGINE_LOGO_OUTLINE_IM_SPRITE =
{
    {
        // sprite's type
        __TYPE(BgmapSprite),

        // texture definition
        (TextureDefinition*)&VBJAENGINE_LOGO_OUTLINE_TX,

        // displacement
        {FTOFIX19_13(13), FTOFIX19_13(1), 0},
    },

	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	__WORLD_BGMAP,

	// display mode (__WORLD_ON, __WORLD_LON or __WORLD_RON)
	__WORLD_ON,
};

BgmapSpriteROMDef* const VBJAENGINE_LOGO_3D_IM_SPRITES[] =
{
	&VBJAENGINE_LOGO_OUTLINE_IM_SPRITE,
	&VBJAENGINE_LOGO_3D_IM_SPRITE,
	NULL
};

ImageROMDef VBJAENGINE_LOGO_3D_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)VBJAENGINE_LOGO_3D_IM_SPRITES,
};
