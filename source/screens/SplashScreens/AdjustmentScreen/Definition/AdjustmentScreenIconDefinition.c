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

extern BYTE AdjustmentScreenIconTiles[];
extern BYTE AdjustmentScreenIconMap[];


//---------------------------------------------------------------------------------------------------------
// 												DEFINITIONS
//---------------------------------------------------------------------------------------------------------

CharSetROMDef ADJUSTMENT_SCREEN_ICON_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows of this texture)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows of this texture)
    // __NOT_ANIMATED: number of chars of whole image
    5,

    // allocation type
    __NOT_ANIMATED,

    // char definition
    AdjustmentScreenIconTiles,
};

TextureROMDef ADJUSTMENT_SCREEN_ICON_TX =
{
    // charset definition
    (CharSetDefinition*)&ADJUSTMENT_SCREEN_ICON_CH,

    // bgmap definition
    AdjustmentScreenIconMap,

    // cols (max 64)
    2,

    // rows (max 64)
    2,

    // number of frames
    1,

    // palette number
    0,
};

BgmapSpriteROMDef ADJUSTMENT_SCREEN_ICON_IM_L_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)& ADJUSTMENT_SCREEN_ICON_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_LON,
};

BgmapSpriteROMDef* const ADJUSTMENT_SCREEN_ICON_IM_L_SPRITES[] =
{
	& ADJUSTMENT_SCREEN_ICON_IM_L_SPRITE,
	NULL
};

BgmapSpriteROMDef const ADJUSTMENT_SCREEN_ICON_IM_R_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)& ADJUSTMENT_SCREEN_ICON_TX,

	// displacement (x, y, z) (in pixels)
	{0, 0, 0},

	// bgmap mode (WRLD_BGMAP, WRLD_AFFINE, WRLD_OBJ or WRLD_HBIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_RON,
};

BgmapSpriteROMDef* ADJUSTMENT_SCREEN_ICON_IM_R_SPRITES[] =
{
	& ADJUSTMENT_SCREEN_ICON_IM_R_SPRITE,
	NULL

};

ImageROMDef ADJUSTMENT_SCREEN_ICON_IM_L =
{
	__TYPE(Image),
	(SpriteROMDef**) ADJUSTMENT_SCREEN_ICON_IM_L_SPRITES,
};

ImageROMDef ADJUSTMENT_SCREEN_ICON_IM_R =
{
	__TYPE(Image),
	(SpriteROMDef**) ADJUSTMENT_SCREEN_ICON_IM_R_SPRITES,
};