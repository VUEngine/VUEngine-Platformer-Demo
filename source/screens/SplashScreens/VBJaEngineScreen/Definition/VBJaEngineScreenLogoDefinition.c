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
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    54,

    // allocation type
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

    // number of frames
    1,

   // palette number
    0,
};

CharSetROMDef VBJAENGINE_LOGO_OUTLINE_CH =
{
    // number of chars, depending on allocation type:
    // __ANIMATED_SINGLE: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_SHARED_COORDINATED: number of chars of a single animation frame (cols * rows)
    // __ANIMATED_MULTI: sum of chars of all animation frames
    // __NOT_ANIMATED: number of chars of whole image
    57,

    // allocation type
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

    // number of frames
    1,

    // palette number
    1,
};

BgmapSpriteROMDef VBJAENGINE_LOGO_3D_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&VBJAENGINE_LOGO_3D_TX,

	// displacement vector
	{0, 0, 0},
	
	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,
	
	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* const VBJAENGINE_LOGO_3D_IM_SPRITES[] =
{
	&VBJAENGINE_LOGO_3D_IM_SPRITE,
	NULL
};

BgmapSpriteROMDef VBJAENGINE_LOGO_OUTLINE_IM_SPRITE =
{
	// sprite's type
	__TYPE(BgmapSprite),

	// texture definition
	(TextureDefinition*)&VBJAENGINE_LOGO_OUTLINE_TX,

	// displacement vector
	{0, 0, 0},

	// bgmap mode (BGMAP, AFFINE or H-BIAS)
	WRLD_BGMAP,

	// display mode (WRLD_ON, WRLD_LON or WRLD_RON)
	WRLD_ON,
};

BgmapSpriteROMDef* VBJAENGINE_LOGO_OUTLINE_IM_SPRITES[] =
{
	&VBJAENGINE_LOGO_OUTLINE_IM_SPRITE,
	NULL
};

ImageROMDef VBJAENGINE_LOGO_3D_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)VBJAENGINE_LOGO_3D_IM_SPRITES,
};

ImageROMDef VBJAENGINE_LOGO_OUTLINE_IM =
{
	__TYPE(Image),
	(SpriteROMDef**)VBJAENGINE_LOGO_OUTLINE_IM_SPRITES,
};