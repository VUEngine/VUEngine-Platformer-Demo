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


//---------------------------------------------------------------------------------------------------------
// 												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern BYTE VBJaEngineLogoTiles[];
extern BYTE VBJaEngineLogoMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef VBJAENGINE_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI, __NOT_ANIMATED: sum of all chars
    56,

    // allocation type
    // (__ANIMATED_SINGLE, __ANIMATED_SHARED, __ANIMATED_SHARED_COORDINATED, __ANIMATED_MULTI or __NOT_ANIMATED)
    __NOT_ANIMATED,

    // char definition
    VBJaEngineLogoTiles,
};

TextureROMDef VBJAENGINE_TX =
{
    // charset definition
    (CharSetDefinition*)&VBJAENGINE_CH,

    // bgmap definition
    VBJaEngineLogoMap,

    // cols (max 64)
    16,

    // rows (max 64)
    4,

    // number of frames, depending on charset's allocation type:
    // __ANIMATED_SINGLE, _SHARED, _SHARED_COORDINATED, __NOT_ANIMATED: 1
    // __ANIMATED_MULTI: total number of frames
    1,

    // palette number (0-3)
    0,
};

BgmapSpriteROMDef VBJAENGINE_IM_L_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&VBJAENGINE_TX,

	// displacement
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_LON,
};

BgmapSpriteROMDef VBJAENGINE_IM_R_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&VBJAENGINE_TX,

	// displacement
	{0, 0, 0},
	
	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_RON,
};

BgmapSpriteROMDef* const VBJAENGINE_IM_SPRITES[] =
{
	&VBJAENGINE_IM_L_SPRITE,
	&VBJAENGINE_IM_R_SPRITE,
	NULL
};

ImageROMDef VBJAENGINE_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)VBJAENGINE_IM_SPRITES,
};